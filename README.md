# AM2302 Temperature and Relative Humidity Sensor Driver for ARM
This is the C code to drive the Amsong AM2302 temperature and humidity sensor throuh it's single wire interface.
* The code is targeting an ARM ST32F100RB Cortex-M 3 ARM Microprocessor. It should be portable.
* The demo project is working on STs M0 Discovery Board
* It is interrupt driven, you tell the library to start acquisition, then for the value, not blocking your main.
* It tries not to couple to the ST peripherics library or CMSIS, so there are intermediate abstractions for the interrupt setup, GPIO, and timer.
* I am using a gnu toolchain (gcc, ld, as) and texane's stlink utility to upload the firmware via ST-Link v1 protocol.

## ATENTION: This is work in progress!
The code is working properly but it needs further testing
