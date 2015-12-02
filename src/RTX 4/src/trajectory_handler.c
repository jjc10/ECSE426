#include "initialization.h"

heading_pair trajectory [20];
int trajectory_array_i = 0;
	
trajectory_states ts;
int pair_count = 0;

float previous_heading = 0;
float heading_threshold = 30;

void addToTrajectory(float angle, int number_of_steps) {
	heading_pair new_heading_pair = {angle, number_of_steps};
	trajectory[trajectory_array_i] = new_heading_pair;
	trajectory_array_i++;
}

void updateTrajectory(float new_heading){
	if(fabs(previous_heading - new_heading) > heading_threshold){
		int number_steps = getNumberOfSteps();
		addToTrajectory(previous_heading, number_steps );
		printf("(%f,%d)\n", previous_heading, getNumberOfSteps());
		previous_heading = new_heading;
		resetNumberOfSteps();
		
	}
}