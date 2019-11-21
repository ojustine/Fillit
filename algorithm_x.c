/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algorithm_x.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojustine <ojustine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/31 18:04:22 by ojustine          #+#    #+#             */
/*   Updated: 2019/11/15 14:24:45 by ojustine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

/*
**	Covers row in rows list and covers its nodes in the corresponding columns.
*/

static t_row	*cover_row(t_row *row)
{
	t_node	*node;
	int		row_len;

	node = row->head;
	row_len = row->length;
	while (row_len--)
	{
		node->up->down = node->down;
		node->down->up = node->up;
		node = node->right;
	}
	row->up->down = row->down;
	row->down->up = row->up;
	return (row);
}

/*
**	Takes pointers to a stack and its id, row.
**	Covers and adds in stack the row itself and all rows that it intersects
**	in columns.
*/

static void		cover(t_row *(*row_stack)[], int *row_stack_id, t_row *row)
{
	t_node	*rownode;
	t_node	*colnode;
	int		do_while_fake;

	do_while_fake = 1;
	rownode = row->head;
	while (rownode != row->head || do_while_fake--)
	{
		colnode = rownode->down;
		while (colnode != rownode)
		{
			(*row_stack)[(*row_stack_id)++] = cover_row(colnode->row);
			colnode = colnode->down;
		}
		rownode = rownode->right;
	}
	(*row_stack)[(*row_stack_id)++] = cover_row(row);
}

/*
**	Uncovers all rows hidden in a stack
*/

static void		uncover(t_row *row_stack[], int *row_stack_id)
{
	t_row	*row;
	t_node	*node;
	int		row_len;

	while (*row_stack_id > 0)
	{
		row = row_stack[--(*row_stack_id)];
		node = row->head;
		row_len = row->length;
		while (row_len--)
		{
			node->up->down = node;
			node->down->up = node;
			node = node->right;
		}
		row->up->down = row;
		row->down->up = row;
	}
}

/*
**	Implementation of Donald Knuth's DLX algorithm
**	See: https://arxiv.org/pdf/cs/0011047.pdf
**       https://en.wikipedia.org/wiki/Dancing_Links
**       https://en.wikipedia.org/wiki/Knuth%27s_Algorithm_X
*/

int				algorithm_xxx(t_row *root, t_row ***sol, int f_count, int depth)
{
	t_row	*row_stack[f_count * 100];
	t_row	*row;
	int		row_stack_id;

	row_stack_id = 0;
	row = root->down;
	while (row != root && row->name != START_NAME + depth)
		row = row->down;
	while (row != root && row->name == (START_NAME + depth))
	{
		(*sol)[depth] = row;
		cover(&row_stack, &row_stack_id, row);
		if (algorithm_xxx(root, sol, f_count, depth + 1) == 1)
		{
			uncover(row_stack, &row_stack_id);
			return (1);
		}
		uncover(row_stack, &row_stack_id);
		row = row->down;
	}
	return ((f_count == depth) ? 1 : 0);
}
