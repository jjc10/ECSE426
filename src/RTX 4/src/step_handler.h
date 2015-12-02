//Step state
typedef enum {
	zero,
	high,
	low,
}step_states;

void updateStepState(float gyro_y);
int getNumberOfSteps(void);
void resetNumberOfSteps(void);