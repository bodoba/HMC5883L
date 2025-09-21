# Support for HMC5883L compass sensor with Wiring Pi in plain C

This is an adoption of the HMC5883L class of the [I2C device library](https://github.com/jrowberg/i2cdevlib/tree/master) to be used in plain C with the [wiring Pi library](https://github.com/WiringPi/WiringPi) as backend.

Usage is straight forward:

```C
#include <wiringPi.h>
#include "hmc5883l.h"

int main(int argc, char** argv) {

    // initialize the hmc5883l sensor
    hmc5883lInit();

    // test the connection and bail out if it fails
    if (hmc5883lTestConnection()) {
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
```

This will show the current heading in 0.5s intervals:

```bash
pi@raspberrypi:~/hmc5883l/build $ ./hmc5883l
HMC5883L connection successful
(X/Y/Z):  154/  27/-344	 Angle: Rad  0.174	Deg    9.944
(X/Y/Z):  153/  19/-345	 Angle: Rad  0.124	Deg    7.079
(X/Y/Z):  154/  20/-345	 Angle: Rad  0.129	Deg    7.400
(X/Y/Z):  156/  20/-344	 Angle: Rad  0.128	Deg    7.306
(X/Y/Z):  153/  19/-345	 Angle: Rad  0.124	Deg    7.079
(X/Y/Z):  118/  51/-341	 Angle: Rad  0.408	Deg   23.374
(X/Y/Z):   33/  78/-340	 Angle: Rad  1.171	Deg   67.068
(X/Y/Z):  -24/  83/-339	 Angle: Rad  1.852	Deg  106.128
(X/Y/Z):  -62/  73/-339	 Angle: Rad  2.275	Deg  130.342
(X/Y/Z): -107/  53/-341	 Angle: Rad  2.682	Deg  153.650
(X/Y/Z): -133/  35/-341	 Angle: Rad  2.884	Deg  165.256

```

The `i2chelper` functions reassemble some convenience methods from `I2Cdev` and are used internally.
