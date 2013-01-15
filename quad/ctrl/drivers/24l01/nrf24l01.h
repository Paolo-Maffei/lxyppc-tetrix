#ifndef NRF24L01_H
#define NRF24L01_H
#include "bsp/bsp.h"
//////////////////////////////////////////////////////////////////////////////////////////////////////////
//NRF24L01 command
#define NRF_READ_REG        0x00  //�����üĴ���,��5λΪ�Ĵ�����ַ
#define NRF_WRITE_REG       0x20  //д���üĴ���,��5λΪ�Ĵ�����ַ
#define NRF_ACTIVATE        0x50  // 
#define NRF_RD_RX_PL_WID    0x60  // read rx payload width
#define NRF_RD_RX_PLOAD     0x61  //��RX��Ч����,1~32�ֽ�
#define NRF_WR_TX_PLOAD     0xA0  //дTX��Ч����,1~32�ֽ�
#define NRF_WR_ACK_PAYLOAD  0xA8  //
#define NRF_FLUSH_TX        0xE1  //���TX FIFO�Ĵ���.����ģʽ����
#define NRF_FLUSH_RX        0xE2  //���RX FIFO�Ĵ���.����ģʽ����
#define NRF_REUSE_TX_PL     0xE3  //����ʹ����һ������,CEΪ��,���ݰ������Ϸ���.
#define NRF_NOP             0xFF  //�ղ���,����������״̬�Ĵ���	 
//NRF24L01 address
#define NRF_CONFIG          0x00  //���üĴ�����ַ;bit0:1����ģʽ,0����ģʽ;bit1:��ѡ��;bit2:CRCģʽ;bit3:CRCʹ��;
                              //bit4:�ж�MAX_RT(�ﵽ����ط������ж�)ʹ��;bit5:�ж�TX_DSʹ��;bit6:�ж�RX_DRʹ��
#define NRF_EN_AA           0x01  //ʹ���Զ�Ӧ����  bit0~5,��Ӧͨ��0~5
#define NRF_EN_RXADDR       0x02  //���յ�ַ����,bit0~5,��Ӧͨ��0~5
#define NRF_SETUP_AW        0x03  //���õ�ַ���(��������ͨ��):bit1,0:00,3�ֽ�;01,4�ֽ�;02,5�ֽ�;
#define NRF_SETUP_RETR      0x04  //�����Զ��ط�;bit3:0,�Զ��ط�������;bit7:4,�Զ��ط���ʱ 250*x+86us
#define NRF_RF_CH           0x05  //RFͨ��,bit6:0,����ͨ��Ƶ��;
#define NRF_RF_SETUP        0x06  //RF�Ĵ���;bit3:��������(0:1Mbps,1:2Mbps);bit2:1,���书��;bit0:�������Ŵ�������
#define NRF_STATUS          0x07  //״̬�Ĵ���;bit0:TX FIFO����־;bit3:1,��������ͨ����(���:6);bit4,�ﵽ�����ط�
                              //bit5:���ݷ�������ж�;bit6:���������ж�;

