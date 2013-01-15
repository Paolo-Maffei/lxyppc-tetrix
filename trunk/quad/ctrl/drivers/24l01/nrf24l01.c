#include "nrf24l01.h"
#include "nrf24l01_config.h"


// https://github.com/maniacbug/RF24
// www.nordicsemi.com/kor/Products/2.4GHz-RF/nRF24L01P

void nrf_init(void)
{
    //spi_init(); // init spi for NRF24L01
    NRF_INIT();
    NRF_TRANSFER_BYTE(0xff);
	NRF_CE_DISABLE;     // idle mode 1
	NRF_CS_DISABLE;     // disable CS
}

void nrf_ce_pulse(void)
{
    NRF_CE_ENABLE;
    delay_us(10);
    NRF_CE_DISABLE;
}

uint8_t nrf_detect(void)
{
	uint8_t buf[5]={0XA5,0XA5,0XA5,0XA5,0XA5};
	uint32_t i;	 
	nrf_write_buf(NRF_WRITE_REG|NRF_TX_ADDR,buf,5);    //write 5 bytes data
	nrf_read_buf(NRF_TX_ADDR,buf,5);               // read 5 bytes data
	for(i=0;i<5;i++)if(buf[i]!=0XA5)break;          // compare them
	if(i!=5)return 0;                               // detect fail
	return 1;                                       // detect success
}

uint8_t nrf_write_reg(uint8_t reg,uint8_t value)
{
	uint8_t status;	
   	NRF_CS_ENABLE;                   // Enable SPI CS
  	status = NRF_TRANSFER_BYTE(reg); // send reg addr
  	NRF_TRANSFER_BYTE(value);       // send value
  	NRF_CS_DISABLE;                     // Disable SPI CS
  	return(status);
}

uint8_t nrf_read_reg(uint8_t reg)
{
	uint8_t reg_val;	    
   	NRF_CS_ENABLE;                   // Enable SPI CS	
  	NRF_TRANSFER_BYTE(reg);         // send reg addr
  	reg_val=NRF_TRANSFER_BYTE(0XFF);// read value
  	NRF_CS_DISABLE;                     // Disable SPI CS    
  	return(reg_val);
}

uint8_t nrf_read_buf(uint8_t reg, uint8_t *pBuf, uint32_t len)
{
	uint8_t status;
  	NRF_CS_ENABLE;
  	status = NRF_TRANSFER_BYTE(reg);   
 	while(len--)
        *pBuf++ = NRF_TRANSFER_BYTE(0XFF);
  	NRF_CS_DISABLE;
  	return status;
}

uint8_t nrf_write_buf(uint8_t reg, const uint8_t *pBuf, uint32_t len)
{
	uint8_t status;
 	NRF_CS_ENABLE;
  	status = NRF_TRANSFER_BYTE(reg);
  	while(len--)
        NRF_TRANSFER_BYTE(*pBuf++);
  	NRF_CS_DISABLE; 
  	return status;
}

uint8_t nrf_tx_packet(const uint8_t *txbuf, uint32_t len)
{
	uint8_t status;
	NRF_CE_DISABLE;
  	nrf_write_buf(NRF_WR_TX_PLOAD,txbuf,len);
 	NRF_CE_ENABLE; // start transmit
	while(!NRF_READY); // wait transfer done
	status = nrf_read_reg(NRF_STATUS);  //read status
	nrf_write_reg(NRF_WRITE_REG|NRF_STATUS,status); // clear IRQ flags
	if(status & NRF_MAX_RT)
	{
		nrf_write_reg(NRF_FLUSH_TX,0xff); // clean TX buffer
		return NRF_MAX_RT; 
	}
	if(status & NRF_TX_OK) // transfer success
	{
		return NRF_TX_OK;
	}
	return 0xff;// transfer fail
}

uint8_t nrf_tx_packet_no_wait(const uint8_t *txbuf, uint32_t len)
{
	NRF_CE_DISABLE;
  	nrf_write_buf(NRF_WR_TX_PLOAD,txbuf,len);
 	NRF_CE_ENABLE; // start transmit
    delay_us(10);  // delay 10 us
    NRF_CE_DISABLE;//
	return 0;//
}


