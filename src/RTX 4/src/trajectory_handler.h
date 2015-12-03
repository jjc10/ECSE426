//trajectory handling state
typedef enum {
	sameHeading,
	headingChange,
}trajectory_states;

typedef struct heading_pair {
	int step_count;
	int heading;
} heading_pair;

void updateTrajectory(int newHeading);