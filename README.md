Elijah Thomas

Experimental program inspired by (and driven by an intense desire to reverse engineer,) donut.c
Uses a basic rotation matrix and some cursor-moving escape codes to make an ASCII graphic of a radar scan.

theta:              Angle the wave is currently positioned at

LENGTH:             The amount of points to plot from the "center" to the "top" of the buffer. You should stick between 1-20.
THETA_INCR:         Radians to move theta with each iteration (clockwise).
ALT_THETA_SPACING:  Amount by which to decrement theta when drawing the other waves "behind" the first.
                    In other words, the distance in radians between each wave.
                    Set this to a fraction of pi for some interesting patterns!
