/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cover.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojustine <ojustine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/07 16:51:05 by ojustine          #+#    #+#             */
/*   Updated: 2019/11/14 15:26:22 by ojustine         ###   ########.fr       */
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
//		if (node->col->head == node)
//			node->col->head = node->down;
//		node->col->length--;
		node = node->right;
	}
	row->up->down = row->down;
	row->down->up = row->up;
	return (row);
}

//static t_col	*cover_col(t_col *col)
//{
//	t_node	*node;
//	int		col_len;
//
//	node = col->head;
//	col_len = col->length;
//	while (col_len--)
//	{
//		node->left->right = node->right;
//		node->right->left = node->left;
//		if (node->row->head == node)
//			node->row->head = node->right;
//		node->row->length--;
//		node = node->down;
//	}
//	col->left->right = col->right;
//	col->right->left = col->right;
//	return (col);
//}

//static void		cover_clones(t_row *root, t_row *row, t_row *(*r_stack)[],
//				int *r_stack_id)
//{
//	t_row	*clone;
//
//	clone = root->down;
//	while (clone != root)
//	{
//		if (clone->name == row->name && clone != row)
//			(*r_stack)[(*r_stack_id)++] = cover_row(clone);
//		clone = clone->down;
//	}
//}

int				cover(t_row *(*r_stack)[], t_col *(*c_stack)[], t_node *node,
				int *r_stack_id)
{
	t_node	*rownode;
	t_node	*colnode;
	int		c_stack_id;
	int		i;

	//cover_clones((*r_stack)[0], node->row, r_stack, r_stack_id);
	c_stack_id = 0;
	i = 1;
	rownode = node;
	while (rownode != node || i--)
	{
		colnode = rownode->down;
		while (colnode != rownode)
		{
			(*r_stack)[(*r_stack_id)++] = cover_row(colnode->row);
			colnode = colnode->down;
		}
//		(*c_stack)[c_stack_id++] = rownode->col;
		rownode = rownode->right;
	}
	(*r_stack)[(*r_stack_id)++] = cover_row(node->row);
	i = -1;
//	while (++i < c_stack_id)
//		cover_col((*c_stack)[i]);
	return (c_stack_id);
}
