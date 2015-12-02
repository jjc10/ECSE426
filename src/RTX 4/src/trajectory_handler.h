//trajectory handling state
typedef enum {
	sameHeading,
	headingChange,
}trajectory_states;

typedef struct heading_pair {
	int step_count;
	float heading;
} heading_pair;

void updateTrajectory(float newHeading);