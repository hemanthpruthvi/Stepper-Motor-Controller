# Generic Stepper Motor Controller for Multi-Axis Motion
The project describes a simple and complete solution to multi-axis motion control using generic stepper-motor based mounts with off-the-shelf motor drives. The hardware system looks like:  

Motion controller &rarr; Stepper motor drive &rarr; Motorized rotation/translation stage

The motion controller has two aspects:  
1. Hardware: design files for dsPIC micro-controller based custom board
2. Firmware: embedded-C program that implements the motion controls

## Hardware
The central element is a dsPIC micro-controller with two UART ports and several I/O ports that enable control of upto 3 drives at a time by sending correspinding pulse trains (drive IDs 1-3). Up to three of such motion controllers can be connected in daisy chain thus being able to control upto nine drives (drive IDs 1-9). The number of daisy chains is only a firmware limitation due to how the drives are numbered. A better numbering scheme should allow for more expansion.

The directory `Hardware` contains the design files. Hardware circuitry is designed using `KiCAD` program. The final `GERBER` file should be enough to produce the custom printed circuit boards.

## Firmware
The firmware is programmed in Embedded-C using `MPLABX IDE` with a header that is specific to the micro-controller of choice. The directory `Firmware` contains the source code as well as the compiled output. The firmware is written into the hardware using `PIKIT 3` programmer tool. The `HEX` file to be written to hardware is located at`<firmware directory>/dist/default/Production`. 