uint8_t nrf_ack_packet(uint8_t pipe, const uint8_t *ackbuf, uint32_t len)
{
    return nrf_write_buf(NRF_WR_ACK_PAYLOAD | (pipe & 0x07), ackbuf, len);
}

uint8_t nrf_rx_packet(uint8_t *rxbuf, uint32_t len)
{
	uint8_t status;		    							   
	status = nrf_read_reg(NRF_STATUS);
	nrf_write_reg(NRF_WRITE_REG|NRF_STATUS,status); // clear IRQ flags
	if(status & NRF_RX_OK)
	{
		nrf_read_buf(NRF_RD_RX_PLOAD,rxbuf,len);
		nrf_write_reg(NRF_FLUSH_RX, 0xff);
		return NRF_RX_OK;
	}	   
	return 0;
}


//#include "hal_nrf.h"
//#include "radio_esb.h"
void nrf_rx_mode_no_aa(const uint8_t* addr, uint8_t addr_len, uint32_t rx_len, uint8_t channel)
{
	NRF_CE_DISABLE;
  	nrf_write_buf(NRF_WRITE_REG|NRF_RX_ADDR_P0, addr,addr_len);
  	nrf_write_reg(NRF_WRITE_REG|NRF_EN_AA, 0);
  	nrf_write_reg(NRF_WRITE_REG|NRF_EN_RXADDR, NRF_ERX_P0);
  	nrf_write_reg(NRF_WRITE_REG|NRF_RF_CH,channel);
  	nrf_write_reg(NRF_WRITE_REG|NRF_RX_PW_P0, rx_len);   
  	nrf_write_reg(NRF_WRITE_REG|NRF_RF_SETUP, NRF_PWR_0dBm | NRF_DR_1Mbps);
  	nrf_write_reg(NRF_WRITE_REG|NRF_CONFIG,
        NRF_EN_ALL_IRQ | NRF_EN_CRC | NRF_CRC_2B | NRF_POWER_UP | NRF_PRIM_RX);
    
    //nrf_write_reg(NRF_WRITE_REG|NRF_RF_SETUP, 0x07);
  	//nrf_write_reg(NRF_WRITE_REG|NRF_CONFIG, 0x0f);
    //nrf_write_reg(NRF_WRITE_REG|NRF_DYNPD, NRF_DPL_P0);
    //nrf_write_reg(NRF_WRITE_REG|NRF_FEATURE, NRD_EN_DPL | NRF_EN_ACK_PAYLOAD);
    NRF_CE_ENABLE;
}	

void nrf_rx_mode(const uint8_t* addr, uint8_t addr_len, uint32_t rx_len, uint8_t channel)
{
    //radio_esb_init(addr, HAL_NRF_PRX);
    //return;
	NRF_CE_DISABLE;
  	nrf_write_buf(NRF_WRITE_REG|NRF_RX_ADDR_P0, addr,addr_len);
  	nrf_write_reg(NRF_WRITE_REG|NRF_EN_AA, NRF_ENAA_P0);
  	nrf_write_reg(NRF_WRITE_REG|NRF_EN_RXADDR, NRF_ERX_P0);
  	nrf_write_reg(NRF_WRITE_REG|NRF_RF_CH,channel);
  	nrf_write_reg(NRF_WRITE_REG|NRF_RX_PW_P0, rx_len);
    nrf_write_reg(NRF_WRITE_REG|NRF_SETUP_AW, NRF_AW_5);
  	nrf_write_reg(NRF_WRITE_REG|NRF_RF_SETUP, NRF_PWR_0dBm | NRF_DR_1Mbps);
  	nrf_write_reg(NRF_WRITE_REG|NRF_CONFIG,
        NRF_EN_ALL_IRQ | NRF_EN_CRC | NRF_CRC_2B | NRF_POWER_UP | NRF_PRIM_RX);
    //nrf_write_reg(NRF_WRITE_REG|NRF_RF_SETUP, 0x07);
  	//nrf_write_reg(NRF_WRITE_REG|NRF_CONFIG, 0x0f);
    //nrf_write_reg(NRF_WRITE_REG|NRF_DYNPD, NRF_DPL_P0);
    //nrf_write_reg(NRF_WRITE_REG|NRF_FEATURE, NRD_EN_DPL | NRF_EN_ACK_PAYLOAD);
    NRF_CE_ENABLE;
}						 

