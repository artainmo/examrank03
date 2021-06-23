#include "micro_paint.h"

int g_error = 0;

int where(int x, int y, t_r *rec)
{
	float l;
	float r;
	float t;
	float b;

	l = rec->x;
	r = rec->x + rec->width;
	t = rec->y;
	b = rec->y + rec->height;
	if (x < l || x > r || y < t || y > b)
		return (0); //Outside
	if (x - l < 1.000000 || r - x < 1.000000 || y - t < 1.000000 || b - y < 1.000000)
		return (2); //border
	return (1); //Inside
}

void put_pixel(int x, int y, t_w *w, t_r *r)
{
	int position;
	char final;

	final = w->background;
	while (r->next != 0)
	{
		position = where(x, y, r);
		if (position == 2 || (position == 1 && r->type == 'R'))
			final = r->draw;
		r = r->next;
	}
	write(1, &final, 1);
}

void draw(t_w *w, t_r *r)
{
	int y;
	int x;

	y = 0;
	while (y < w->height)
	{
		x = 0;
		while(x < w->width)
		{
			put_pixel(x, y, w, r);
			x++;
		}
		write(1, "\n", 1);
		y++;
	}
}

void parse(FILE *fd, t_w *w, t_r *r)
{
	int ret;

	ret = 1;
	if (!fscanf(fd, "%d %d %c ", &w->width, &w->height, &w->background))
		g_error = 1;
	if (w->width <= 0 || w->width > 300 || w->height <= 0 || w->height > 300)
	   	g_error = 1;
	while (ret != -1)
	{
		if (!(ret = fscanf(fd, "%c %f %f %f %f %c ", &r->type, &r->x, &r->y, &r->width, &r->height, &r->draw)))
			g_error = 1;
		if (ret == -1)
			r->next = 0;
		else
		{
			if (r->type != 'r' && r->type != 'R')
				g_error = 1;
			if (r->width <= 0 || r->height <= 0 || ret != 6)
				g_error = 1;
			r->next = malloc(sizeof(t_r));
			r = r->next;
		}
	}
}

int main(int argc, char **argv)
{
	FILE *fd;
	t_w *w;
	t_r *r;

	if (argc != 2)
	{
		write(1, "Error: argument\n", 16);
		return (1);
	}
	if (!(fd = fopen(argv[1], "r")))
	{
		write(1, "Error: Operation file corrupted\n", 32);
		return (1);
	}
	w = malloc(sizeof(t_w));
	r = malloc(sizeof(t_r));
	parse(fd, w, r);
	fclose(fd);
	if (g_error == 1)
	{
		write(1, "Error: Operation file corrupted\n", 32);
		return (1);
	}
	draw(w, r);
	return (0);
}
