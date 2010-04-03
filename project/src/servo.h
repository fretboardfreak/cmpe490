#ifndef SERVO
#define SERVO

#include <stdlib.h>
#include <string.h>

#include "parts/m55800/lib_m55800.h"
#include "drivers/capture/capture.h"
#include "drivers/wait/wait.h"
#include "parts/m55800/eb55.h"
#include "periph/timer_counter/lib_tc.h"

#define FIRE 0x79E
#define COCK 0x41A
#define SERVO_PERIOD 0x4E20

void servoInit(void);

void fire(void);

#endif