void nrf_rx_mode_dual(const uint8_t* addr, uint8_t addr_len, uint8_t channel)
{
	NRF_CE_DISABLE;
  	nrf_write_buf(NRF_WRITE_REG|NRF_RX_ADDR_P0, addr,addr_len);
  	nrf_write_reg(NRF_WRITE_REG|NRF_EN_AA, NRF_ENAA_P0);
  	nrf_write_reg(NRF_WRITE_REG|NRF_EN_RXADDR, NRF_ERX_P0);
  	nrf_write_reg(NRF_WRITE_REG|NRF_RF_CH,channel);
  	nrf_write_reg(NRF_WRITE_REG|NRF_RX_PW_P0, 16);
    
    nrf_write_reg(NRF_WRITE_REG|NRF_FEATURE , NRD_EN_DPL | NRF_EN_ACK_PAYLOAD);
    if(nrf_read_reg(NRF_FEATURE) == 0x00 && (nrf_read_reg(NRF_DYNPD) == 0x00)){
        nrf_write_reg(NRF_ACTIVATE, 0x73);
    }
    nrf_write_reg(NRF_WRITE_REG|NRF_FEATURE , NRD_EN_DPL | NRF_EN_ACK_PAYLOAD);
    nrf_write_reg(NRF_WRITE_REG|NRF_DYNPD, NRF_DPL_P0 | NRF_DPL_P1| NRF_DPL_P2| NRF_DPL_P3| NRF_DPL_P4| NRF_DPL_P5);
    
    nrf_write_reg(NRF_WRITE_REG|NRF_SETUP_AW, NRF_AW_5);
  	nrf_write_reg(NRF_WRITE_REG|NRF_RF_SETUP, NRF_PWR_0dBm | NRF_DR_1Mbps);
  	nrf_write_reg(NRF_WRITE_REG|NRF_CONFIG,
        NRF_EN_ALL_IRQ | NRF_EN_CRC | NRF_CRC_2B | NRF_POWER_UP | NRF_PRIM_RX);
    
    //nrf_write_reg(NRF_WRITE_REG|NRF_RF_SETUP, 0x07);
  	//nrf_write_reg(NRF_WRITE_REG|NRF_CONFIG, 0x0f);
    //nrf_write_reg(NRF_WRITE_REG|NRF_DYNPD, NRF_DPL_P0);
    //nrf_write_reg(NRF_WRITE_REG|NRF_FEATURE, NRD_EN_DPL | NRF_EN_ACK_PAYLOAD);
    NRF_CE_ENABLE;
}

void nrf_tx_mode_dual(const uint8_t* addr, uint8_t addr_len , uint8_t channel)
{
	NRF_CE_DISABLE;
  	nrf_write_buf(NRF_WRITE_REG|NRF_TX_ADDR,addr,addr_len);//дTX�ڵ��ַ 
  	nrf_write_buf(NRF_WRITE_REG|NRF_RX_ADDR_P0,addr,addr_len); //����TX�ڵ��ַ,��ҪΪ��ʹ��ACK	  
    nrf_write_reg(NRF_WRITE_REG|NRF_SETUP_AW, NRF_AW_5);
  	nrf_write_reg(NRF_WRITE_REG|NRF_EN_AA, NRF_ENAA_P0);
  	nrf_write_reg(NRF_WRITE_REG|NRF_EN_RXADDR, NRF_ERX_P0);
    
    nrf_write_reg(NRF_WRITE_REG|NRF_FEATURE , NRD_EN_DPL | NRF_EN_ACK_PAYLOAD);
    if(nrf_read_reg(NRF_FEATURE) == 0x00 && (nrf_read_reg(NRF_DYNPD) == 0x00)){
        nrf_write_reg(NRF_ACTIVATE, 0x73);
    }
    nrf_write_reg(NRF_WRITE_REG|NRF_FEATURE , NRD_EN_DPL | NRF_EN_ACK_PAYLOAD);
    nrf_write_reg(NRF_WRITE_REG|NRF_DYNPD, NRF_DPL_P0 | NRF_DPL_P1| NRF_DPL_P2| NRF_DPL_P3| NRF_DPL_P4| NRF_DPL_P5);
    
    
  	nrf_write_reg(NRF_WRITE_REG|NRF_SETUP_RETR, NRF_ARD(500) | NRF_ARC(2));

  	nrf_write_reg(NRF_WRITE_REG|NRF_RF_CH, channel);
  	nrf_write_reg(NRF_WRITE_REG|NRF_RF_SETUP, NRF_PWR_0dBm | NRF_DR_1Mbps);
  	nrf_write_reg(NRF_WRITE_REG|NRF_CONFIG, 
        NRF_EN_ALL_IRQ | NRF_EN_CRC | NRF_CRC_2B | NRF_POWER_UP | NRF_PRIM_TX );



    NRF_CE_ENABLE;
}


