//trajectory handling state
#include <stdint.h>
typedef enum {
	sameHeading,
	headingChange,
}trajectory_states;

typedef struct heading_pair {
	int step_count;
	int heading;
} heading_pair;

void updateTrajectory(int newHeading);

int build_transmittable_trajectory(uint8_t* to_send);
int get_number_of_points();
void print_trajectory();
