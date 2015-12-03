#include <stdio.h>
#include <string.h>
#include "stm32f4xx.h"
#include "stm32f4xx_conf.h"
#include "stm32f429i_discovery.h"
#include "stm32f429i_discovery_lcd.h"
#include <math.h>

#define Y_MIN 5
#define Y_MAX 235
#define X_MIN 5
#define X_MAX 235

#define PI 3.1415926



typedef struct LCDPoint {
	int x;
	int y;
} LCDPoint;

typedef struct heading_pair {
	int step_count;
	float heading;
} heading_pair;

void drawTrajectory(heading_pair * pair, int length);
