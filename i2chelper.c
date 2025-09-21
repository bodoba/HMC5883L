/* *********************************************************************************** */
/*  Some routines to help with I2C handling in a similar was as in                     */
/*  Jeff Rowberg’s I2Cdev implementation                                               */
/* *********************************************************************************** */
/*                                                                                     */
/*  Copyright 2025 by Bodo Bauer <bb@bb-zone.com>                                      */
/*                                                                                     */
/*  This program is free software: you can redistribute it and/or modify               */
/*  it under the terms of the GNU General Public License as published by               */
/*  the Free Software Foundation, either version 3 of the License, or                  */
/*  (at your option) any later version.                                                */
/*                                                                                     */
/*  This program is distributed in the hope that it will be useful,                    */
/*  but WITHOUT ANY WARRANTY; without even the implied warranty of                     */
/*  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the                      */
/*  GNU General Public License for more details.                                       */
/*                                                                                     */
/*  You should have received a copy of the GNU General Public License                  */
/*  along with this program.  If not, see <http://www.gnu.org/licenses/>.              */
/* *********************************************************************************** */
#include <stdint.h>
#include "i2chelper.h"

#include <wiringPi.h>
#include <wiringPiI2C.h>

int i2cReadBits(int fd, uint8_t regAddr, uint8_t bitStart, uint8_t length) {
    // Read one byte from device register
    int b = wiringPiI2CReadReg8(fd, regAddr);
    if (b < 0) return -1; // error

    uint8_t byte = (uint8_t)b;

    // Mask for desired bits
    uint8_t mask = ((1 << length) - 1);

    // Shift down and mask
    return (byte >> (bitStart - length + 1)) & mask;
}

int i2cWriteBits(int fd, uint8_t regAddr, uint8_t bitStart, uint8_t length, uint8_t value) {
    int b = wiringPiI2CReadReg8(fd, regAddr);
    if (b < 0) return -1; // read error

    uint8_t byte = (uint8_t)b;

    // Create mask for the bits we want to update
    uint8_t mask = ((1 << length) - 1) << (bitStart - length + 1);

    // Shift new value into position
    value <<= (bitStart - length + 1);

    // Clear target bits in original byte, insert new bits
    byte = (byte & ~mask) | (value & mask);

    // Write back to device
    if (wiringPiI2CWriteReg8(fd, regAddr, byte) < 0) return -1;

    return 0;
}

int i2cReadBytes(int fd, uint8_t regAddr, uint8_t length, uint8_t *data) {
    for (int i = 0; i < length; i++) {
        int b = wiringPiI2CReadReg8(fd, regAddr + i);
        if (b < 0) {
            return -1; // error
        }
        data[i] = (uint8_t)b;
    }
    return length;
}

int i2cWriteBytes(int fd, uint8_t regAddr, uint8_t length, const uint8_t *data) {
    for (int i = 0; i < length; i++) {
        int result = wiringPiI2CWriteReg8(fd, regAddr + i, data[i]);
        if (result < 0) {
            return -1; // error
        }
    }
    return 0;
}