#define NRF_OBSERVE_TX      0x08  //���ͼ��Ĵ���,bit7:4,���ݰ���ʧ������;bit3:0,�ط�������
#define NRF_CD              0x09  //�ز����Ĵ���,bit0,�ز����;
#define NRF_RPD             0x09  //�ز����Ĵ���,bit0,�ز����;
#define NRF_RX_ADDR_P0      0x0A  //����ͨ��0���յ�ַ,��󳤶�5���ֽ�,���ֽ���ǰ
#define NRF_RX_ADDR_P1      0x0B  //����ͨ��1���յ�ַ,��󳤶�5���ֽ�,���ֽ���ǰ
#define NRF_RX_ADDR_P2      0x0C  //����ͨ��2���յ�ַ,����ֽڿ�����,���ֽ�,����ͬRX_ADDR_P1[39:8]���;
#define NRF_RX_ADDR_P3      0x0D  //����ͨ��3���յ�ַ,����ֽڿ�����,���ֽ�,����ͬRX_ADDR_P1[39:8]���;
#define NRF_RX_ADDR_P4      0x0E  //����ͨ��4���յ�ַ,����ֽڿ�����,���ֽ�,����ͬRX_ADDR_P1[39:8]���;
#define NRF_RX_ADDR_P5      0x0F  //����ͨ��5���յ�ַ,����ֽڿ�����,���ֽ�,����ͬRX_ADDR_P1[39:8]���;
#define NRF_TX_ADDR         0x10  //���͵�ַ(���ֽ���ǰ),ShockBurstTMģʽ��,RX_ADDR_P0��˵�ַ���
#define NRF_RX_PW_P0        0x11  //��������ͨ��0��Ч���ݿ��(1~32�ֽ�),����Ϊ0��Ƿ�
#define NRF_RX_PW_P1        0x12  //��������ͨ��1��Ч���ݿ��(1~32�ֽ�),����Ϊ0��Ƿ�
#define NRF_RX_PW_P2        0x13  //��������ͨ��2��Ч���ݿ��(1~32�ֽ�),����Ϊ0��Ƿ�
#define NRF_RX_PW_P3        0x14  //��������ͨ��3��Ч���ݿ��(1~32�ֽ�),����Ϊ0��Ƿ�
#define NRF_RX_PW_P4        0x15  //��������ͨ��4��Ч���ݿ��(1~32�ֽ�),����Ϊ0��Ƿ�
#define NRF_RX_PW_P5        0x16  //��������ͨ��5��Ч���ݿ��(1~32�ֽ�),����Ϊ0��Ƿ�
#define NRF_FIFO_STATUS     0x17  //FIFO״̬�Ĵ���;bit0,RX FIFO�Ĵ����ձ�־;bit1,RX FIFO����־;bit2,3,����
                              //bit4,TX FIFO�ձ�־;bit5,TX FIFO����־;bit6,1,ѭ��������һ���ݰ�.0,��ѭ��;
#define NRF_DYNPD           0x1C
#define NRF_FEATURE         0x1D
//////////////////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////////////////////////
/// NRF24L01 bit field
// config register
#define NRF_PRIM_RX         0x01
#define NRF_PRIM_TX         0x00
#define NRF_POWER_UP        0x02
#define NRF_CRC0            0x04
#define NRF_CRC_1B          0x00
#define NRF_CRC_2B          0x04
#define NRF_EN_CRC          0x08
#define NRF_DIS_CRC         0x00
#define NRF_MASK_MAX_RT     0x10
#define NRF_EN_MAX_RT_IRQ   0x00
#define NRF_DIS_MAX_RT_IRQ  0x10
#define NRF_MASK_TX_OK      0x20
#define NRF_EN_TX_OK_IRQ    0x00
#define NRF_DIS_TX_OK_IRQ   0x20
#define NRF_MASK_RX_OK      0x40
#define NRF_EN_RX_OK_IRQ    0x00
#define NRF_DIS_RX_OK_IRQ   0x40
#define NRF_EN_ALL_IRQ      0x00
#define NRF_DIS_ALL_IRQ     (NRF_DIS_MAX_RT_IRQ | NRF_DIS_TX_OK_IRQ | NRF_DIS_RX_OK_IRQ)
// EN_AA
#define NRF_ENAA_P0         0x01
#define NRF_ENAA_P1         0x02
#define NRF_ENAA_P2         0x04
#define NRF_ENAA_P3         0x08
#define NRF_ENAA_P4         0x10
#define NRF_ENAA_P5         0x20
// EN_RXADDR
#define NRF_ERX_P0          0x01
#define NRF_ERX_P1          0x02
#define NRF_ERX_P2          0x04
#define NRF_ERX_P3          0x08
#define NRF_ERX_P4          0x10
#define NRF_ERX_P5          0x20
// SETUP_AW
#define NRF_AW_3            0x01
#define NRF_AW_4            0x02
#define NRF_AW_5            0x03
// SETUP_RETR
#define NRF_ARD(us)      ( (( (us-1)/250  )&0x0f)<<4 )
#define NRF_ARDx( X_250_plus_250_us)     ( ((X_50_plus_250_us&)&0x0f)<<4 )
#define NRF_ARC( arc_count )            ((arc_count) & 0x0f)
// RF_CH
// RF_SETUP
#define NRF_PWR_18dBm         (0x0<<1)
#define NRF_PWR_12dBm         (0x1<<1)
#define NRF_PWR_6dBm          (0x2<<1)
#define NRF_PWR_0dBm          (0x3<<1)
#define NRF_DR_250Kbps        (1<<5)
#define NRF_DR_1Mbps          (0<<3)
#define NRF_DR_2Mbps          (1<<3)
#define NRF_PLL_LOCK          (1<<4)
#define NRF_CONT_WAVE            (1<<7)
// STATUS register
#define NRF_MAX_RT  	    0x10  //�ﵽ����ʹ����ж�
#define NRF_TX_OK   	    0x20  //TX��������ж�
#define NRF_RX_OK   	    0x40  //���յ������ж�
#define NRF_RX_P_NO_MASK    (0x07<<1)
#define NRF_TX_FULL         0x01
// OBSERVE_TX
#define  NRF_PLOS_CNT       0xF0
#define  NRF_ARC_CNT        0x0F
// FIFO_STATUS
#define  NRF_FIFO_RX_EMPTY  0x01
#define  NRF_FIFO_RX_FULL   0x02
#define  NRF_FIFO_TX_EMPTY  0x10
#define  NRF_FIFO_TX_FULL   0x20
#define  NRF_FIFO_TX_REUSE  0x40
// DYNPD
#define  NRF_DPL_P0         0x01
#define  NRF_DPL_P1         0x02
#define  NRF_DPL_P2         0x04
#define  NRF_DPL_P3         0x08
#define  NRF_DPL_P4         0x10
#define  NRF_DPL_P5         0x20
// FEATURE
#define  NRF_EN_DYN_ACK         0x01
#define  NRF_EN_ACK_PAYLOAD     0x02
#define  NRD_EN_DPL             0x04

