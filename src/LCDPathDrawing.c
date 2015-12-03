#include "LCDPathDrawing.h"

LCDPoint path[100];

int getXFromPolar(float angle, int r) {
	float temp;
	temp = r * cos((180 - angle) * PI / 180);
	if (temp < 0) {
		temp = ceil(temp - 0.5);
	} else {
		temp = floor(temp + 0.5);
	}
	return (int)(temp);
}

int getYFromPolar(float angle, int r) {
	float temp;
	temp = r * sin((180 - angle) * PI / 180);
	if (temp < 0) {
		temp = ceil(temp - 0.5);
	} else {
		temp = floor(temp + 0.5);
	}
	return (int)(temp);
}

void convertHeadingToCartesian(heading_pair * heading, int length) {	
	int i;
	int gtrdn = 0;
	for (i = 0; i < length; i++) {
		if (i == 0) {
			path->x = 0;
			path->y = 0;
			(path + 1)->x = getXFromPolar(heading->heading, heading->step_count);
			(path + 1)->y = getYFromPolar(heading->heading, heading->step_count);
		} else {
			(path + i + 1)->x = getXFromPolar((heading + i)->heading, (heading + i)->step_count) + (path + i)->x;
			(path + i + 1)->y = getYFromPolar((heading + i)->heading, (heading + i)->step_count) + (path + i)->y;
		}
	}
}

void drawBorder() {
	LCD_DrawUniLine(X_MIN, Y_MIN, X_MIN, Y_MAX);
	LCD_DrawUniLine(X_MIN, Y_MAX, X_MAX, Y_MAX);
	LCD_DrawUniLine(X_MAX, Y_MAX, X_MAX, Y_MIN);
	LCD_DrawUniLine(X_MAX, Y_MIN, X_MIN, Y_MIN);
}

int getMinY(LCDPoint * path, int length) {
	int min = path->y;
	int i;	
	for (i = 0; i < length; i++) {
		if ((path + i)->y < min) {
			min = (path + i)->y;
		}			
	}
	return min;
}

int getMinX(LCDPoint * path, int length) {
	int min = path->x;
	int i;	
	for (i = 0; i < length; i++) {
		if ((path + i)->x < min) {
			min = (path + i)->x;
		}			
	}	
	return min;
}

int getMaxY(LCDPoint * path, int length) {
	int max = path->y;
	int i;
	for (i = 0; i < length; i++) {
		if ((path + i)->y > max) {
			max = (path + i)->y;
		}			
	}
	
	return max;	
}

int getMaxX(LCDPoint * path, int length) {
	int max = path->x;
	int i;
	for (i = 0; i < length; i++) {
		if ((path + i)->x > max) {
			max = (path + i)->x;
		}			
	}
	
	return max;		
}

int getScaledX(int pathX, int pathMinX, int pathMaxX) {
	float scaleFactor = (X_MAX - X_MIN) / (pathMaxX - pathMinX);
	return X_MIN + (scaleFactor * (pathX - pathMinX));
}

int getScaledY(int pathY, int pathMinY, int pathMaxY) { // Takes care of transformation from LCD coordinate system to real coodinate system
	float scaleFactor = (Y_MAX - Y_MIN) / (pathMaxY - pathMinY);
	return Y_MAX - (scaleFactor * (pathY - pathMinY));
}	

LCDPoint potato[] = {{0, 0}, {4, 9}, {0, 17}, {-9, 19}, {-14, 11}, {-23, 7}};

void drawPath(int length) {	
	int pathMinX = getMinX(path, length);
	int pathMinY = getMinY(path, length);
	int pathMaxX = getMaxX(path, length);
	int pathMaxY = getMaxY(path, length);
	int i;
	int x;
	int y;
	
	int max;
	int min;
	
	if (pathMinX < 0) {
		int negativeOffsetX = -pathMinX;
		pathMinX += negativeOffsetX;
		pathMaxX += negativeOffsetX;
		for (i = 0; i < length; i++) {
			(path + i)->x += negativeOffsetX;
		}
	}
	
	if (pathMinY < 0) {
		int negativeOffsetY = -pathMinY;
		pathMinY += negativeOffsetY;
		pathMaxY += negativeOffsetY;
		for (i = 0; i < length; i++) {
			(path + i)->y += negativeOffsetY;
		}
	}
	
	if (pathMaxX > pathMaxY) {
		max = pathMaxX;
	} else {
		max = pathMaxY;
	}
	
	if (pathMinX < pathMinY) {
		min = pathMinX;
	} else {
		min = pathMinY;
	}
	
	for (i = 0; i < length - 1; i++) {
		int x1 = getScaledX((path + i)->x, min, max);
		int y1 = getScaledY((path + i)->y, min, max);
		int x2 = getScaledX((path + i + 1)->x, min, max);
		int y2 = getScaledY((path + i + 1)->y, min, max);
		LCD_DrawUniLine(x1, y1, x2, y2);
	}		
}
	void drawTrajectory(heading_pair * pair, int length) {
		/* LCD initiatization */
		LCD_Init();
		/* LCD Layer initiatization */
		LCD_LayerInit();
		/* Enable the LTDC controler */
		LTDC_Cmd(ENABLE);
		/* Set LCD foreground layer as the current layer */
		LCD_SetLayer(LCD_FOREGROUND_LAYER);
		LCD_Clear(0xFFFFFF);
		
		convertHeadingToCartesian(pair, length);
		drawPath(length + 1);
	}
	