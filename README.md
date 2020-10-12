# lib3142a


Hello! We are team 3142A from Atlanta, Georgia and this is our code for the VEX Robotics Competition 2020-2021 game: Change Up.

This is our sumbission for the Annotated Programming Skills Challenge

1. [ File System. ](#fileSys)
2. [ Resources. ](#resources)


<a name="fileSys"></a>
## File System ##

###  Base files ###


### Utilities ###

 - `include/Util/vex.h` includes stdlib libraries and vex sdk 
 - `include/Util/literals.h` + `src/Util_src/literals.cpp` literal implementation
 - `include/Util/mathAndConstants.h` + `src/Util_src/mathAndConstants.cpp` math helper functions

### Chassis Systems ###

 - `include/ChassisSystems/ChassisGlobals.h` + `src/ChassisSystems_src/ChassisGlobals.cpp` contains custom wrapper library for drive and tracking systems
 - `include/ChassisSystems/ChassisGlobals.h` + `src/ChassisStystems_src/chassisfunctions.cpp` contains drive functions
 - `include/ChassisSystems/posPID.h` + `src/ChassisSystems_src/posPID.cpp` functions for position PID
 - `include/ChassisSystems/motionprofile.h` + `src/ChassisSystems_src/motionprofile.cpp` Library for motion profile and feedforward commands
 - `include/ChassisSystems/odometry.h` + `src/ChassisSystems_src/odometry.cpp` Robot odometry implementation
 
 
### Brain Screen Selector ###

 - `include/Selector/selectorAPI.h` + `include/Selector_src/selectorAPI.cpp` wrapper library for selector buttons
 - `include/Selector/selectorImpl.h` + `include/Selector_src/selectorImpl.cpp` Implmentation of selector library 
 
<a name = "resources"></a>
## Resources


