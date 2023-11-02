#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define LENGTH 15               // Radar's "range"
#define THETA_INCR 0.0005       // How many radians to add to theta per iteration
#define ALT_THETA_SPACING 0.1   // Alternate Theta Spacing; 

typedef unsigned char uchar;

int main(){
    // Varied brightness levels (same as donut.c)
    uchar* gradient = "@$#*!=;:~-,.";

    int 
        WIDTH       = LENGTH * 2 - 1,   // Width of entire board. Always an odd number.
        NZLENGTH    = LENGTH - 1,       // Length, disregarding the origin (0, 0) tile.
        AREA        = WIDTH * WIDTH,    // Area of entire board. Always odd.
        xp[LENGTH],                     // Stands for X Permanent; initial coordinates to transpose w/ "matrix"
        yp[LENGTH];                     // Y coordinate array, same rule as xp
    uchar b[AREA];                      // Actual buffer of characters to print
    float theta = 0;                    // Angle, gets incremented each iteration

    // Setup loop, define values explicitly if you'd like!
    for(uchar i = 0; i < LENGTH; i++){
        xp[i] = 0;
        yp[i] = i * -1;
    }

    // Runtime loop
    while(1){

        // Refresh the buffer pre-render
        for(int i = 0; i < AREA; i++){
            b[i] = ' ';
        }

        // Put the sweep characters in the buffer! Character selected depends on j
        for(uchar j = 0; j < 12; j++){

            // Precompute trig functions
            float 
                sint = sin(theta - j * ALT_THETA_SPACING), 
                cost = cos(theta - j * ALT_THETA_SPACING);

            // Do the actual linear algebra to transform the xp and yp coordinates according to theta.

            /*
            
                Corresponds to this matrix:

                --            --
                | cost   -sint |
                | sint    cost |
                --            --
            
            
            */
            for(uchar i = 0; i < LENGTH; i++){
                float
                    xpi = (float)xp[i],
                    ypi = (float)yp[i];
                b[
                             NZLENGTH + (int)round(xpi * cost - ypi * sint) +
                    WIDTH * (NZLENGTH + (int)round(xpi * sint + ypi * cost))
                ] = gradient[j];
            }
        }

        // Print the buffer
        printf("\x1b[H");
        for(int i = 0; i < AREA; i++){
            if((i+1)%WIDTH){
                printf("%c ", b[i]);
            }else{
                printf("%c\n", b[i]);
            }
        }

        theta = theta >= 6.28 ? 0 : theta + THETA_INCR;
    }
}