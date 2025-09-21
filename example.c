//
// I2C device class (I2Cdev) demonstration Arduino sketch for HMC5883L class
// 10/7/2011 by Jeff Rowberg <jeff@rowberg.net>
// Updates should (hopefully) always be available at https://github.com/jrowberg/i2cdevlib
//
// Changelog:
//     2025-09-22 - Ported Jeff's code to plain C with wiringPi backend
//     2013-05-04 - Added Heading Calculation in degrees
//     2011-10-07 - initial release

/* ============================================
I2Cdev device library code is placed under the MIT license
Copyright (c) 2011 Jeff Rowberg

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
===============================================
*/
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <math.h>

#include <wiringPi.h>
#include "hmc5883l.h"

int main ( int argc, char** argv ) {

    // initialize the hmc5883l sensor
    hmc5883lInit();

    // test the connection and bail out if it fails
    if ( hmc5883lTestConnection() ) {
        printf("HMC5883L connection successful\n");    
    } else { 
        printf("HMC5883L connection failed\n");
        exit(-1);
    }

    // show readings in an infinite loop
    while(true) {
        int16_t mx, my, mz;

        // get raw readings
        hmc5883lGetHeading(&mx, &my, &mz);

        // calculate heading
        float heading = atan2(my, mx);

        if(heading < 0)
            heading += 2 * M_PI;
        
        // show results
        printf("(X/Y/Z): % 4d/% 4d/% 4d\t Angle: Rad % 5.3f\tDeg % 8.3f\n", mx, my, mz, 
            heading,
            heading * 180/M_PI);
        
        // rest
        delay(500);
    }

    return 0;
}