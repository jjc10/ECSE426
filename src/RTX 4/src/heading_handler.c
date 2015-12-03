#include "initialization.h"

float gyro_frequency = 238; //HZ
float mD_to_D = 1000;	
float heading = 0;
int getHeading(float gyro_data){
		heading = heading + (gyro_data / (mD_to_D * gyro_frequency)); 
	  int res = normalizeAngle(heading);
		return res;
}

int normalizeAngle(float angle1) {
	int angle = (int) angle1;
	if (abs(angle) > 360) {
		angle = angle - (angle / 360 * 360);
	}
	if (angle < 0) {
		angle = angle + 360;
	}
	return getFixedHeading45(angle);
}

//int roundAngle(int angle, int step) {
//	int res = 0;
//	int mod = angle % step;
//	if (mod > (step / 2)) {
//		res = (angle / step) * step + step;
//	}
//	else {
//		res = (angle / step) * step;
//	}
//	return res;
//}

int getFixedHeading30(int a) {
	if (a <= 15 || a > 345 ) {
		return 0;
	}
	if (a > 15 && a <= 45) {
		return 30;
	}
	if (a > 45 && a <= 75) {
		return 60;
	}
	if(a > 75 && a <= 105){
		return 90;
	}
	if (a > 105 && a <= 135) {
		return 120;
	}
	if (a > 135 && a <= 165) {
		return 150;
	}
	if (a > 165 && a <= 195) {
		return 180;
	}
	if (a > 195 && a <= 225) {
		return 210;
	}
	if (a > 225 && a <= 255) {
		return 240;
	}
	if (a > 255 && a <= 285) {
		return 270;
	}
	if (a > 285 && a <= 315) {
		return 300;
	}
	if (a > 315 && a <= 345) {
		return 330;
	}
}

int getFixedHeading45(int a) {
	if (a <= 22.5 || a > 337.5) {
		return 0;
	}
	if (a > 22.5 && a <= 67.5) {
		return 45;
	}
	if (a > 67.5 && a <= 112.5) {
		return 90;
	}
	if (a > 112.5 && a <= 157.5) {
		return 135;
	}
	if (a > 157.5 && a <= 202.5) {
		return 180;
	}
	if (a > 202.5 && a <= 247.5) {
		return 225;
	}
	if (a > 247.5 && a <= 292.5) {
		return 270;
	}
	if (a > 292.5 && a <= 337.5) {
		return 315;
	}
}