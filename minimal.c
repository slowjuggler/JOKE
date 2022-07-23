	/* Claude Shannon's Theorem #I:
	 * 
	 * (F + D) / (V + D) = B / H,  or in our case
	 * (FlightTime + DwellTime) / (EmptyTime + DwellTime) = NumberOfBalls / NumberOfHands
	 * 
	 * In the Newtons Mechanic:
	 * 
	 * HorizontalSpeed = HorizontalPath / FlightTime
	 * VerticalSpeed = sqrt(2 * g * ThrowHeight)
	 * ThrowHeight = VerticalSpeed^2 / (2 * g)
	 * 
	 * Due to throws and catches lies on the same heigth we have
	 * 
	 * FlightTime = sqrt(8 * ThrowHeight / g)
	 * VerticalSpeed = g * FlightTime / 2
	 * ThrowHeight = g * FlightTime^2 / 2
	 * 
	 * Theorem #II
	 * 
	 * If NumberOfBalls and NumberOfHands are relatively prime then there is
	 * essentially a unique uniform juggle.
	 * 
	 * Theorem #III
	 * 
	 * If NumberOfBalls and NumberOfHands are relatively prime and N is their
	 * greatest common divisor then 
	 * 
	 * NumberOfBalls = N * P and
	 * NumberOfHands = N * Q, where P and Q are relatively prime.
	 * 
	 * In this microcode, we'll try to estimate the minimum throw height for juggling n (NumberOfBalls),
	 * below which, due to biomechanics, we are no longer able to throw. This will also show us the 
	 * ultimate juggling speed. For convenience, we introduce a couple of new variables.
	 * 
	 * R = DwellTime / (DwellTime + EmptyTime) and
	 * Y = (NumberOfBalls - k) / NumberOfArches
	 * 
	 * Where R is delay ratio or that part of time during which the hand holds the ball.
	 * Y shows us how many balls are currently located on each arc of parabola (in 'cascade' case). 
	 * For 3 balls it is 0.5 (because one ball in each hand => k = 2 and one in the air)
	 * So Y can also be defined as equal to part of time the balls are in flight
	 *  
	 * Y = FlightTime / (DwellTime + EmptyTime)
	 * 
	 * It is easy to see that k varies from 0 (flash) to 2 (one ball in each hand).
	 * As first aproximation, we will consider the juggler to be ideal, that is, at any given time, 
	 * he has only one ball in one of his hands.
	 * 
	 * Then
	 * R + Y = NumberOfBalls / NumberOfHands
	 * 
	 * And this equation will be used to find the limit height
	 * 
	 * The time of holding the ball in the hand will vary from 150 to 300 milliseconds.
	 * As we'll see, this is enough, since this time is limited by the inertia of the levers and the weight
	 * of the balls (it is hardly possible for a person to move his hands from the catch position to the 
	 * throw position for a sufficiently long time in less than 150 milliseconds).
	 * On the other hand, if the holding time is too long (meaning that the balls are thrown to a greater height),
	 * then this affects the accuracy of the throws. That is, the range of 150 - 300 milliseconds is more than
	 * sufficient for us.
	 *     
	 */
	 
#include <stdio.h>
#include <math.h>

#define EPS 0.01

int main() {
    const double g = 9.81;
    double NumberOfBalls; 
    const double NumberOfHands = 2.0;
    const double NumberOfArches = 2.0;
    double MaxDwell;
    double ThrowHeight;
    double DwellTime = 0;
    double Rmin;
    for (MaxDwell = 0.150; MaxDwell <= 0.3; MaxDwell += 0.05) {
	printf("Maximal hold time is : %.3f sec\n", MaxDwell);
	for (NumberOfBalls = 3; NumberOfBalls < 16; NumberOfBalls += 2) {
	    for (ThrowHeight = 0.1; ThrowHeight <= 25.0; ThrowHeight += 0.01) {
		Rmin = NumberOfBalls / NumberOfHands - (NumberOfBalls - 1.0) / NumberOfArches;
		DwellTime = (sqrt(8 * ThrowHeight / g) * Rmin) / (NumberOfBalls / NumberOfHands - Rmin);
		if ((DwellTime - MaxDwell) <= EPS && (DwellTime - MaxDwell) >= 0) {
		    printf("\tNumber of balls = %2.f | Minimal throw height = %.2f m\n", NumberOfBalls, ThrowHeight);
		    break;
		}
	    }
	}
    }
    return 0;
}
