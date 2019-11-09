/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cover.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojustine <ojustine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/07 16:51:05 by ojustine          #+#    #+#             */
/*   Updated: 2019/11/09 19:17:56 by ojustine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

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
	int		col_len;

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

void			cover(t_row *(*r_stack)[], t_col *(*c_stack)[], int *r_cov,
				int *c_cov)
{
	t_row	*curr;
	t_row	*clone;
	t_node	*rownode;
	t_node	*colnode;
	int		i;

	curr = (*r_stack)[1];
	clone = (*r_stack)[0]->down;
	while (clone->name != curr->name + 1 && clone->name != '\0')
	{
		if (clone->name == curr->name && clone != curr)
			(*r_stack)[(*r_cov)++] = cover_row(clone);
		clone = clone->down;
	}
	i = 1;
	rownode = curr->head;
	while (rownode != curr->head || i)
	{
		colnode = rownode->down;
		while (colnode != rownode)
		{
			(*r_stack)[(*r_cov)++] = cover_row(colnode->row);
			colnode = colnode->down;
		}
		(*c_stack)[(*c_cov)++] = rownode->col;
		rownode = rownode->right;
		i = 0;
	}
	(*r_stack)[(*r_cov)++] = cover_row(curr);
	i = -1;
	while (++i < *c_cov)
		cover_col((*c_stack)[i]);
}