#ifndef  NRF_CE_SET
#define  NRF_CE_SET
#endif 
#ifndef  NRF_CE_RESET
#define  NRF_CE_RESET
#endif 
#ifndef  NRF_CS_SET
#define  NRF_CS_SET
#endif 
#ifndef  NRF_CS_RESET
#define  NRF_CS_RESET
#endif

#define  NRF_CE_ENABLE      NRF_CE_SET
#define  NRF_CE_DISABLE     NRF_CE_RESET
#define  NRF_CS_ENABLE      NRF_CS_RESET
#define  NRF_CS_DISABLE     NRF_CS_SET
#define  NRF_READY          (NRF_IRQ == 0)

#define  NRF_MAX_CHANNEL    127

#define  NRF_TX_FAIL        0
#define  NRF_TX_SUCCESS     1
#define  NRF_ACK_SUCCESS    2

void nrf_init(void);
uint8_t nrf_detect(void);
uint8_t nrf_write_reg(uint8_t reg,uint8_t value);
uint8_t nrf_read_reg(uint8_t reg);
uint8_t nrf_read_buf(uint8_t reg,uint8_t *pBuf,uint32_t len);
uint8_t nrf_write_buf(uint8_t reg, const uint8_t *pBuf, uint32_t len);

uint8_t nrf_tx_packet(const uint8_t *txbuf, uint32_t len);
uint8_t nrf_tx_packet_no_wait(const uint8_t *txbuf, uint32_t len);
uint8_t nrf_ack_packet(uint8_t pipe, const uint8_t *ackbuf, uint32_t len);
uint8_t nrf_rx_packet(uint8_t *rxbuf, uint32_t len);
void nrf_rx_mode(const uint8_t* addr, uint8_t addr_len, uint32_t rx_len, uint8_t channel);
void nrf_tx_mode(const uint8_t* addr, uint8_t addr_len, uint8_t channel);

void nrf_rx_mode_no_aa(const uint8_t* addr, uint8_t addr_len, uint32_t rx_len, uint8_t channel);
void nrf_tx_mode_no_aa(const uint8_t* addr, uint8_t addr_len, uint8_t channel);

void nrf_tx_mode_dual(const uint8_t* addr, uint8_t addr_len, uint8_t channel);
void nrf_rx_mode_dual(const uint8_t* addr, uint8_t addr_len, uint8_t channel);

uint8_t nrf_get_status(void);
uint8_t nrf_test_carrier(void);
uint8_t nrf_rx_available(void);

void nrf_irq_handler(void);
void nrf_tx_done(uint8_t success);
void nrf_on_rx_data(const void* data, uint32_t len, uint8_t channel);
#endif
