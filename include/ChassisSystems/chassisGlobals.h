#pragma once
#include "Util/vex.h"
#include "ChassisSystems/posPID.h"
#include "Util/premacros.h"
#include "chassisConstraints.h"
#include <vector>
using namespace vex;
/* 
* Header file with all the global classes (motors, sensors) and other applications such as PID and Motion Profiling
*
* @author Nikhel Krishna, 3142A

*/


struct FourMotorDrive
{

  Dimensions m_chassisDimensions;
  Limits m_chassisLimits;
  
  posPID distancePID;
  posPID anglePID;
  posPID turnPID;

  double gearRatio;
  vex::gearSetting setting;

  enum backOrFront
  {
    FRONT,
    BACK,
  };

  motor leftFront;
  motor rightFront;
  motor leftBack;
  motor rightBack;

  /**
   * Initializes 4 motor drive
   * @param leftGroup vector of left motor ports (front,back)
   * @param rightGroup vector of right motor ports (front,back)
   * @param setting gear cartridge type (36:1.18:1,6:1)
   * @param gearRatio gear ratio
   * @param chassisDimensions chassis dimensions (trackWidth and wheel size)
   * @param chassisLimits chassis limits (max velocity and acceleration)
   * @param PDGains Controller chassis parameters
   */

  FourMotorDrive(std::array<int32_t,2> leftGroup,
                 std::array<int32_t,2> rightGroup,
                 vex::gearSetting setting, double gearRatio, Dimensions chassisDimensions, Limits chassisLimits, std::initializer_list<PDcontroller> PDGains);

  /**
   * Handles the reversal of motors.
   * @param LeftReverseVals boolean array of leftFront and leftBack desired reversal states
   * @param RightReverseVals boolean array of rightFront and rightBack desired reversal states
   */

  void setReverseSettings(std::vector<bool> LeftReverseVals, std::vector<bool> RightReverseVals);

  /**
   * Does a point turn based off of inertial value
   * @param angle the desired ABSOLUTE angle for the robot to turn to
   * @see posPID#posPID
   * @see posPID#calculatePower
   */

  void turnToDegreeGyro(double angle);

  /**
   * Drives the robot straight using feedforward control
   * 
   * We calculate our final motor voltage kV*velocity + kA*acceleration + kP*(desiredPos-currentPos)
   * 
   * the velocity and acceleration values are generated from the trapezoidal motion profile described in motionprofile.h and .cpp
   * 
   * the kV and kA terms are "feedfoward" meaning they guess the pose,velocity, acceleration at a certian timestep
   * 
   * We let the kV and kA terms do the brunt of the work and have a P loop on the difference between current position and the actual desired pose ot the current time (not the final pose)
   * 
   * @param distance desired distance to travel
   * @param backwards the desired path is backwards or not
   * @see TrapezoidalMotionProfile#TrapezoidalMotionProfile
   * @see TrapezoidalMotionProfile#calculateMpVelocity
   * @see TrapezoidalMotionProfile#calculateMpAcceleration
   * @see posPID#posPID
   * @see posPID#calculatePower
   */

  void driveStraightFeedforward(const double distance, bool backwards = false);


  void normalize(double &left, double &right);


  void moveToPoint(const double x, const double y, bool backwards = false);


  void driveArcFeedforward(const double radius, const double exitAngle);

  //resets the chassis encoders to 0
  void resetPosition();

  //resets the chassis encoders to 0
  void resetRotation();


  

  /**
   * sets the chassis to drive at a voltage 
   * @param leftVoltage desired left voltage
   * @param rightVoltage desired right voltage
   */

  void setDrive(double leftVoltage, double rightVoltage);


  /**
   * sets the chassis to drive at a velocity 
   * @param leftVelocity desired left side velocity
   * @param rightVelocity desired right side velocity
   * @param units desired velocity units (rpm, dps, etc)
   */


  void setVelDrive(double leftVelocity, double rightVelocity, velocityUnits units);

  
  /**
   * gets the encoder values of the all motors (average)
   * @return the total average econder values
   */

  double getAverageEncoderValueMotors();

  /**
   * gets the encoder values of the right encoders (average)
   * @return the total average  of right econder values
   */

  double getRightEncoderValueMotors();

  /**
   * gets the encoder values of the left encoders (average)
   * @return the total average  of left encoder values
   */

  double getLeftEncoderValueMotors();


  //converts an imput meters to encoder ticks based off of gear ratio, gearbox etc.
  double convertMetersToTicks(double num_meters);

  //converts an imput ticks meters based off of gear ratio, gearbox etc.
  double convertTicksToMeters(double num_ticks);
};





struct WheelDistances
{
  double R_DISTANCE;
  double L_DISTANCE;
  double B_DISTANCE;
};

struct Tracking
{

  enum trackingWheelID
  {
    LEFT_ENCODER,
    RIGHT_ENCODER,
    BACK_ENCODER,
  };

  enum trackType
  {
    THREE_ENCODER_MODEL,
    IME_ENCODER_MODEL
  };

  enum triportIndex
  {
    A,
    B,
    C,
    D,
    E,
    F,
    G,
    H
  };
  brain brained;
  double trackWidth;
  double wheelRadius;
  double backDistance;
  double ticksPerRev;
  double maxVelocity;
  double maxAcceleration;
  WheelDistances m_odomImpl;
  encoder rightEncoder;
  encoder leftEncoder;
  encoder backEncoder;
  inertial inert;

  /**
     * Constructor for 3 encoder model
     * @param trackWidth of encoder model
     * @param distance from tracking center to the back encoder
     * @param encoder wheel radius
     * @param encoder ticks per revolution
     * @param list of triports (in order of left, right, back)
     * @param gyroport (if any)
     */

  Tracking(WheelDistances wheels, double wheelRadius, std::vector<triportIndex> enocoderPorts, int GyroPort = NULL, double ticksPerRev = 360.0);

  /**
     * Constructor for 2 IME  and one backEncoder model
     * @param trackWidth of encoder model
     * @param distance from tracking center to the back encoder
     * @param encoder wheel radius
     * @param encoder ticks per revolution
     * @param list of triports (in order of left, right, back)
     * @param gyroport (if any)
     */

  Tracking(FourMotorDrive drive, triportIndex backPort, int GyroPort = NULL);

  Tracking(FourMotorDrive drive, int GyroPort = NULL);
  /**
   * returns "fixed" inertial value
   * @return intertial value
   */

  double getInertialHeading();

  double getAverageEncoderValueEncoders();
};