void nrf_irq_handler(void)
{
    uint8_t buffer[32];
    uint8_t status = nrf_read_reg(NRF_STATUS);
	nrf_write_reg(NRF_WRITE_REG|NRF_STATUS,status); // clear IRQ flags
    
    switch(status & (NRF_MAX_RT|NRF_TX_OK|NRF_RX_OK) )
    {
        case NRF_MAX_RT:
            nrf_tx_done(NRF_TX_FAIL);
            nrf_write_reg(NRF_FLUSH_TX,0xff);
            break;
        case NRF_TX_OK:
            nrf_tx_done(NRF_TX_SUCCESS);
            break;
        case NRF_TX_OK|NRF_RX_OK:
            nrf_tx_done(NRF_ACK_SUCCESS);
        case NRF_RX_OK:
            while( (status & NRF_RX_P_NO_MASK) != NRF_RX_P_NO_MASK){
                uint32_t len = nrf_read_reg(NRF_RD_RX_PL_WID);
                nrf_read_buf(NRF_RD_RX_PLOAD,buffer,len);
                nrf_on_rx_data(buffer, len, (status & NRF_RX_P_NO_MASK) >> 1);
                status = nrf_read_reg(NRF_STATUS);
            }
            break;
        default:
            break;
    }
}

void nrf_test_reg(void)
{
    uint8_t buf[16] = {0};
    nrf_read_buf(NRF_RX_ADDR_P0, buf, 5);
    nrf_read_buf(NRF_TX_ADDR, buf, 5);
    buf[0] = nrf_read_reg(NRF_EN_AA);
    buf[1] = nrf_read_reg(NRF_EN_RXADDR);
    buf[2] = nrf_read_reg(NRF_RF_CH);
    buf[3] = nrf_read_reg(NRF_RX_PW_P0);
    buf[4] = nrf_read_reg(NRF_RF_SETUP);
    buf[5] = nrf_read_reg(NRF_CONFIG);
    buf[6] = nrf_read_reg(NRF_SETUP_RETR);
}

void nrf_tx_mode_no_aa(const uint8_t* addr, uint8_t addr_len, uint8_t channel)
{
	NRF_CE_DISABLE;
  	nrf_write_buf(NRF_WRITE_REG|NRF_TX_ADDR,addr,addr_len);//дTX�ڵ��ַ 
  	//nrf_write_buf(NRF_WRITE_REG|NRF_RX_ADDR_P0,addr,addr_len); //����TX�ڵ��ַ,��ҪΪ��ʹ��ACK	  

  	nrf_write_reg(NRF_WRITE_REG|NRF_EN_AA, 0);
  	nrf_write_reg(NRF_WRITE_REG|NRF_EN_RXADDR, 0);
  	nrf_write_reg(NRF_WRITE_REG|NRF_SETUP_RETR, 0);
  	nrf_write_reg(NRF_WRITE_REG|NRF_RF_CH, channel);
  	nrf_write_reg(NRF_WRITE_REG|NRF_RF_SETUP, NRF_PWR_0dBm | NRF_DR_1Mbps);
  	nrf_write_reg(NRF_WRITE_REG|NRF_CONFIG, 
        NRF_EN_ALL_IRQ | NRF_EN_CRC | NRF_CRC_2B | NRF_POWER_UP | NRF_PRIM_TX );
    //nrf_write_reg(NRF_WRITE_REG|NRF_RF_SETUP, 0x07);
  	//nrf_write_reg(NRF_WRITE_REG|NRF_CONFIG, 0x0e);
    
    //nrf_write_reg(NRF_WRITE_REG|NRF_DYNPD, NRF_DPL_P0);
    //nrf_write_reg(NRF_WRITE_REG|NRF_FEATURE, NRD_EN_DPL | NRF_EN_ACK_PAYLOAD);
	NRF_CE_ENABLE;
}

