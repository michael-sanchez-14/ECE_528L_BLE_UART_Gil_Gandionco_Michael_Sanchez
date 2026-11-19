/**
 * @file main.c
 *
 * @brief Main source code for the BLE_UART program.
 *
 * This file contains the main entry point for the BLE_UART program,
 * which is used to demonstrate the BLE_UART driver.
 *
 * It interfaces with the Adafruit Bluefruit LE UART Friend Bluetooth Low Energy (BLE) module, which uses the UART communication protocol.
 *  - Product Link: https://www.adafruit.com/product/2479
 *
 * @note For more information regarding the Enhanced Universal Serial Communication Interface (eUSCI),
 * refer to the MSP432Pxx Microcontrollers Technical Reference Manual
 *
 * @authors Gil Gandionco and Michael Sanchez
 *
 */

#include <stdint.h>
#include <math.h>
#include "msp.h"

#include "inc/Clock.h"
#include "inc/CortexM.h"
#include "inc/GPIO.h"
#include "inc/EUSCI_A0_UART.h"
#include "inc/Motor.h"
#include "inc/BLE_UART.h"

#define PWM_NOMINAL 3000

void Process_BLE_UART_Data(char BLE_UART_Buffer[])
{
    if(Check_BLE_UART_Data(BLE_UART_Buffer, "RGB LED GREEN"))
    {
        LED2_Output(RGB_LED_GREEN);
    }

    else if(Check_BLE_UART_Data(BLE_UART_Buffer, "RGB LED OFF"))
    {
        LED2_Output(RGB_LED_OFF);
    }

    else
    {
        printf("BLE UART Command Not Found \n");
    }
}

void Decode_Controller_Packet(char BLE_UART_Buffer[])
{
    if(BLE_UART_Buffer[0] == 0x21 && BLE_UART_Buffer[1] == 0x42)
    {
        printf("valid Button Packet \n");
        if(BLE_UART_Buffer[3] == 0x30)
        {
            Motor_Stop();
        }
        if(BLE_UART_Buffer[3] == 0x31)
        {
            switch (BLE_UART_Buffer[2])
            {
                case 0x35:
                    //Motor_Forward(PWM_NOMINAL * 0.3, PWM_NOMINAL * 0.3);
                    Motor_Forward(PWM_NOMINAL, PWM_NOMINAL);
                    break;

                case 0x36:
                    //Motor_Backward(PWM_NOMINAL * 0.3, PWM_NOMINAL * 0.3);
                    Motor_Backward(PWM_NOMINAL, PWM_NOMINAL);
                    break;

                case 0x37:
                    //Motor_Left(PWM_NOMINAL * 0.3, PWM_NOMINAL * 0.3);
                    Motor_Left(PWM_NOMINAL, PWM_NOMINAL);
                    break;

                case 0x38:
                    //Motor_Right(PWM_NOMINAL * 0.3, PWM_NOMINAL * 0.3);
                    Motor_Right(PWM_NOMINAL, PWM_NOMINAL);
                    break;
            }
        }
    }
    else
    {
        printf("Invalid Button Packet \n");
    }
}

int main(void)
{

    DisableInterrupts();
    Clock_Init48MHz();
    LED2_Init();
    EUSCI_A0_UART_Init_Printf();
    BLE_UART_Init();
    Motor_Init();

    char BLE_UART_Buffer[BLE_UART_BUFFER_SIZE] = {0};

    EnableInterrupts();

    Clock_Delay1ms(1000);
    BLE_UART_Reset();

    BLE_UART_OutString("BLE UART ACTIVE\r\n");
    Clock_Delay1ms(1000);


    while(1)
    {
        //int string_size = BLE_UART_InString(BLE_UART_Buffer, BLE_UART_BUFFER_SIZE);
        BLE_UART_InPacket(BLE_UART_Buffer);

        printf("BLE UART DATA: ");

        for(int i = 0; i < 5; i++)
        {
            printf("%c", BLE_UART_Buffer[i]);
        }

        printf("\n");

        //Process_BLE_UART_Data(BLE_UART_Buffer);
        Decode_Controller_Packet(BLE_UART_Buffer);

        //Part A
//        BLE_UART_OutChar(0xAA);
//        Clock_Delay1ms(100);

//        BLE_UART_OutChar(0x55);
//        Clock_Delay1ms(100);
//        BLE_UART_OutChar(0xFF);
//        Clock_Delay1ms(100);
//        BLE_UART_OutChar(0x00);
//        Clock_Delay1ms(100);

        //Part B
//        uint8_t button_status = Get_Buttons_Status();
//        uint8_t switch_status = Get_PMOD_SWT_Status();
//        LED_Controller(button_status, switch_status);
//        Clock_Delay1ms(100);
    }
}
