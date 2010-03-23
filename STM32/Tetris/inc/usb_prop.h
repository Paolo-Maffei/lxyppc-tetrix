/******************** (C) COPYRIGHT 2008 STMicroelectronics ********************
* File Name          : usb_prop.h
* Author             : MCD Application Team
* Version            : V2.2.0
* Date               : 06/13/2008
* Description        : All processing related to Mass Storage Demo (Endpoint 0)
********************************************************************************
* THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
* WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE TIME.
* AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY DIRECT,
* INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING FROM THE
* CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE CODING
* INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
*******************************************************************************/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __usb_prop_H
#define __usb_prop_H

/* Includes ------------------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
void Speaker_init(void);
void Speaker_Reset(void);
void Speaker_SetConfiguration(void);
void Speaker_SetDeviceAddress (void);
void Speaker_SetInterface(void);
void Speaker_Status_In (void);
void Speaker_Status_Out (void);
RESULT Speaker_Data_Setup(u8);
RESULT Speaker_NoData_Setup(u8);
RESULT Speaker_Get_Interface_Setting(u8 Interface, u8 AlternateSetting);
u8 *Speaker_GetDeviceDescriptor(u16 );
u8 *Speaker_GetConfigDescriptor(u16);
u8 *Speaker_GetStringDescriptor(u16);
u8 *Mute_Command(u16 Length);

/* Exported define -----------------------------------------------------------*/
#define Speaker_GetConfiguration          NOP_Process
//#define Speaker_SetConfiguration          NOP_Process
#define Speaker_GetInterface              NOP_Process
//#define Speaker_SetInterface              NOP_Process
#define Speaker_GetStatus                 NOP_Process
#define Speaker_ClearFeature              NOP_Process
#define Speaker_SetEndPointFeature        NOP_Process
#define Speaker_SetDeviceFeature          NOP_Process
//#define Speaker_SetDeviceAddress          NOP_Process
#define GET_CUR                           0x81
#define SET_CUR                           0x01

#define SET_INTERFACE                     0x0b

#endif /* __usb_prop_H */
/******************* (C) COPYRIGHT 2008 STMicroelectronics *****END OF FILE****/

