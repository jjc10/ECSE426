#include "initialization.h"

heading_pair trajectory [40];
int trajectory_array_i = 0;
	
trajectory_states ts;
int pair_count = 0;

int previous_heading = 0;
int heading_threshold = 45;

void addToTrajectory(int angle, int number_of_steps) {
	if(number_of_steps != 0){
		heading_pair new_heading_pair= {number_of_steps, angle}; 	
		trajectory[trajectory_array_i] = new_heading_pair;
		trajectory_array_i++;
	}
}

void updateTrajectory(int new_heading){
	//new_heading = getFixedHeading(new_heading);
	//new_heading = roundAngle(new_heading, heading_threshold);
	if(previous_heading != new_heading){
		int number_steps = getNumberOfSteps();
		addToTrajectory(previous_heading, number_steps );
		printf("(%d, %d)\n", previous_heading, getNumberOfSteps());
		previous_heading = new_heading;
		resetNumberOfSteps();
	}
}

