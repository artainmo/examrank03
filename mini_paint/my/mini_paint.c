#include "mini_paint.h"

int g_error = 0;

int is_in_circle(t_win *win, t_cir *cir, float x, float y)
{
	float	distance_diff;
	float	distance;

	distance = sqrtf(powf(x - cir->x_c, 2) + powf(y - cir->y_c, 2));
	distance_diff = distance - cir->radius;
	if (distance_diff <= 0.00000000 && cir->type == 'C')
		return (cir->draw);
	if (distance_diff > -1.00000000 && distance_diff < 1.00000000 && cir->type == 'c')
		return (cir->draw);
	return (win->background);
}


static char ft_pixel_put(t_win *win, t_cir *cir, int x, int y)
{
	char ret;
	char final;

	final = win->background;
	while(cir->next != NULL)
	{
		ret = is_in_circle(win, cir, x, y);
		if (ret != win->background)
			final = ret;
		cir = cir->next;
	}
	return (final);
}

static t_cir *new_list(t_cir *cir)
{
	t_cir *new;

	new = malloc(sizeof(t_cir));
	cir->next = new;
	return (new);
}

char *get_buffer(t_win *win, t_cir *cir)
{
	int x;
	int y;
	int i = 0;
	char *buffer;

	x = 0;
	y = 0;
	buffer = malloc((win->width * win->height) + win->height + 1);
	while(y < win->height)
	{
		x = 0;
		while (x < win->width)
		{
			buffer[i] = ft_pixel_put(win, cir, (float)x, (float)y);
			x++;
			i++;
		}
		buffer[i] = '\n';
		i++;
		y++;
	}
	buffer[i] = '\0';
	return (buffer);
}

void parse(t_win *win, t_cir *cir, FILE * fd)
{
	int ret;
	t_cir *beginlist;

	ret = 1;
	beginlist = cir;
	if(!(fscanf(fd, "%d %d %c ", &win->width, &win->height, &win->background)))
	{
		g_error = 1;
	}
	if (win->width <= 0 || win->width > 300 || win->height <= 0 || win->height > 300)
	{
		g_error = 1;
	}
	while(ret != -1)
	{
		if(!(ret = fscanf(fd, "%c %f %f %f %c ", &cir->type, &cir->x_c, &cir->y_c, &cir->radius, &cir->draw)))
		{
			g_error = 1;
		}
		if (ret == 5)
		{

			if ((cir->type != 'c' && cir->type != 'C') || cir->radius <= 0)
			{
				g_error = 1;
			}
			cir = new_list(cir);
		}
		else
			cir->next = NULL;
	}
}

int main(int argc, char **argv)
{
	FILE * fd;
	t_win *win;
	t_cir *cir;
	char *buffer;
	int i;

	cir = malloc(sizeof(t_cir));
	win = malloc(sizeof(t_win));
	i = 0;
	if (argc != 2)
	{
		write(1,"Error: argument\n", 16);
		return (1);
	}
	if (!(fd = fopen(argv[1],"r")))
	{
		write(1,"Error: Operation file corrupted\n",32);
		return(1);
	}
	parse(win, cir, fd);
	if (!g_error)
	{
		buffer = get_buffer(win, cir);
	while(buffer[i])
	{
		write(1,&buffer[i],1);
		i++;
	}
	}
	return (g_error);
}
