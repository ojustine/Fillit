/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_fig.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojustine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/17 14:19:49 by ojustine          #+#    #+#             */
/*   Updated: 2019/10/17 14:20:33 by ojustine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

static int		touches(const char *buf, int i)
{
	int touch;

	touch = 0;
	if (*(buf + 1) == '#')
		touch++;
	if (i > 0 && *(buf - 1) == '#')
		touch++;
	if (i < 16 && *(buf + 5) == '#')
		touch++;
	if (i > 4 && *(buf - 5) == '#')
		touch++;
	return (touch);
}

static int		is_valid(const char *buf)
{
	t_errors err;

	err.dot = 0;
	err.obj = 0;
	err.touch = 0;
	err.nl = 0;
	err.i = -1;
	CHECK_INT(buf[4] == '\n' && buf[9] == '\n' && buf[14] == '\n'
	&& buf[19] == '\n' && (buf[20] == '\n' || buf[20] == '\0'));
	while (buf[++err.i])
		if (buf[err.i] == '#')
		{
			err.obj++;
			err.touch += touches(&buf[err.i], err.i);
		}
		else if (buf[err.i] == '.')
			err.dot++;
		else if (buf[err.i] == '\n')
			err.nl++;
		else
			return (0);
	CHECK_INT(err.obj == 4 && err.dot == 12 && err.nl > 3 && err.nl < 6);
	CHECK_INT(err.touch == 6 || err.touch == 8);
	return (1);
}

static int		shift_fig(const char *buf, int axis)
{
	int	shift;
	int	x;
	int	y;

	shift = 0;
	x = 0;
	y = 0;
	if (axis == X)
	{
		while (buf[x] != '#')
			if (buf[x++] == '\n')
				shift++;
	}
	else
	{
		while (buf[y++ * 5 + x] != '#')
			if (y == 4)
			{
				y = 0;
				x++;
				shift++;
			}
	}
	return (shift);
}

static t_fig	*conv_str_to_fig(char *buf, t_fig *fig, char sym)
{
	int		y;
	int		x;
	int		point;
	int		shift_x;
	int		shift_y;

	fig->sym = sym;
	shift_y = shift_fig(buf, X);
	shift_x = shift_fig(buf, Y);
	y = 0;
	point = 0;
	while (y < 4)
	{
		x = -1;
		while (++x < 4)
			if (buf[y * 5 + x] == '#')
			{
				fig->points[point][X] = (x - shift_x);
				fig->points[point++][Y] = (y - shift_y);
			}
		y++;
	}
	return (fig);
}

t_fig			*get_next_fig(int fd)
{
	t_fig	*fig;
	char	buf[22];
	ssize_t	reads;

	CHECK_NULL((reads = read(fd, buf, 21)) > 19);
	buf[reads] = '\0';
	CHECK_NULL(is_valid(buf));
	CHECK_NULL(fig = (t_fig*)malloc(sizeof(t_fig)));
	CHECK_NULL(fig = conv_str_to_fig(buf, fig, 'A'));
	return (fig);
}
