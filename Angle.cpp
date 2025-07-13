#include "Angle.h"

//This controls the default units that will be assumed when talking to your Angles if you don't specify a unit.
//DEGREES is used by default.
//This value can be changed back and forth during your program without modifying the underling angle data.
//It can also be ignored, and you can always specify units in Angle methods.
//extern AngleUnits Default_Angle_Units = AngleUnits::DEGREES;  -- not going to use -- bad practice.  Use your units.


Angle::Angle() {
	Angle(0, DEGREES);
}

Angle::Angle(double value, AngleUnits units) {
	set(value, units);
}


void Angle::set(double value, AngleUnits units) {
	valueDeg = convertAngleUnits(value, units, BASE_UNITS);
}

Angle Angle::add(double value) {
	return add(value, Default_Angle_Units);
}

Angle Angle::add(double value, AngleUnits units) {
	Angle other(value, units);
	return add(other);
}

Angle Angle::add(Angle other) {
	return Angle(value(BASE_UNITS) + other.value(BASE_UNITS), BASE_UNITS);
}

Angle Angle::subtract(Angle other) {
	return Angle(value(BASE_UNITS) - other.value(BASE_UNITS), BASE_UNITS);
}

bool Angle::closerPositive(Angle other) {
	Angle difference = subtract(other);
	if (difference.final_closerDirection().value(BASE_UNITS) > 0) return true;
	else return false;
}

bool Angle::closerNegative(Angle other) {
	Angle difference = subtract(other);
	if (difference.final_closerDirection().value(BASE_UNITS) < 0) return true;
	else return false;
}

bool Angle::equals(Angle other) {
	if (value(BASE_UNITS) == other.value(BASE_UNITS)) return true;
	else return false;
}

Angle Angle::flipDirection() {
	if (value() > 0) {
		return final_negative();
	}
	else {
		return final_positive();
	}
}

Angle Angle::reverse() {
	Angle oppositeAngle = add(HALF_REV_ANGLE);
	return oppositeAngle.final_closerDirection();
}

Angle Angle::perpendicular_positive() {
	return add(PERPENDICULAR_ANGLE);
}

Angle Angle::perpendicular_negative() {
	return subtract(PERPENDICULAR_ANGLE);
}

Angle Angle::operator+(Angle other) {
	return add(other);
}

Angle Angle::operator-(Angle other) {
	return subtract(other);
}

Angle Angle::operator-() {
	return Angle(-valueDeg, BASE_UNITS);
}

bool Angle::operator==(Angle other) {
	return equals(other);
}

bool Angle::operator!=(Angle other) {
	return (!equals(other));
}

bool Angle::operator>(Angle other) {
	return (value(BASE_UNITS) > value(BASE_UNITS));
}

bool Angle::operator<(Angle other) {
	return (value(BASE_UNITS) < other.value(BASE_UNITS));
}

bool Angle::operator>=(Angle other) {
	return closerPositive(other);
}

bool Angle::operator<=(Angle other) {
	return closerNegative(other);
}

Angle Angle::operator!() {
	return reverse();
}

Angle Angle::operator*(double multiplier) {
	return multiplyBy(multiplier);
}

Angle Angle::operator/(double denominator) {
	return divideBy(denominator);
}

double Angle::operator/(Angle other) {
	return divideBy(other);
}

//double Angle::value() {
//	return value(Default_Angle_Units);
//}

double Angle::value(AngleUnits units) {
	return convertAngleUnits(valueDeg, BASE_UNITS, units);
}

string Angle::value_degsMinsSecs() {
	int degs;
	int mins;
	double secs;
	degs = value(DEGREES);
	mins = value(DEGREES) * 60 - degs * 60;
	secs = value(DEGREES) * 3600 - degs * 3600 - mins * 60;
	string output = std::to_string(degs);
	char degreeSign = 167;
	output.append(std::to_string(degreeSign));
	output.append(" ");
	output.append(std::to_string(mins));
	output.append("\' ");
	output.append(std::to_string(secs));
	output.append("\"");
	return output;
}

Angle Angle::finalAngle() {
	Angle fullRevs(revolutions(), AngleUnits::REVOLUTIONS);
	return subtract(fullRevs);
}

Angle Angle::final_closerDirection() {
	Angle output = final_positive();
	if (output.value(AngleUnits::DEGREES) > DEGREES_HALF_REV) {
		output.subtract(HALF_REV_ANGLE);
	}
	return output;
}

Angle Angle::final_positive() {
	Angle final = finalAngle();
	if (final.value(BASE_UNITS) < 0) {
		final = final + FULL_REV_ANGLE;
	}
	return final;
}

Angle Angle::final_negative() {
	Angle final = finalAngle();
	if (final.value(BASE_UNITS) > 0) {
		final = final - FULL_REV_ANGLE;
	}
	return final;
}

int Angle::revolutions() {
	int revs;
	revs = (int)convertAngleUnits(value(BASE_UNITS), BASE_UNITS, AngleUnits::REVOLUTIONS);
	return revs;
}

Angle Angle::divideBy(double denominator) {
	return Angle(value(BASE_UNITS) / denominator, BASE_UNITS);
}

//divide the angle by another angle

inline double Angle::divideBy(Angle other) {
	return (value(Default_Angle_Units) / other.value(Default_Angle_Units));
}

Angle Angle::multiplyBy(double multiplier) {
	return Angle(value(BASE_UNITS) * multiplier, BASE_UNITS);
}

double Angle::sin() {
	return std::sin(value(AngleUnits::RADIANS));
}

double Angle::cos() {
	return std::cos(value(AngleUnits::RADIANS));
}

double Angle::tan() {
	return std::tan(value(AngleUnits::RADIANS));
}

double convertAngleUnits(double value, AngleUnits inputUnits, AngleUnits outputUnits) {
	//I chose to convert all to degrees first, then back out to their output units to make things neater
	//I initially did embedded switches for input and output, but realized it'll grow by the square of
	//the number of units.  This seems better.

	//step 1: just return the input for the trivial case of no conversion (same input and output units)
	if (inputUnits == outputUnits) return value;
	double input = 0; double output = 0;

	//step 2: convert the input value to degrees
	switch (inputUnits) {
	case(AngleUnits::DEGREES):
		input = value;
		break;
	case(AngleUnits::RADIANS):
		input = value * DEGREES_PER_RADIAN;
		break;
	case(AngleUnits::REVOLUTIONS):
		input = value * DEGREES_PER_REV;
		break;
	}

	//step 3: convert from degrees to the desired output units
	switch (outputUnits) {
	case(AngleUnits::DEGREES):
		output = input;
		break;
	case(AngleUnits::RADIANS):
		output = input * RADIANS_PER_DEGREE;
		break;
	case(AngleUnits::REVOLUTIONS):
		output = input / DEGREES_PER_REV;
		break;
	}

	//step 4: send the result
	return output;
}

Angle angleToCoordinate(double x, double y) {
	return arctan(y, x);
}

Angle arcsin(double sine) {
	double answer = std::asin(sine);
	Angle outputAngle(answer, RADIANS);
	return outputAngle;
}

Angle arccos(double cosine) {
	return Angle(std::acos(cosine), RADIANS);
} 

Angle arctan(double opposite, double adjacent) {
	double result = std::atan2(opposite, adjacent);
	Angle answer(result, RADIANS);
	return answer;
}

Angle arctan(double tangent) {
	return Angle(std::atan(tangent), RADIANS);
}

/*Angle::Angle(double value) {
	set(value);
}*/

/*void Angle::set(double value) {
	set(value, Default_Angle_Units);
}*/