void nrf_tx_mode(const uint8_t* addr, uint8_t addr_len, uint8_t channel)
{					
	NRF_CE_DISABLE;
  	nrf_write_buf(NRF_WRITE_REG|NRF_TX_ADDR,addr,addr_len);//дTX�ڵ��ַ 
  	nrf_write_buf(NRF_WRITE_REG|NRF_RX_ADDR_P0,addr,addr_len); //����TX�ڵ��ַ,��ҪΪ��ʹ��ACK	  
    nrf_write_reg(NRF_WRITE_REG|NRF_SETUP_AW, NRF_AW_5);
  	nrf_write_reg(NRF_WRITE_REG|NRF_EN_AA, NRF_ENAA_P0);
  	nrf_write_reg(NRF_WRITE_REG|NRF_EN_RXADDR, NRF_ERX_P0);
  	nrf_write_reg(NRF_WRITE_REG|NRF_SETUP_RETR, NRF_ARD(500) | NRF_ARC(2));
    //nrf_write_reg(NRF_WRITE_REG|NRF_SETUP_RETR, 0x1a);
  	nrf_write_reg(NRF_WRITE_REG|NRF_RF_CH, channel);
  	nrf_write_reg(NRF_WRITE_REG|NRF_RF_SETUP, NRF_PWR_0dBm | NRF_DR_1Mbps);
  	nrf_write_reg(NRF_WRITE_REG|NRF_CONFIG, 
        NRF_EN_ALL_IRQ | NRF_EN_CRC | NRF_CRC_2B | NRF_POWER_UP | NRF_PRIM_TX );
    //nrf_write_reg(NRF_WRITE_REG|NRF_RF_SETUP, 0x07);
  	//nrf_write_reg(NRF_WRITE_REG|NRF_CONFIG, 0x0e);
    //nrf_write_reg(NRF_WRITE_REG|NRF_DYNPD, NRF_DPL_P0);
    //nrf_write_reg(NRF_WRITE_REG|NRF_FEATURE, NRD_EN_DPL | NRF_EN_ACK_PAYLOAD);
    
	NRF_CE_ENABLE;
}

uint8_t nrf_flush_tx(void)
{
    uint8_t status;
    NRF_CS_ENABLE;
    status = NRF_TRANSFER_BYTE( NRF_FLUSH_TX );
    NRF_CS_DISABLE;
    return status;
}

uint8_t nrf_flush_rx(void)
{
    uint8_t status;
    NRF_CS_ENABLE;
    status = NRF_TRANSFER_BYTE( NRF_FLUSH_RX );
    NRF_CS_DISABLE;
    return status;
}

uint8_t nrf_get_status(void)
{
  uint8_t status;
  NRF_CS_ENABLE;
  status = NRF_TRANSFER_BYTE( NRF_NOP );
  NRF_CS_DISABLE;
  return status;
}

void nrf_set_channel(uint8_t channel)
{
    // TODO: 
    nrf_write_reg(NRF_WRITE_REG|NRF_RF_CH, channel);
}

uint8_t nrf_test_carrier(void)
{
  return ( nrf_read_reg(NRF_CD) & 1 );
}

uint8_t nrf_test_RPD(void)
{
  return ( nrf_read_reg(NRF_RPD) & 1 ) ;
}

uint8_t nrf_get_status_and_reset_int(void)
{
    return nrf_write_reg(NRF_WRITE_REG|NRF_STATUS,NRF_RX_OK | NRF_TX_OK | NRF_MAX_RT );
}

// get available pipe number
uint8_t nrf_rx_available(void)
{
    uint8_t status = nrf_get_status_and_reset_int();
    if(status & NRF_RX_OK){
        return (status >> 1) & 0x7;
    }
    return 0xff;
}


