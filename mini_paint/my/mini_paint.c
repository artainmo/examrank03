#include "mini_paint.h"

//On exam no obligation to free correctly
int g_error = 0;

int where(float x, float y, t_cir *cir)
{
	float distance;

	distance = sqrtf((powf((x - cir->x), 2) + powf((y - cir->y), 2)));
	if (distance > cir->radius)
		return (0); //Outside
	if (cir->radius - distance < 1.000000)
		return (2); //Border
	return (1); //Inside
}

char is_in_circle(t_win *win, t_cir *cir, float x, float y)
{
	int position;

	position = where(x, y, cir);
	if (position == 2 || (position == 1 && cir->type == 'C'))
		return (cir->draw);
	else
		return (win->background);
}


static char ft_pixel_put(t_win *win, t_cir *cir, float x, float y)
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

void free_list(t_cir *cir)
{
	t_cir *tmp;

	while (cir)
	{
		tmp = cir;
		cir = cir->next;
		free(tmp);
	}
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
			buffer[i] = ft_pixel_put(win, cir, x, y);
			x++;
			i++;
		}
		buffer[i] = '\n';
		i++;
		y++;
	}
	buffer[i] = '\0';
	free_list(cir);
	return (buffer);
}

void parse(t_win *win, t_cir *cir, FILE * fd)
{
	int ret;

	ret = 1;
	if(!(fscanf(fd, "%d %d %c ", &win->width, &win->height, &win->background)))
		g_error = 1;
	if (win->width <= 0 || win->width > 300 || win->height <= 0 || win->height > 300)
		g_error = 1;
	while(ret != -1)
	{
		if(!(ret = fscanf(fd, "%c %f %f %f %c ", &cir->type, &cir->x, &cir->y, &cir->radius, &cir->draw)))
			g_error = 1;
		if (ret != -1)
		{
			if ((cir->type != 'c' && cir->type != 'C') || cir->radius <= 0 || ret != 5)
				g_error = 1;
			cir->next = malloc(sizeof(t_cir));
			cir = cir->next;
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
	cir = malloc(sizeof(t_cir));
	win = malloc(sizeof(t_win));
	parse(win, cir, fd);
	if (!g_error)
	{
		buffer = get_buffer(win, cir);
		while(buffer[i])
		{
			write(1, &buffer[i], 1);
			i++;
		}
		free(buffer);
		return (0);
	}
	write(1,"Error: Operation file corrupted\n",32);
	return(1);
}
