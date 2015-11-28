#define pinGroup		GPIOB
#define segA				GPIO_Pin_5
#define segB				GPIO_Pin_7
#define segC				GPIO_Pin_8
#define segD				GPIO_Pin_11
#define segE				GPIO_Pin_12
#define segF				GPIO_Pin_13
#define segG				GPIO_Pin_14
#define segDP				GPIO_Pin_15
#define dig1				GPIO_Pin_0
#define dig2				GPIO_Pin_1
#define dig3				GPIO_Pin_2
#define dig4				GPIO_Pin_4

void displayNothing(void);
void displayZero(void);
void displayOne(void);
void displayTwo(void);
void displayThree(void);
void displayFour(void);
void displayFive(void);
void displaySix(void);
void displaySeven(void);
void displayEight(void);
void displayNine(void);
void displayLine(void);
void displayDegree(void);

void selectDigit(int digitNumber);
void displayDigit(int digitNumber);
void displayNumber(int number);
void displayDPAt(int position);
void display_thread(void const *argument);