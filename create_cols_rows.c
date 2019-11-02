/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_cols_rows.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojustine <ojustine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/31 11:44:30 by ojustine          #+#    #+#             */
/*   Updated: 2019/10/31 14:54:43 by ojustine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

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
	t_row	*root;
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
	root = rows->down;
	return (root);
}

t_row			*create_cols_rows(t_row *figs_lst, t_col ***cols_ptr, int size)
{
	t_row	*root;
	t_row	*rows;

	rows = NULL;
	create_cols(cols_ptr, size);
	rows = create_rows(figs_lst, size);
	if (!rows)
		error_exit(1);
	if (!(root = (t_row*)malloc(sizeof(t_row))))
		error_exit(1);
	root->name = '*';
	root->down = rows;
	root->up = rows->up;
	root->up->down = root;
	root->down->up = root;
	return (root);
}
