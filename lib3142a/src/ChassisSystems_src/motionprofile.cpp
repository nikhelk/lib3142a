#include "ChassisSystems/motionprofile.h"
#include <cmath>
#include <string>

/**
 * Initilizes TrapezoidalMotionProfile with constraints
 *
 * We use a trapezoidal motion profile generator for our 1D motion generator
 *
 * The user inputs wheel velcoity constraints and a distance to travelled
 *
 * Using kinematic formulas, we are able to find the position, acceleration and
 * most importantly the velocity at every timestep in the motio
 *
 * @param maxVel max Velocity
 * @param maxAcc max acceleration
 * @param distance desired distance
 */
TrapezoidalMotionProfile::TrapezoidalMotionProfile(const double maxVel,
                                                   const double maxAcc,
                                                   const double distanceTotal)
    : m_distanceTotal(distanceTotal), m_maxVel(maxVel), m_maxAcc(maxAcc) {

  m_accelTime = m_maxVel / m_maxAcc;

  m_decelTime = m_maxVel / m_maxAcc;

  m_distanceAccel = .5 * m_accelTime * m_maxVel;

  m_distanceDecel = .5 * m_decelTime * maxVel;

  m_distanceCoast = m_distanceTotal - (2 * m_distanceAccel);

  m_coastTime = m_distanceCoast / maxVel;

  if (m_distanceCoast < 0) {

    m_accelTime = sqrt(m_distanceTotal / m_maxAcc);

    m_decelTime = sqrt(m_distanceTotal / m_maxAcc);

    m_distanceCoast = 0;

    m_distanceAccel = m_distanceDecel = m_distanceTotal / 2;
    m_coastTime = 0;
  }

  m_totalTime = m_accelTime + m_coastTime + m_decelTime;
}

double TrapezoidalMotionProfile::calculateMpVelocity(const double t) const {

  if (t < m_accelTime) {
    return (t * m_maxAcc);
  } else if (t > m_accelTime && t < (m_accelTime + m_coastTime)) {
    return (m_maxVel);
  } else if (t > m_accelTime + m_coastTime && t < m_totalTime) {
    return ((m_totalTime - t) * m_maxAcc);
  }
  return 0;
}

double TrapezoidalMotionProfile::calculateMpAcceleration(const double t) const {

  if (t < m_accelTime) {
    return (m_maxAcc);
  } else if (t > m_accelTime && t < (m_accelTime + m_coastTime)) {
    return (0);
  } else if (t > m_accelTime + m_coastTime && t < m_totalTime) {
    return (m_maxAcc * -1);
  }
  return 0;
}

std::string TrapezoidalMotionProfile::getMpStatus(const double t) const {

  if (t < m_accelTime) {
    return ("accelerating");
  } else if (t > m_accelTime && t < m_accelTime + m_coastTime) {
    return ("coasting");
  } else if (t > m_accelTime + m_coastTime && t < m_totalTime) {
    return ("decelerating");
  }
  return ("done");
}

Feedfoward::Feedfoward(double kV, double kA) {
  this->kV = kV;
  this->kA = kA;
}