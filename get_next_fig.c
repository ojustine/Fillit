/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_fig.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojustine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/17 14:19:49 by ojustine          #+#    #+#             */
/*   Updated: 2019/10/19 12:10:11 by ojustine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

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
	{
		CHECK_INT(buf[err.i] == '#' || buf[err.i] == '.' || buf[err.i] == '\n');
		err.obj += (buf[err.i] == '#');
		err.touch += (buf[err.i] == '#' && buf[err.i + 1] == '#');
		err.touch += (err.i > 0 && buf[err.i] == '#' && buf[err.i - 1] == '#');
		err.touch += (err.i < 16 && buf[err.i] == '#' && buf[err.i + 5] == '#');
		err.touch += (err.i > 4 && buf[err.i] == '#' && buf[err.i - 5] == '#');
		err.dot += (buf[err.i] == '.');
		err.nl += (buf[err.i] == '\n');
	}
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
	if (axis == Y)
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
	shift_x = shift_fig(buf, X);
	shift_y = shift_fig(buf, Y);
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

ssize_t			get_next_fig(int fd, t_fig **figs)
{
	char			buf[22];
	ssize_t			reads;
	static char		sym = 'A';

	CHECK_INT(sym <= 'Z');
	if ((reads = read(fd, buf, 21)) == 0)
		return (-1);
	buf[reads] = '\0';
	CHECK_INT(is_valid(buf));
	CHECK_INT(*figs = (t_fig*)malloc(sizeof(t_fig)));
	CHECK_INT(*figs = conv_str_to_fig(buf, *figs, sym++));
	return (reads);
}
