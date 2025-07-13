#pragma once

/*

Angle class library
===================
v0.0

by Bryan Shortall

EngineerShorty@email.com

This library will allow the programmer to easily work with angles, using the Angle class.

Angles


*/

#include <cmath>
#include <string>

#define ANGLE_H_LIBRARY

using std::string;

//This enum allows you to tell angles what units (degrees vs radians) you're using.
//You can select DEGREES, RADIANS, or REVOLUTIONS.  REVOLUTIONS will give a decimal
//representation of the number of revolutions (e.g. 450 DEGREES == 1.25 REVOLUTIONS)
enum AngleUnits {
	DEGREES, 
	RADIANS, 
	REVOLUTIONS
};


//the value of the angle is always stored in Degrees.
//this was decided for several reasons:
//	-	whenever humans want talk about the size of the angle, it's almost always more intuitive to see it  
//		or enter it in degrees
//	-	in degrees, 360 deg == 1 rev.  With radians, 6.28318530718 rads != 1 rev...  we have some rounding 
//		to account for.  It seems more precise to talk in degrees, due to the inability to accurately represent PI
//	-	This will cost 1 extra multiplication step for conversion when performing trig functions, but that seems 
//		worth the accuracy
//	-	REVOLUTIONS was added later, so it wasn't originally considered
const AngleUnits BASE_UNITS = AngleUnits::DEGREES;

//CONSTANTS (mainly for conversions)
const double PI = 3.141592653589793;
const double DEGREES_PER_REV = 360;
const double DEGREES_HALF_REV = DEGREES_PER_REV / 2;
const double RADIANS_PER_REV = 2 * PI;
const double RADIANS_PER_DEGREE = PI / DEGREES_HALF_REV;
const double DEGREES_PER_RADIAN = DEGREES_HALF_REV / PI;


class Angle {
public:
	//default constructor starts with angle 0
	Angle();
	//initialize the angle in the given units
	Angle(double value, AngleUnits units);
	//set the value of the angle in the input units
	void set(double value, AngleUnits units);
	//add the value in the default units
	Angle add(double value);
	//add the value in the specified units
	Angle add(double value, AngleUnits units);
	//add 2 angles together
	Angle add(Angle other);
	//subtract the input angle from this angle
	Angle subtract(Angle other);
	//return whether the two angles are equal.
	//trivial example: 90deg == 90deg
	//less trivial: 270deg == -450deg
	bool equals(Angle other);
	//flips the angle from the positive to negative direction or vice-versa
	//example: 45 degrees becomes -315 degrees
	//example2: -435 degrees becomes 285 degrees
	Angle flipDirection();
	//return the angle in the opposite direction (will be between -180 and 180)
	Angle reverse();
	//return the perpendicular angle in the positive direction
	Angle perpendicular_positive();
	//return the perpendicular angle in the negative direction
	Angle perpendicular_negative();

	//returns the value of the angle in the Default_Angle_Units
	double value();
	//returns the value of the angle in the given units
	double value(AngleUnits units);
	//return the value in a string showing degrees minutes seconds (e.g. 43° 34' 21.45")
	string value_degsMinsSecs();
	//the number of full revolutions
	int revolutions();
	//the final angle after all the full revolutions are removed, keeping the original sign
	//example: 630 degrees -> 270 degrees
	//example: -630 degrees -> -270 degrees
	//basically just strips away the full revs
	Angle finalAngle();
	//return the final angle (all revolutions removed) and measures the angle in the positive direction (0deg to <360deg)
	//example: -450deg -> 270deg
	Angle final_positive();
	//return the final angle (all revolutions removed) and measures the angle in the negative direction (0deg to >-360deg)
	//example: 450deg -> -270deg
	Angle final_negative();
	//the final angle (all full revolutions removed) and measures the angle in the negative direction (will be >-180deg to 180deg)
	//useful for understanding which direction (+/-) to go
	//example: -630deg -> 90deg
	Angle final_closerDirection();
	//return whether it's closer to go in the positive direction to get to the other angle
	bool closerPositive(Angle other);
	//return whether it's closer to go in the negative direction to get to the other angle
	bool closerNegative(Angle other);
	//divide the angle by the denominator
	Angle divideBy(double denominator);
	//divide the angle by another angle
	double divideBy(Angle other);
	//multiply the angle by a number
	Angle multiplyBy(double multiplier);

	double sin();
	double cos();
	double tan();

	Angle operator+(Angle other);
	Angle operator-(Angle other);
	Angle operator-();
	//returns true if the angles are equivalent (point in the same direction)
	// e.g. 270 == -90 ; 630 == -90
	bool operator==(Angle other);
	//returns false if the two angles point in the same direction
	bool operator!=(Angle other);
	//returns whether the second angle is strictly greater than the first
	bool operator>(Angle other);
	//returns whether the second angle is strictly less than the first
	bool operator<(Angle other);
	//returns whether the second angle's final position is closer in the positive direction
	bool operator>=(Angle other);
	//returns whether the second angle's final position is closer in the negative direction
	bool operator<=(Angle other);
	//returns the angle 180 degrees from this angle
	Angle operator!();
	//multiply the angle by the number provided
	Angle operator*(double multiplier);
	//divide the angle by the number provided
	Angle operator/(double denominator);
	//divide the angle by another angle
	double operator/(Angle other);

protected:
	//the value of the angle is always stored in Degrees.
	//this was decided for several reasons:
	//	-	whenever humans want talk about the size of the angle, it's almost always more intuitive to see it  
	//		or enter it in degrees
	//	-	in degrees, 360 deg == 1 rev.  With radians, 6.28318530718 rads != 1 rev...  we have some rounding 
	//		to account for.  It seems more precise to talk in degrees, due to the inability to accurately represent PI
	//	-	This will cost 1 extra multiplication step for conversion when performing trig functions, but that seems 
	//		worth the accuracy
	//	-	REVOLUTIONS was added later, so it wasn't originally considered
	double valueDeg; 
};

//convert the value from the first units to the second units
extern double convertAngleUnits(double value, AngleUnits inputUnits, AngleUnits outputUnits);

//angle formed by the line segment leading to that point
extern Angle angleToCoordinate(double x, double y);

//angle (from -90 to 90) with the input sine value
//angle could also be 180 - this value
Angle arcsin(double sine);
//angle (from -90 to 90) with the input cosine value
//angle could also be 0 - this value
Angle arccos(double cosine);
//angle formed by a triangle with opposite and adjacent side lengths
Angle arctan(double opposite, double adjacent);
//angle (from -90 to 90) with the input tangent value
//angle could also be 180 + this value
Angle arctan(double tangent);

//ANGLE CONSTANTS

//constant for full, 360-degree angle
const Angle FULL_REV_ANGLE(DEGREES_PER_REV, AngleUnits::DEGREES);
//constant for half revolution, 180 degree angle
const Angle HALF_REV_ANGLE(DEGREES_HALF_REV, AngleUnits::DEGREES);
//constant for 90-degree angle
const Angle PERPENDICULAR_ANGLE(DEGREES_HALF_REV / 2, AngleUnits::DEGREES);