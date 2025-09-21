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
#ifndef I2CHELPER_H
#define I2CHELPER_H

#include <stdint.h>

/* *********************************************************************************** *
 * @brief Reads bits from an 8-bit device register over I2C
 * @param fd        file descriptor from wiringPiI2CSetup()
 * @param regAddr   register address to read from
 * @param bitStart  index of first bit (7 = MSB, 0 = LSB)
 * @param length    number of bits to read
 * @return          extracted bits, right aligned
 * *********************************************************************************** */
int i2cReadBits(int fd, uint8_t regAddr, uint8_t bitStart, uint8_t length);

/* *********************************************************************************** *
 * @brief Write multiple bits in an 8-bit device register over I2C
 * @param fd        file descriptor from wiringPiI2CSetup()
 * @param regAddr   register address to read from
 * @param bitStart  index of first bit (7 = MSB, 0 = LSB)
 * @param length    number of bits to read
 * @param value     new value for those bits (right aligned)
 * @return          0 on success, -1 on error
 * *********************************************************************************** */
int i2cWriteBits(int fd, uint8_t regAddr, uint8_t bitStart, uint8_t length, uint8_t value);

/* *********************************************************************************** *
 * @brief Reads multiple consecutive bytes starting at regAddr
 * @param fd       wiringPi file descriptor
 * @param regAddr  starting register address
 * @param length   number of bytes to read
 * @param data     pointer to output buffer
 * @return         number of bytes read, or -1 on error
 * *********************************************************************************** */
 int i2cReadBytes(int fd, uint8_t regAddr, uint8_t length, uint8_t *data);

/* *********************************************************************************** *
 * @brief Writes multiple consecutive bytes starting at regAddr
 * @param fd       wiringPi file descriptor
 * @param regAddr  starting register address
 * @param length   number of bytes to write
 * @param data     pointer to buffer with bytes to send
 * @return         0 on success, -1 on error
 * *********************************************************************************** */
 int i2cWriteBytes(int fd, uint8_t regAddr, uint8_t length, const uint8_t *data);

#endif