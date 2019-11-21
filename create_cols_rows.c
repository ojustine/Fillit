/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_cols_rows.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojustine <ojustine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/31 11:44:30 by ojustine          #+#    #+#             */
/*   Updated: 2019/11/14 14:31:17 by ojustine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

/*
**	Accepts the address of the pointer for future columns and the proposed size
**	of the future solution. At the address creates an array of pointers to a
**	structure of type t_col. The size of the array is the number of cells of the
**	proposed solution (i.e., size^2). For each pointer from the array,
**	a structure of type t_col is created, which has the Name and Length fields.
**	One column is one corresponding cell of a possible solution (for a given
**	size). Columns are named from 1 to size^2.
**	An example with the size of the proposed solution 3:
**	                        |1|2|3|    cols[0] = {.length = 0, .name = 1}
**	cols[size * size]   =>  |4|5|6| => cols[1] = {.length = 0, .name = 2}
**	                        |7|8|9|    cols[8] = {.length = 0, .name = 9}
*/

static void		create_cols(t_col ***cols, int size)
{
	int		i;

	*cols = (t_col**)malloc(sizeof(t_col*) * (size * size));
	if (!(*cols))
		error_exit(1);
	i = 0;
	while (i < size * size)
	{
		(*cols)[i] = (t_col*)malloc(sizeof(t_col));
		if (!(*cols)[i])
			error_exit(1);
		(*cols)[i]->length = 0;
		i++;
	}
}

/*
**	Accepts a pointer to a figure, proposed size of the future solution,
**	and integers x and y. Returns 1 if the given figure with a shift by x and y
**	can be placed in the given size. Returns 0 if not.
*/

static int		is_fits(t_row *fig, int size, int x, int y)
{
	int obj;

	obj = 0;
	while (obj < MODE)
	{
		if (fig->objs[obj][X] + x >= size || fig->objs[obj][Y] + y >= size)
			return (0);
		obj++;
	}
	return (1);
}

/*
**	Accepts a pointer to rows list, a pointer to a figure, integers x and y.
**	Allocates memory for a row. Writes the given figure into it with a shift by
**	x and y. Adds a row to the rows list.
*/

static void		add_row(t_row **rows, t_row *fig, int x, int y)
{
	t_row	*row;
	int		i;

	row = (t_row*)malloc(sizeof(t_row));
	if (!row)
		error_exit(1);
	row->length = 0;
	row->name = fig->name;
	row->up = row;
	row->down = row;
	if (*rows != NULL)
	{
		row->up = *rows;
		row->down = (*rows)->down;
		row->up->down = row;
		row->down->up = row;
	}
	i = 0;
	while (i < MODE)
	{
		row->objs[i][X] = fig->objs[i][X] + x;
		row->objs[i][Y] = fig->objs[i][Y] + y;
		i++;
	}
	*rows = row;
}

/*
**	Accepts a pointer to a list of figures and the proposed size of the future
**	solution. Returns a circular doubly linked list, which are all possible
**	positions of each figure for a given size. Each row is one of the positions
**	of a certain figure.
*/

static t_row	*create_rows(t_row *puzzle, int size)
{
	t_row	*figs;
	t_row	*rows;
	int		shift_x;
	int		shift_y;

	rows = NULL;
	figs = puzzle->down;
	while (figs != puzzle)
	{
		shift_y = -1;
		while (++shift_y < size)
		{
			shift_x = -1;
			while (++shift_x < size)
				if (is_fits(figs, size, shift_x, shift_y))
					add_row(&rows, figs, shift_x, shift_y);
		}
		figs = figs->down;
	}
	if (rows)
		return (rows->down);
	else
		return (NULL);
}

/*
**	Accepts a pointer to a list of figures, a pointer address for future columns
**	and a solution size address. Creates columns at the received address.
**	Creates rows and the root row (empty). All rows and root row are added to
**	a circular doubly linked list
**	Returns a pointer to the root.
**	If necessary, the minimum required size of the future
**	solution is increased (e.g. figure "stick" and size 3).
**	More details in the description of inner functions.
*/

t_row			*create_cols_rows(t_row *puzzle, t_col ***cols_ptr, int *size)
{
	t_row	*root;
	t_row	*rows;

	rows = NULL;
	while ((rows = create_rows(puzzle, *size)) == NULL)
		(*size)++;
	create_cols(cols_ptr, *size);
	if (!(root = (t_row*)malloc(sizeof(t_row))))
		error_exit(1);
	root->name = 0;
	root->down = rows;
	root->up = rows->up;
	root->up->down = root;
	root->down->up = root;
	return (root);
}
