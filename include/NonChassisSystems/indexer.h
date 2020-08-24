#pragma once
#include "Util/vex.h"
#include "Config/other-config.h"
#include "Config/chassis-config.h"
#include "Impl/goal.h"
using namespace vex;
int indexerTask();
void stopIndexerTask(task taskID);
extern bool IndexerStopWhenTopDetected;
extern bool IndexerStopWhenMiddleDetected;
extern bool IndexerStopWhenBottomDetected;
extern bool IndexerRunContinuously;