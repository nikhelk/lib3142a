#include "ChassisSystems/chassisGlobals.h"

using namespace vex;

extern Tracking poseTracker;
extern FourMotorDrive testchassis;
extern FourMotorDrive chassis;

// VEXcode devices
extern encoder testEncoder;
extern line intakeDetect;
extern brain Brain;


/**
 * Used to initialize code/tasks/devices of the chassis
 */
void initChassis(void);
