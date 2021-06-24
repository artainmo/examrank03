#include "mini_paint.h"

int g_error = 0;

int where(int x, int y, t_c *c)
{
	float distance;

	distance = sqrtf(powf(c->x - x, 2) + powf(c->y - y, 2));
	if (distance > c->r)
		return (0); //Outside
	if (c->r - distance < 1.000000)
		return (2); //Border
	return (1); //Inside
}

void ft_pixel_put(int x, int y, t_w *w, t_c *c)
{
	char final;
	int ret;

	final = w->backgroundchar;
	while(c->next != 0)
	{
		ret = where(x, y, c);
		if (ret == 2 || (ret == 1 && c->type == 'C'))
			final = c->draw;
		c = c->next;
	}
	write(1, &final, 1);
}

void draw(t_w *w, t_c *c)
{
	int x;
	int y;

	y = 0;
	while (y < w->height)
	{
		x = 0;
		while (x < w->width)
		{
			ft_pixel_put(x, y, w, c);
			x++;
		}
		write(1, "\n", 1);
		y++;
	}
}

void parse(FILE *fd, t_w *w, t_c *c)
{
	int ret;

	ret = 0;
	if (fscanf(fd, "%d %d %c ", &w->width, &w->height, &w->backgroundchar) != 3)
		g_error = 1;
	if (w->width <= 0 || w->width > 300 || w->height <= 0 || w->height > 300)
		g_error = 1;
	while (ret != -1)
	{
		if (!(ret = fscanf(fd, "%c %f %f %f %c ", &c->type, &c->x, &c->y, &c->r, &c->draw)))
			g_error = 1;
		if (ret == -1)
		{
			c->next = 0;
			break ;
		}
		if ((c->type != 'c' && c->type != 'C') || c->r <= 0 || ret != 5)
			g_error = 1;
		c->next = malloc(sizeof(t_c));
		c = c->next;
	}
}

int main(int argc, char **argv)
{
	t_w *w;
	t_c *c;
	FILE *fd;

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
	c = malloc(sizeof(t_c));
	parse(fd, w, c);
	if (g_error != 0)
	{
		write(1, "Error: Operation file corrupted\n", 32);
		return (1);
	}
	draw(w, c);
	return (0);
}

