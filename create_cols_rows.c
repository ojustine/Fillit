/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_cols_rows.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojustine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/31 11:44:30 by ojustine          #+#    #+#             */
/*   Updated: 2019/11/05 12:41:47 by ojustine         ###   ########.fr       */
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
**	size). Columns are named from 1 to size^2. All columns are added to a
**	circular doubly linked list.
**	An example with the size of the proposed solution 3:
**							|1|2|3|    cols[0] = {.length = 0, .name = 1}
**	cols[size * size]   =>	|4|5|6| => cols[1] = {.length = 0, .name = 2}
**							|7|8|9|     ... and so on
*/
static void		create_cols(t_col ***cols, int size)
{
	int		i;

	if (!(*cols = (t_col**)malloc(sizeof(t_col*) * (size * size))))
		error_exit(1);
	i = 0;
	while (i < size * size)
	{
		if (!((*cols)[i] = (t_col*)malloc(sizeof(t_col))))
			error_exit(1);
		(*cols)[i]->name = i + 1;
		(*cols)[i]->length = 0;
		if (i > 0)
		{
			(*cols)[i]->left = (*cols)[i - 1];
			(*cols)[i - 1]->right = (*cols)[i];
		}
		i++;
	}
	(*cols)[0]->left = (*cols)[size * size - 1];
	(*cols)[size * size - 1]->right = (*cols)[0];
}

static int		is_fits(t_row *figs, int size, int x, int y)
{
	int i;

	i = 0;
	while (i < 4)
	{
		if (figs->points[i][X] + x >= size || figs->points[i][Y] + y >= size)
			return (0);
		i++;
	}
	return (1);
}

static void		add_row(t_row **rows, t_row *figs, int x, int y)
{
	t_row	*row;
	int		i;

	if (!(row = (t_row*)malloc(sizeof(t_row))))
		error_exit(1);
	row->length = 0;
	row->name = figs->name;
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
	while (i < 4)
	{
		row->points[i][X] = figs->points[i][X] + x;
		row->points[i][Y] = figs->points[i][Y] + y;
		i++;
	}
	*rows = row;
}

static t_row	*create_rows(t_row *figs_lst, int size)
{
	t_row	*figs;
	t_row	*rows;
	int		shift_x;
	int		shift_y;

	rows = NULL;
	figs = figs_lst->down;
	while (figs != figs_lst)
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
**	Creates rows and the root row (empty) included in the row list. Returns a
**	pointer to the root. If necessary, the minimum required size of the future
**	solution is increased.
**	More details in the description of inner functions.
*/

t_row			*create_cols_rows(t_row *figs_lst, t_col ***cols_ptr, int *size)
{
	t_row	*root;
	t_row	*rows;

	rows = NULL;
	while ((rows = create_rows(figs_lst, *size)) == NULL)
		(*size)++;
	create_cols(cols_ptr, *size);
	if (!(root = (t_row*)malloc(sizeof(t_row))))
		error_exit(1);
	root->name = '\0';
	root->down = rows;
	root->up = rows->up;
	root->up->down = root;
	root->down->up = root;
	return (root);
}
