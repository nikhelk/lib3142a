#pragma once

#include "Util/vex.h"

namespace math3142a {
/**
 * Determnies whether a number is negative or positive
 * @param num number to be determined
 * @return -1 if negative, 1 if positive, 0 if 0
 */
int sgn(double num);


/**
 * Determnies cosine of value in degrees
 * @param value ( in degrees)
 * @return cosine of value 
 */

double cosDegrees(double value);

/**
 * Determnies sine of value in degrees
 * @param value ( in degrees)
 * @return sine of value 
 */

double sinDegrees(double value);

//coverts input degree value to radians
double toRadians(double value);

//coverts input degree value to radians
double toDegrees(double value);

class TimeoutTimer {

public:
	int m_delay;
	int m_timeout;
	int m_currentTime;


	TimeoutTimer(int delay, int timeout) : m_delay(delay), m_timeout(timeout) {

	m_currentTime = 0;
}

	void reset() {
	m_currentTime =0; 
}

};

}
