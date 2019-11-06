/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   link_matrix.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojustine <ojustine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/31 11:46:16 by ojustine          #+#    #+#             */
/*   Updated: 2019/11/05 16:24:09 by ojustine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

static void	insert_node_in_row(t_node *head, t_node *new)
{
	new->right = head;
	new->left = head->left;
	new->left->right = new;
	new->right->left = new;
}

static void	insert_node_in_col(t_node *head, t_node *new)
{
	new->down = head;
	new->up = head->up;
	new->up->down = new;
	new->down->up = new;
}

static void	add_node(t_row *row, t_col *col)
{
	t_node *node;

	if (!(node = (t_node*)malloc(sizeof(t_node))))
		error_exit(1);
	node->row = row;
	node->col = col;
	if (row->length == 0)
	{
		row->head = node;
		node->left = node;
		node->right = node;
	}
	else
		insert_node_in_row(row->head, node);
	row->length++;
	if (col->length == 0)
	{
		col->head = node;
		node->up = node;
		node->down = node;
	}
	else
		insert_node_in_col(col->head, node);
	col->length++;
}

void		link_matrix(t_row *root, t_col **cols, int size)
{
	t_row	*rows;
	int		i;
	int 	approp_col_id;

	rows = root->down;
	while (rows != root)
	{
		i = 0;
		while (i < 4)
		{
			approp_col_id = rows->points[i][Y] * size + rows->points[i][X];
			add_node(rows, cols[approp_col_id]);
			i++;
		}
		rows = rows->down;
	}
}
