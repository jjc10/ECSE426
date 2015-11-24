void switchRowToOutput(void);
void switchRowToInput(void);
void switchColumnToOutput(void);
void switchColumnToInput(void);
void scanKeypad(int* rows, int* columns);
int scanInputArray(int* array, int size);
void keypad_thread(void const *argument);

typedef enum {
	WAIT_KEY,
	ACTION,
	IDLE
}keypad_state;