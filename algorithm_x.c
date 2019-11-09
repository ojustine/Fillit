/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algorithm_x.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojustine <ojustine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/31 18:04:22 by ojustine          #+#    #+#             */
/*   Updated: 2019/11/09 19:16:21 by ojustine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

static t_row	*cover_row(t_row *row)
{
	t_node	*node;
	int 	row_len;

	node = row->head;
	row_len = row->length;
	while (row_len--)
	{
		node->up->down = node->down;
		node->down->up = node->up;
		if (node->col->head == node)
			node->col->head = node->down;
		node->col->length--;
		node = node->right;
	}
	row->up->down = row->down;
	row->down->up = row->up;
	return (row);
}

static t_col	*cover_col(t_col *col)
{
	t_node	*node;
	int 	col_len;

	node = col->head;
	col_len = col->length;
	while (col_len--)
	{
		node->left->right = node->right;
		node->right->left = node->left;
		if (node->row->head == node)
			node->row->head = node->right;
		node->row->length--;
		node = node->down;
	}
	col->left->right = col->right;
	col->right->left = col->right;
	return (col);
}

static void		uncover_row(t_row *row)
{
	t_node	*node;
	int 	row_len;

	node = row->head;
	row_len = row->length;
	while (row_len--)
	{
		node->up->down = node;
		node->down->up = node;
		if (node->col->head == node->down)
			node->col->head = node;
		node->col->length++;
		node = node->right;
	}
	row->up->down = row;
	row->down->up = row;
}

static void		uncover_col(t_col *col)
{
	t_node	*node;
	int 	col_len;

	node = col->head;
	col_len = col->length;
	while (col_len--)
	{
		node->left->right = node;
		node->right->left = node;
		if (node->row->head == node->right)
			node->row->head = node;
		node->row->length++;
		node = node->down;
	}
	col->left->right = col;
	col->right->left = col;
}

int				algorithm_x(t_row *root, t_row ***sol, int f_count, int depth)
{
	t_row		*curr_row;
	t_col		*colStack[1000];
	t_row		*rowStack[1000];
	int 		rowcov = 0;
	int 		colcov = 0;
	int 		solved;

	curr_row = root->down;
	while (curr_row != root)
	{
		(*sol)[depth] = curr_row;
		rowStack[0] = root;
		rowStack[1] = curr_row;
		cover(&rowStack, &colStack, &rowcov, &colcov);
		solved = algorithm_x(root, sol, f_count, depth + 1);

		while(colcov > 0)
			uncover_col(colStack[--colcov]);
		while(rowcov > 0)
			uncover_row(rowStack[--rowcov]);
		if (solved)
			return (1);
		curr_row = curr_row->down;
	}
	return ((depth == f_count) ? 1 : 0);
}
