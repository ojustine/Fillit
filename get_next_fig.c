/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_fig.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojustine <ojustine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/31 11:43:50 by ojustine          #+#    #+#             */
/*   Updated: 2019/11/01 15:06:19 by ojustine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

/*
**	Checks tetramino contained in string buffer
*/

static int		is_valid(const char *buf)
{
	t_tet_params pr;

	pr.dot = 0;
	pr.obj = 0;
	pr.con = 0;
	pr.nl = 0;
	pr.i = -1;
	if (!(buf[4] == '\n' && buf[9] == '\n' && buf[14] == '\n'
		&& buf[19] == '\n' && (buf[20] == '\n' || buf[20] == '\0')))
		return (-1);
	while (buf[++pr.i])
	{
		CHECK_INT(buf[pr.i] == '#' || buf[pr.i] == '.' || buf[pr.i] == '\n');
		pr.obj += (buf[pr.i] == '#');
		pr.con += (buf[pr.i] == '#' && buf[pr.i + 1] == '#');
		pr.con += (pr.i > 0 && buf[pr.i] == '#' && buf[pr.i - 1] == '#');
		pr.con += (pr.i < 16 && buf[pr.i] == '#' && buf[pr.i + 5] == '#');
		pr.con += (pr.i > 4 && buf[pr.i] == '#' && buf[pr.i - 5] == '#');
		pr.dot += (buf[pr.i] == '.');
		pr.nl += (buf[pr.i] == '\n');
	}
	CHECK_INT(pr.obj == 4 && pr.dot == 12 && pr.nl > 3 && pr.nl < 6);
	CHECK_INT(pr.con == 6 || pr.con == 8);
	return (1);
}

/*
**	Returns the number by which the tetramino contained in the buffer
**	can be shifted to the maximum left (along the X axis)
**	or up (along the Y axis) to point {0;0} of 4x4 area
*/

static int		shift_fig_to_0(const char *buf, int axis)
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

/*
**	Converts tetramino contained in the string buffer into a structure
*/

static t_row	*conv_str_to_fig(char *buf, t_row *fig, char name)
{
	int		y;
	int		x;
	int		point;
	int		shift_x;
	int		shift_y;

	fig->name = name;
	shift_x = shift_fig_to_0(buf, X);
	shift_y = shift_fig_to_0(buf, Y);
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

/*
**	Accepts fd and pointer to a structure. Reads a figure from file,
**	checks its validity and writes it to the structure.
**	Returns the number of bytes read if successful and -1 otherwise.
*/

ssize_t			get_next_fig(int fd, t_row **fig)
{
	char			buf[22];
	ssize_t			reads;
	static char		sym = START_SYM;

	CHECK_INT(sym - START_SYM < MAX_FIGS_COUNT);
	if ((reads = read(fd, buf, 21)) == 0)
		return (0);
	buf[reads] = '\0';
	CHECK_INT(is_valid(buf));
	CHECK_NULL(*fig = (t_row*)malloc(sizeof(t_row)));
	CHECK_NULL(*fig = conv_str_to_fig(buf, *fig, sym++));
	return (reads);
}
