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
**	It works correctly only with MODE < 7
*/

static int		object_touches(int i, const char *obj)
{
	int touches;

	touches = 0;
	touches += (*(obj + 1) == OBJ_SYM);
	touches += (i > 0 && *(obj - 1) == OBJ_SYM);
	touches += (i < (MODE * MODE) && *(obj + (MODE + 1)) == OBJ_SYM);
	touches += (i > MODE && *(obj - (MODE + 1)) == OBJ_SYM);
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
	t_fig_params pr;

	pr.emp = 0;
	pr.obj = 0;
	pr.touches = 0;
	pr.nls = 0;
	pr.i = -1;
	while (pr.nls < MODE && buf[MODE * pr.nls + MODE + pr.nls] == '\n')
		pr.nls++;
	if (pr.nls != MODE || (buf[MODE * (MODE + 1)] != '\n'
		&& buf[MODE * (MODE + 1)] != '\0'))
		return (0);
	while (buf[++pr.i])
	{
		if (buf[pr.i] != EMPTY_SYM && buf[pr.i] != OBJ_SYM && buf[pr.i] != '\n')
			return (0);
		if (buf[pr.i] == OBJ_SYM)
		{
			pr.obj++;
			pr.touches += object_touches(pr.i, &buf[pr.i]);
		}
		pr.emp += (buf[pr.i] == EMPTY_SYM);
	}
	return (pr.obj == MODE && pr.emp == (MODE * (MODE - 1))
			&& pr.touches >= ((MODE - 2) + MODE));
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
		while (buf[y++ * (MODE + 1) + x] != OBJ_SYM)
			if (y == MODE)
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

static void		convert_str_to_struct(char *buf, t_row **fig, char name)
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
	while (y < MODE)
	{
		x = -1;
		while (++x < MODE)
			if (buf[y * (MODE + 1) + x] == OBJ_SYM)
			{
				(*fig)->objs[point][X] = (x - shift_x);
				(*fig)->objs[point][Y] = (y - shift_y);
				point++;
			}
		y++;
	}
}

/*
**	Accepts fd, number of bytes read of the previous call to this function,
**	and address of pointer to a structure. Reads a figure from file,
**	checks its validity and writes it at address to the structure.
**	Returns the number of bytes read if successful and -1 otherwise.
*/

ssize_t			get_next_fig(int fd, ssize_t prev_reads, t_row **fig)
{
	char			buf[MODE * (MODE + 1) + 2];
	ssize_t			reads;
	static char		name = START_NAME;

	if (name - START_NAME > MAX_FIGS_COUNT)
		return (-1);
	if ((reads = read(fd, buf, (MODE * (MODE + 1) + 1))) < (MODE * (MODE + 1)))
	{
		if (reads == 0 && prev_reads == (MODE * (MODE + 1)))
			return (0);
		else
			return (-1);
	}
	buf[reads] = '\0';
	*fig = (t_row*)malloc(sizeof(t_row));
	if (!(*fig) || !is_valid(buf))
		return (-1);
	convert_str_to_struct(buf, fig, name++);
	return (reads);
}
