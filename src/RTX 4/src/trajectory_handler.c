#include "initialization.h"

heading_pair trajectory [20];
int trajectory_array_i = 0;


trajectory_states ts;
int pair_count = 0;

int previous_heading = 0;
int heading_threshold = 45;

int send_threshold = 20;

/**
 * @brief  Adds an element to the polar path
 * @param  angle Angle of the heading
 * @param  number_of_steps The number of steps taken in that particular heading
 */
void addToTrajectory(int angle, int number_of_steps) {
	if(number_of_steps != 0){
		heading_pair new_heading_pair= {number_of_steps, angle}; 	
		trajectory[trajectory_array_i] = new_heading_pair;
		trajectory_array_i++;
	}
}

/**
 * @brief  Signals the module that it should start counting steps for a new heading
 * @param  new_heading Angle of the heading
 */
void updateTrajectory(int new_heading){
	if(previous_heading != new_heading){
		int number_steps = getNumberOfSteps();
		addToTrajectory(previous_heading, number_steps );
		printf("(%d, %d)\n", previous_heading, getNumberOfSteps());
		previous_heading = new_heading;
		resetNumberOfSteps();
	}
}

/**
 * @brief  Converts the polar path into a transmittable element
 * @param  to_send Pointer to the element to be transmitted
 */
int build_transmittable_trajectory(uint8_t* to_send) {
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
			to_send[index] = trajectory[i].heading / 45;
			index++;
		}
	}
	return index;
}

/**
 * @brief  Get the number of elements in the polar path
 * @retval The size of the polar path
 */
int get_number_of_points() {
	return trajectory_array_i;
}


/**
 * @brief  Fancy print of polar path
 */
void print_trajectory() {
	int i;
	int data_points =  get_number_of_points();
	for (i = 0; i < data_points; i++) {
		printf("heading: %d\t steps: %d\n", trajectory[i].heading, trajectory[i].step_count);
	}		
}

