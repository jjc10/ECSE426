#include "initialization.h"

heading_pair trajectory [20];
//heading_pair trajectory[3] = {{4, 0}, {2, 45}, {3, 90}};
//heading_pair trajectory[3] = {{2, 0}, {15, 90}, {20, 45}};
//int trajectory_array_i = 0;
int trajectory_array_i = 0;


trajectory_states ts;
int pair_count = 0;

int previous_heading = 0;
int heading_threshold = 45;

int send_threshold = 5;


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
int build_transmittable_trajectory(uint8_t* to_send) {
	// a: step, heading
	int i;
	int j;
	int index = 0;
	for (i = 0; i < trajectory_array_i; i++) {
		for (j = 0; j < send_threshold; j++) {
			to_send[index] = 'S';
			index++;
		}
		for (j = 0; j < send_threshold; j++) {
			to_send[index] = trajectory[i].step_count;
			index++;
		}
		for (j = 0; j < send_threshold; j++) {
			to_send[index] = 'H';
			index++;
		}
		for (j = 0; j < send_threshold; j++) {
			to_send[index] = trajectory[i].heading / 45; // compress to single byte.
			index++;
		}
	}
	return index;
}


