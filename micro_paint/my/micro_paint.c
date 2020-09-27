#include "micro_paint.h"

//On exam no obligation to free correctly
int g_error = 0;

int where(float x, float y, t_r *rec)
{
	float xl = rec->x;
	float xr = rec->x + rec->width;
	float yt = rec->y;
	float yb = rec->y + rec->height;

	if (x < xl || x > xr || y < yt || y > yb)
		return (0); //Outside
	if (x - xl < 1.000000 || xr - x < 1.000000 || y - yt < 1.000000 || yb - y < 1.000000)
		return (2); //Border
	return (1); //Inside
}

int is_in_rectangle(t_win *win, t_r *rec, float x, float y)
{
	int position;

	position = where(x, y, rec);
	if (position == 2 || (position == 1 && rec->type == 'R'))
		return (rec->draw);
	else
		return (win->background);
}


char ft_pixel_put(t_win *win, t_r *r, float x, float y)
{
	char ret;
	char final;

	final = win->background;
	while(r->next != NULL)
	{
		ret = is_in_rectangle(win, r, x, y);
		if (ret != win->background) //Last rectangle activates the pixel
			final = ret;
		r = r->next;
	}
	return (final);
}

void free_list(t_r *rec)
{
	t_r *tmp;

	while (rec)
	{
		tmp = rec;
		rec = rec->next;
		free(tmp);
	}
}

char *get_buffer(t_win *win, t_r *r)
{
	int x;
	int y;
	int i;
	char *buffer;

	x = 0;
	y = 0;
	i = 0;
	buffer = malloc((win->width * win->height) + win->height + 1);
	while(y < win->height)
	{
		x = 0;
		while (x < win->width)
		{
			buffer[i] = ft_pixel_put(win, r, x, y);
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

void parse(t_win *win, t_r *r, FILE * fd)
{
	int ret;

	ret = 1;
	if(!(fscanf(fd, "%d %d %c ", &win->width, &win->height, &win->background)))
		g_error = 1;
	if (win->width <= 0 || win->width > 300 || win->height <= 0 || win->height > 300)
		g_error = 1;
	while(ret != -1)
	{
		if(!(ret = fscanf(fd, "%c %f %f %f %f %c ", &r->type, &r->x, &r->y, &r->width, &r->height, &r->draw)))
			g_error = 1;
		if (ret != -1)
		{
			if ((r->type != 'r' && r->type != 'R') || r->width <= 0 || r->height <= 0 || ret != 6)
				g_error = 1;
			r->next = malloc(sizeof(t_r));
			r = r->next;
		}
		else
			r->next = NULL;
	}
}

int main(int argc, char **argv)
{
	FILE * fd;
	t_win *win;
	t_r *r;
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
	r = malloc(sizeof(t_r));
	win = malloc(sizeof(t_win));
	parse(win, r, fd);
	if (!g_error)
	{
		buffer = get_buffer(win, r);
		while(buffer[i])
		{
			write(1,&buffer[i],1);
			i++;
		}
		free(buffer);
		return (0);
	}
	write(1, "Error: Operation file corrupted\n", 32);
	return (1);
}
