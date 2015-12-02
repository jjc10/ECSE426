#include "initialization.h"

float gyro_frequency = 238; //HZ
float mD_to_D = 1000;	
float heading = 0;
float getHeading(float gyro_data){
		heading = heading + (gyro_data / (mD_to_D * gyro_frequency)); 
		return heading;
}