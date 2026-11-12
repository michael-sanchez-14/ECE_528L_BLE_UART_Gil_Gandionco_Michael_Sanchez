# ECE 528/L - Robotics and Embedded Systems with Lab
**CSU Northridge**

**Department of Electrical and Computer Engineering**

## Bluetooth Low Energy (BLE) Lab
The Bluetooth Low Energy (BLE) lab interfaces with the following:

* User LEDs of the TI MSP432 LaunchPad
* Pololu Gearmotor with Encoder - [Product Link](https://www.pololu.com/product/3675)
* Adafruit Bluefruit LE UART Friend - Bluetooth Low Energy (BLE) Module - [Product Link](https://www.adafruit.com/product/2479)

## Overview

## Components Used:

## Pre Lab
1. What is Bluetooth Low Energy (BLE)? How does it differ from regular Bluetooth in
terms of power consumption and range?

2. What does GAP stand for and what is its purpose? What is the difference between
Peripheral and Central devices in the context of BLE?

GAP means Generic Access Profile, its purpose is to control the connections and advertising in Bluetooth. 
The difference between Peripheral and Central devices in the context of BLE is that peripheral devices are smaller low power devices that connecet to a more powerful device while a central device is one that you connect to, inorder to get more proccessing power.

3. What is GATT in BLE, and how does it structure data exchange between connected
devices? Provide definitions for the following: Profile, Service, and Characteristic.

4. What is an advertising packet in BLE and what information can it contain?

An advertising packet is a signal that tells other devices that it is able to be connected to, it contains the advertising data.

5. What is a UUID used for in BLE and why are 128-bit UUIDs used? You can use this
page as a reference.

6. What bit from which register determines if the UART data is received or transmitted
MSB or LSB first? Refer to the eUSCI_A UART Registers section (24.4) of the
MSP432P4xx Technical Reference Manual (SLAU356I)

The 13th bit, UCMSB, from the UCAxCTLW0 register determines if the UART data is recieved or transmitted MSB or LSB first. If this bit is set it is MSB first, else it is LSB first.

7. rovide the mnemonic and primary module function for each pin listed. Refer to
Table 6-45 (Default Mapping) on page 126 of the MSP432P401R Datasheet.  

8. Write a void function named P2_2_and_P2_3_Init that takes no arguments and
configures the following pins to use primary function mode: P2.2 and P2.3. It is not
necessary to set the direction of the pins. Refer to the following documents:
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

## Known Issues or Limitations
No known issues or limitations.

## Author Contribution
* Michael Sanchez
    * 
    * 
* Gil Gandionco 
    * 
    * 
## References

* MSP432P4xx SimpleLink™ Microcontrollers
Technical Reference Manual
