/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algorithm_x.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojustine <ojustine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/31 18:04:22 by ojustine          #+#    #+#             */
/*   Updated: 2019/11/02 13:23:40 by ojustine         ###   ########.fr       */
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

int				algorithm_x(t_row *root, t_row **sol, int f_count, int depth)
{
	t_rstack	*r_stack;
	t_cstack	*c_stack;

	if (root->down == root && depth == f_count)
		return (1);
	else if (root->down == root)
		return (0);
	while ()
	{
		sol[depth] = root->down;
	}
	return (0);
}
