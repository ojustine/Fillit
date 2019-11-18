/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   uncover.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojustine <ojustine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/13 14:53:16 by ojustine          #+#    #+#             */
/*   Updated: 2019/11/13 15:00:57 by ojustine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

static void		uncover_row(t_row *row)
{
	t_node	*node;
	int		row_len;

	node = row->head;
	row_len = row->length;
	while (row_len--)
	{
		node->up->down = node;
		node->down->up = node;
//		if (node->col->head == node->down)
//			node->col->head = node;
//		node->col->length++;
		node = node->right;
	}
	row->up->down = row;
	row->down->up = row;
}

static void		uncover_col(t_col *col)
{
	t_node	*node;
	int		col_len;

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

void			uncover(t_row *row_stack[], t_col *col_stack[], int *r_stack_id,
				int *c_stack_id)
{
	while (*c_stack_id > 0)
		uncover_col(col_stack[--(*c_stack_id)]);
	while (*r_stack_id > 0)
		uncover_row(row_stack[--(*r_stack_id)]);
}
