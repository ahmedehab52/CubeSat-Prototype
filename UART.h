/*
 * UART.h
 *
 * Created: 05-Oct-18 11:43:13 AM
 *  Author: MO_Ali
 */ 


#ifndef _UART_H_
#define _UART_H_
#define C_NOTOK_U8         0x00u
#define C_OK_U8            0x01u

#define C_INVALID_U8       0x00u
#define C_VALID_U8         0x01u

#define C_FAILED_U8        0x00u
#define C_SUCCESSFUL_U8    0x01u
#define C_BUSY_U8          0x02u


#define C_BINARY_U8           2u
#define C_DECIMAL_U8         10u
#define C_HEX_U8             16u

#include "../../main.h"
#define C_MinBaudRate_U32 2400
#define C_MaxBaudRate_U32 115200UL


#define M_GetBaudRateGeneratorValue(baudrate)  (((F_CPU -((baudrate) * 8L)) / ((baudrate) * 16UL)))
/**************************************************************************************************/





/***************************************************************************************************
                      PreCompile configurations to enable/disable the functions
****************************************************************************************************
PreCompile configuration to enable or disable the API's.
 1.Required interfaces can be enabled/disabled by configuring 
   its respective macros to 1/0.
 2. By default all the API's are enabled except for FLOAT transmission.
 3. Transmitting of floating number takes huge controller
    resources and need to be enabled only if required. 
	This implies for other interfaces as well. 
***************************************************************************************************/
#define    Enable_UART_TxString          1
#define    Enable_UART_RxString          1
#define    Enable_UART_TxNumber          1
#define    Enable_UART_TxFloatNumber     1
#define    Enable_UART_Printf            1
/**************************************************************************************************/





/***************************************************************************************************
                             Commonly used UART macros/Constants
***************************************************************************************************/
#define C_DefaultDigitsToTransmit_U8          0xffu    // Will transmit the exact digits in the number
#define C_MaxDigitsToTransmit_U8              10u      // Max decimal/hexadecimal digits to be transmitted
#define C_NumOfBinDigitsToTransmit_U8         16u      // Max bits of a binary number to be transmitted
#define C_MaxDigitsToTransmitUsingPrintf_U8   C_DefaultDigitsToTransmit_U8 /* Max dec/hexadecimal digits to be displayed using printf */
/**************************************************************************************************/





/***************************************************************************************************
                             Function Prototypes
***************************************************************************************************/

void UART_Init(uint32 v_baudRate_u32);
void UART_SetBaudRate(uint32 v_baudRate_u32);
void UART_TxChar(char v_uartData_u8);
char UART_RxChar(void);
void UART_TxString(char *ptr_string);
uint8 UART_RxString(char *ptr_string);
void UART_TxNumber(uint8_t v_numericSystem_u8, uint32 v_number_u32, uint8 v_numOfDigitsToTransmit_u8);
void UART_TxFloatNumber(f32 _floatNumber_f32);
void UART_TxFloatNumberD(f32 v_floatNumber_f32 , uint8 Digit_Num);
void UART_Printf(const char *argList, ...);
extern uint8 UART_RxStringSize(char *ptr_string , uint8 Size);
/**************************************************************************************************/

/******************* Errors Types *********************************/

#define INVALID_USER_OR_PASS	((uint8)(0u))
#define INVALID_ARGUMENT		((uint8)(1u))
#define INVALID_DATA			((uint8)(2u))
#define ACCES_DENIED			((uint8)(3u))

/******************************************************************/

#endif /* UART_H_ */