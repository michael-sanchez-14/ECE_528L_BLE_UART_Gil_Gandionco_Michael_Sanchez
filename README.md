# ECE 528/L - Robotics and Embedded Systems with Lab
**CSU Northridge**

**Department of Electrical and Computer Engineering**

## Bluetooth Low Energy (BLE) Lab
The Bluetooth Low Energy (BLE) lab interfaces with the following:

* User LEDs of the TI MSP432 LaunchPad
* Pololu Gearmotor with Encoder - [Product Link](https://www.pololu.com/product/3675)
* Adafruit Bluefruit LE UART Friend - Bluetooth Low Energy (BLE) Module - [Product Link](https://www.adafruit.com/product/2479)

## Overview
The lab introduces both Bluetooth Low Energy(BLE) communcation and Universal Asynchronous Reciever/Transmitter(UART). The lab requires to develop a UART driver, specifically the EUSCI_A module, that allows the MSP432 LaunchPad to communicate with an Adafruit BlueFruit LE UART module. Using the Bluefruit Connect mobile app on the phone, wireless commands can be sent to the MSP432 to control the RGB LED and the motors of the robot.

## Components Used:
For this lab we used the following components:
* User LEDs of the TI MSP432 LaunchPad
* Pololu Gearmotor with Encoder - [Product Link](https://www.pololu.com/product/3675)
* Adafruit Bluefruit LE UART Friend - Bluetooth Low Energy (BLE) Module - [Product Link](https://www.adafruit.com/product/2479)
* MSP432 LaunchPad
* USB-A to Micro-USB cable
* TI-RSLK MAX Chassis 
* PMOD SWT
* Oscilloscope Probes

## Pre Lab
1. What is Bluetooth Low Energy (BLE)? How does it differ from regular Bluetooth in terms of power consumption and range?

Bluetooth Low Energy (BLE) is a power-efficient version of Bluetooth, designed for short-range wireless communication with low power consumption.

BLE uses less power, approximately 0.01W to 0.5W compared to bluetooth that uses around 1W. Both share a similar range of roughly 10 to 30 meters.


2. What does GAP stand for and what is its purpose? What is the difference between
Peripheral and Central devices in the context of BLE?

GAP means Generic Access Profile, its purpose is to control the connections and advertising in Bluetooth. 
The difference between Peripheral and Central devices in the context of BLE is that peripheral devices are smaller low power devices that connecet to a more powerful device while a central device is one that you connect to, inorder to get more proccessing power.

3. What is GATT in BLE, and how does it structure data exchange between connected devices? Provide definitions for the following: Profile, Service, and Characteristic.

Generic Attribute Profile (GATT) is the communication protocol in BLE that defines how devices organize, access, and exchange data after establishing a connection.

GATT organizes data into a 4-level hierarchy:
- Profile: set of rules that defines how BLE devices communicate
- Service: a group of data or features provided by a BLE device
- Characteristic: a specific piece of data that can be  read, written or updated
- Descriptor: additional information about a characteristic

4. What is an advertising packet in BLE and what information can it contain?

An advertising packet is a signal that tells other devices that it is able to be connected to, it contains the advertising data.

5. What is a UUID used for in BLE and why are 128-bit UUIDs used? You can use this page as a reference.

Universally unique identifier (UUID) is used in BLE to identify services, characteristics, and descriptors. BLE devices can recognize what type of data or features are avaiable.

128-bit UUIDs are used to prevent accidental duplication, making it unlikely for developers to accidentally create the same UUID. It removes the need for a central organization to assign each identifier.

6. What bit from which register determines if the UART data is received or transmitted
MSB or LSB first? Refer to the eUSCI_A UART Registers section (24.4) of the
MSP432P4xx Technical Reference Manual (SLAU356I)

The 13th bit, UCMSB, from the UCAxCTLW0 register determines if the UART data is recieved or transmitted MSB or LSB first. If this bit is set it is MSB first, else it is LSB first.

7. Provide the mnemonic and primary module function for each pin listed. Refer to Table 6-45 (Default Mapping) on page 126 of the MSP432P401R Datasheet.  

| Pin | Mnemonic | Input Pin Primary Function | Output Pin Primary Function |
| -------- | -------- | -------- | -------- |
| P2.2  | PM_UCA1RXD/PM_UCA1SOMI  | UART: MSP432 receives data from Bluetooth module. SPI: Slave sends data to master | N/A |
| P2.3  | PM_UCA1TXD/PM_UCA1SIMO  | N/A | UART: MSP432 sends data to Bluetooth module. SPI: Master sends data to slave |
| P3.2  | PM_UCA2RXD/PM_UCA2SOMI  | UART: MSP432 receives data from Bluetooth module. SPI: Slave sends data to master | N/A |
| P3.3  | PM_UCA2TXD/PM_UCA2SIMO  | N/A | UART: MSP432 sends data to Bluetooth module. SPI: Master sends data to slave |

8. Write a void function named P2_2_and_P2_3_Init that takes no arguments and configures the following pins to use primary function mode: P2.2 and P2.3. It is not necessary to set the direction of the pins. Refer to the following documents:
   * Section 12.2.6 – “Function Select Registers (PxSEL0, PxSEL1)” of the
MSP432P4xx Technical Reference Manual (SLAU356I)
   * Section 4.1 – “Pin Diagrams” and Section 6.12.2 – “Port P2 (P2.0 to P2.3)
Input/Output With Schmitt Trigger” of the MSP432P401R Datasheet

```
    void P2_2_and_P2_3_Init()
    {
        P2->SEL0 |= 0x0C;
        P2->SEL1 &= ~0x0C;
    }
```

## Analysis and Results:
The start of the lab required the implementation of several UART driver functions in the BLE_UART.c file as well as the main.c file. The functions are the following:
* BLE_UART_INIT()
  * Initializes UART
* BLE_UART_InChar()
  * Recieves Incoming character
* BLE_UART_OutChar()
  * Transmit outgoing character
* BLE_UART_InString()
  * Recieves and stores a string of characters
* BLE_UART_OutString()
  * Transmits string one character at a time
* Check_BLE_UART_Data()
  * Checks if the specified string exits in data
* BLE_UART_Reset()
  * Resets the BLE module
* Process_BLE_UART_Data()
  * Checks if the user sends a specific string

After implement the functions, the first part the lab required to very UART communication by sending the following data and checking the output with an oscilloscope:
* 0xAA
* 0x55
* 0xFF
* 0x00

The output of the oscilloscope for two of the bytes are displayed in the following photos:
* [0xAA](0xAA.jpg)
* [0x55](0x55.jpg)

Note that the least significant bit (LSB) is sent first which follows the configuration of UART. The next part required connecting the PMOD SWT module to select which byte is transmitted. Here is a table of the switch cases:

| Active Switch | All Other Switches | Byte Transmitted |
|:--------------|:------------------:|----------------:|
| SW1          | SW2, SW3, SW4 = OFF| 0xAA            |
| SW2          | SW1, SW3, SW4 = OFF| 0x10            |
| SW3          | SW1, SW2, SW4 = OFF| 0xF0            |
| SW4          | SW1, SW2, SW3 = OFF| 0x0F            |
| Other        |                    | 0x00            |

The results are captured in a video of all the switch cases, [Result](Taskb.mp4). The last task involved using wireless commands to control the robot's movement using the Bluefruit Connect mobile app. When a directional button is pressed or released, the mobile app transmits a five-byte packet:

| Byte | Description | Example |
| --- | --- | --- |
| Byte 0 | Header | ! (0x21) |
| Byte 1 | Packet Type | B (0x42) - Button Packet |
| Byte 2 | Button number | 5 = Up |
| Byte 3 | Button State | 1 = Pressed |
| Byte 4 | Checksum | Add the bytes and inverts the sum |

 The function, BLE_UART_InPacket(), was implemented to read exactly five bytes, beginning with the "!" header. It would discard all incoming characters until it received the "!" header (0x21) so it always starts the reading at the beginning of a packet. It stores the header and the next four bytes in the BLE_UART_buffer array.

 Another function, Decode_Controller_Packet(), would take the bytes stored in the BLE_UART_buffer and was used to validate the header and packet type. It would also identify the button number and state. Then, it would call the corresponding motor function. The up button makes the robot move forward, down button makes the robot move backward, left button makes the robot rotate left, and right button makes the robot rotate right. When a button is released, the motor stops immediately.

## Known Issues or Limitations
No known issues or limitations.

## Author Contribution
* Michael Sanchez
    * Worked on the Procedure portion of the Lab
    * Word on the Even quesitons in the Pre Lab
* Gil Gandionco 
    * Worked on the Task portion of the Lab
    * Worked on the Odd questions in the Pre Lab
## References

* MSP432P4xx SimpleLink™ Microcontrollers
Technical Reference Manual
* Microchip's Introduction to Bluetooth Low Energy - [Link](https://developerhelp.microchip.com/xwiki/bin/view/applications/ble/introduction/)
* Adafruit's guide on BLE - [Link](https://cdn-learn.adafruit.com/downloads/pdf/introduction-to-bluetooth-low-energy.pdf)