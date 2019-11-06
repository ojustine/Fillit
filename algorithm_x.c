/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algorithm_x.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojustine <ojustine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/31 18:04:22 by ojustine          #+#    #+#             */
/*   Updated: 2019/11/06 18:13:16 by ojustine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

static void		cover(t_row *row)
{
	t_node	*row_node;
	t_node	*col_node;
	int		row_len;
	int		col_len;

	row_node = row->head;
	row_len = row->length;
	while (row_len--)
	{
		col_len = row_node->col->length;
		col_node = row_node->col->head;
		while (col_len--)
		{
			if (col_node->row->up->down == col_node->row
			&& col_node->row->down->up == col_node->row)
			{
				col_node->row->up->down = col_node->row->down;
				col_node->row->down->up = col_node->row->up;
			}
			col_node = col_node->down;
		}
		row_node = row_node->right;
	}
}

static void		uncover(t_row *row)
{
	t_node	*row_node;
	t_node	*col_node;
	int		row_len;
	int		col_len;

	row_node = row->head;
	row_len = row->length;
	while (row_len--)
	{
		col_len = row_node->col->length;
		col_node = row_node->col->head;
		while (col_len--)
		{
			if (col_node->row->up->down != col_node->row
			&& col_node->row->down->up != col_node->row)
			{
				col_node->row->up->down = col_node->row;
				col_node->row->down->up = col_node->row;
			}
			col_node = col_node->down;
		}
		row_node = row_node->right;
	}
}

static t_row	*choose_row(t_row *root, t_row ***sol, int depth)
{
	t_row	*chosen_one;
	int 	i;

	chosen_one = root->down;
	i = -1;
	while (++i < depth)
	{
		while (chosen_one->name == (*sol)[i]->name)
			chosen_one = chosen_one->down;
	}
	return (chosen_one);
}

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
	t_stack		stack[10000];
	t_col		*colStack[1000];
	t_row		*rowStack[1000];
	int 		rowcov = 0;
	int 		colcov = 0;
	t_node		*row_node;
	t_node		*col_node;

	curr_row = choose_row(root, sol, depth);
	while (curr_row != root)
	{
		(*sol)[depth] = curr_row;
		t_node *slide = curr_row->head;
		do{
			t_node *deletor = slide->down;
			while(deletor != slide){
				rowStack[rowcov++] = cover_row(deletor->row);
				deletor = deletor->down;
			}
			colStack[colcov++] = slide->col;
			slide = slide->right;
		}while(slide != curr_row->head);
		rowStack[rowcov++] = cover_row(curr_row);
		for (int i = 0; i < colcov; i++)
			cover_col(colStack[i]);
		if (algorithm_x(root, sol, f_count, depth + 1) == 1)
			return (1);
		while(colcov > 0){
			colcov--;
			uncover_col(colStack[colcov]);
		}
		while(rowcov > 0) {
			rowcov--;
			uncover_row(rowStack[rowcov]);
		}
		curr_row = curr_row->down;
	}
	return ((f_count == depth) ? (1) : (0));
	return (0);
}
