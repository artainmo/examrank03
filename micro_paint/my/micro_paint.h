#ifndef MICRO_PAINT_H
#define MICRO_PAINT_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>

typedef struct s_window
{
	int width;
	int height;
	char background;
} t_w;

typedef struct s_rectangle
{
	char type;
	float x;
	float y;
	float width;
	float height;
	char draw;
	struct s_rectangle *next;
} t_r;

extern int g_error;

#endif
