/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_fig.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojustine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/31 11:43:50 by ojustine          #+#    #+#             */
/*   Updated: 2019/11/12 16:16:09 by ojustine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

/*
**	Returns the number of touches for this object with other objects
*/

static int		object_touches(int i, const char *obj)
{
	int touches;

	touches = 0;
	touches += (*(obj + 1) == OBJ_SYM);
	touches += (i > 0 && *(obj - 1) == OBJ_SYM);
	touches += (i < 16 && *(obj + 5) == OBJ_SYM);
	touches += (i > 4 && *(obj - 5) == OBJ_SYM);
	return (touches);
}

/*
**	Checks tetramino contained in string buffer
**	A valid tetramino must contain 4 objects, 12 dots,
**	5 line breaks or 4 line breaks and 1 null-terminator.
**	Each object must touch at least one other object
*/

static int		is_valid(const char *buf)
{
	t_tet_params par;

	par.dot = 0;
	par.obj = 0;
	par.touches = 0;
	par.nl = 0;
	par.i = -1;
	if (!(buf[4] == '\n' && buf[9] == '\n' && buf[14] == '\n'
		&& buf[19] == '\n' && (buf[20] == '\n' || buf[20] == '\0')))
		return (0);
	while (buf[++par.i])
	{
		if (buf[par.i] != '.' && buf[par.i] != OBJ_SYM && buf[par.i] != '\n')
			return (0);
		if (buf[par.i] == OBJ_SYM)
		{
			par.obj++;
			par.touches += object_touches(par.i, &buf[par.i]);
		}
		par.dot += (buf[par.i] == '.');
		par.nl += (buf[par.i] == '\n');
	}
	return (par.obj == 4 && par.dot == 12 && par.nl > 3 && par.nl < 6
			&& (par.touches == 6 || par.touches == 8));
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
		while (buf[x] != OBJ_SYM)
			if (buf[x++] == '\n')
				shift++;
	if (axis == X)
		while (buf[y++ * 5 + x] != OBJ_SYM)
			if (y == 4)
			{
				y = 0;
				x++;
				shift++;
			}
	return (shift);
}

/*
**	Converts tetramino contained in the string buffer into a structure
*/

static void		conv_str_to_struct(char *buf, t_row **fig, char name)
{
	int		y;
	int		x;
	int		point;
	int		shift_x;
	int		shift_y;

	(*fig)->name = name;
	shift_x = shift_fig_to_0(buf, X);
	shift_y = shift_fig_to_0(buf, Y);
	y = 0;
	point = 0;
	while (y < 4)
	{
		x = -1;
		while (++x < 4)
			if (buf[y * 5 + x] == OBJ_SYM)
			{
				(*fig)->points[point][X] = (x - shift_x);
				(*fig)->points[point][Y] = (y - shift_y);
				point++;
			}
		y++;
	}
}

/*
**	Accepts fd and pointer to a structure. Reads a figure from file,
**	checks its validity and writes it to the structure.
**	Returns the number of bytes read if successful and -1 otherwise.
*/

ssize_t			get_next_fig(int fd, ssize_t prev_reads, t_row **fig)
{
	char			buf[22];
	ssize_t			reads;
	static char		name = START_SYM;

	if (name - START_SYM > MAX_FIGS_COUNT)
		return (-1);
	if ((reads = read(fd, buf, 21)) < 20)
	{
		if (reads == 0 && prev_reads == 20)
			return (0);
		else
			return (-1);
	}
	buf[reads] = '\0';
	*fig = (t_row*)malloc(sizeof(t_row));
	if (!(*fig) || !is_valid(buf))
		return (-1);
	conv_str_to_struct(buf, fig, name++);
	return (reads);
}
