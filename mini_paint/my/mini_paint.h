#ifndef MINI_PAINT_H
#define MINI_PAINT_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <math.h>

typedef struct s_window
{
	int width;
	int height;
	char backgroundchar;
} t_w;

typedef struct s_circle
{
	char type;
	float x;
	float y;
	float r;
	char draw;
	struct s_circle *next;
} t_c;

extern int g_error;

#endif
