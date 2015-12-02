#include "initialization.h"

step_states step_state = high;
int high_count = 0;
int low_count = 0;
int zero_count = 0;

int high_count_threshold = 30;
int low_count_threshold = 30;
int zero_count_threshold = 30;

int high_threshold = 60000;
int low_threshold = -60000;
int zero_threshold = 8000;

int number_of_steps = -1;

int observations[40];
int obs_count = 0;

void updateStepState(float gyro_y){
		switch ( step_state ){
				
				/* Initialization state */
				case zero : {
					if(gyro_y >= high_threshold){
						high_count++;
						if (high_count >= high_count_threshold) {
							step_state = high;
							high_count = 0;
							low_count = 0;
							zero_count = 0;
							printf("High\n");
							printf("OBS COUNT %d\n", obs_count);
							observations[obs_count] = high;
							obs_count++;
						}
					}
					break;
				}
				case high : {
					if(gyro_y <= low_threshold){
						low_count++;
						if (low_count >= low_count_threshold) {
							step_state = low;
							high_count = 0;
							low_count = 0;
							zero_count = 0;
							printf("Low\n");
							observations[obs_count] = low;
							printf("OBS COUNT %d\n", obs_count);
							obs_count++;
						}
					}
					else if(fabs(gyro_y) <= zero_threshold){
						zero_count++;
						if (zero_count >= zero_count_threshold) {
							step_state = zero;
							high_count = 0;
							low_count = 0;
							zero_count = 0;
							printf("Zero\n");
							observations[obs_count] = zero;
							printf("OBS COUNT %d\n", obs_count);
							obs_count++;
							number_of_steps++;
						}
					}
					break;
				}
				case low :{
					if(gyro_y >= high_threshold){
						high_count++;
						if (high_count >= high_count_threshold) {
							step_state = high;
							high_count = 0;
							low_count = 0;
							zero_count = 0;
							printf("High\n");
							observations[obs_count] = high;
							printf("OBS COUNT %d\n", obs_count);
							obs_count++;
						}
					}
					break;
				}
			}
}

int getNumberOfSteps(){
	return number_of_steps;
}

void resetNumberOfSteps(){
	number_of_steps = 0;
}