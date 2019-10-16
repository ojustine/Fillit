#pragma clang diagnostic push
#pragma ide diagnostic ignored "EmptyDeclOrStmt"
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_figs.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojustine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 16:16:11 by ojustine          #+#    #+#             */
/*   Updated: 2019/10/16 13:52:59 by ojustine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

static int		is_valid(const char *buf)
{
	t_errors err = {0, 0, 0, 0, 0};

	CHECK_INT(buf[4] == '\n' && buf[9] == '\n' && buf[14] == '\n'
	&& buf[19] == '\n');
	while (buf[err.i])
	{
		if (buf[err.i] == '#')
		{
			err.obj++;
			if (buf[err.i + 1] == '#' || (err.i > 0 && buf[err.i - 1] == '#')
			|| (err.i < 16 && buf[err.i + 5] == '#')
			|| (err.i > 4 && buf[err.i - 5] == '#'))
				err.touch++;
		}
		else if (buf[err.i] == '.')
			err.dot++;
		else if (buf[err.i] == '\n')
			err.nl++;
		else
			return (0);
		err.i++;
	}
	CHECK_INT(err.obj == 4 && err.dot == 12 && err.nl > 3 && err.nl < 6);
	CHECK_INT(buf[0] != '\n' && (err.touch == 6 || err.touch == 8));
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

static t_fig	*conv_str_to_fig(char *buf, char sym)
{
	t_fig	*fig;
	int		y;
	int		x;
	int		shift_x;
	int		shift_y;

	CHECK_NULL(fig = (t_fig*)malloc(sizeof(t_fig)));
	fig->sym = sym;
	shift_x = shift_fig(buf, X);
	shift_y = shift_fig(buf, Y);
	y = 0;
	while (y < 4)
	{
		x = -1;
		while (++x < 4)
			if (buf[y * 5 + x] == '#')
			{
				fig->points[y][X] = (x - shift_x);
				fig->points[y][Y] = (y - shift_y);
			}
		y++;
	}
	return (fig);
}

t_fig			*get_next_fig(int fd)
{
	t_fig	*fig;
	char	buf[23];
	ssize_t	reads;

	//CHECK_NULL(reads = read(fd, buf, 21) > 19);
	reads = read(fd, buf, 22);
	if (reads == 20)
		reads++;
	buf[reads] = '\0';
	CHECK_NULL(is_valid(buf));
	CHECK_NULL(fig = conv_str_to_fig(buf, 'A'));
	return (fig);
}
