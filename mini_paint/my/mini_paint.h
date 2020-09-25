#ifndef MINI_PAINT_H
#define MINI_PAINT_H

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

typedef struct s_window
{
	int width;
	int height;
	char background;
} t_win;

typedef struct s_circle
{
	char type;
	float x_c;
	float y_c;
	float radius;
	char draw;
	struct s_circle *next;
} t_cir;

extern int g_error;

#endif


