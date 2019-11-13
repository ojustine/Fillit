/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algorithm_x.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojustine <ojustine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/31 18:04:22 by ojustine          #+#    #+#             */
/*   Updated: 2019/11/13 15:04:47 by ojustine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

int				algorithm_xx(t_row *root, t_row ***sol, int f_count, int depth)
{
	t_node		*node;
	t_col		*col_stack[1000];
	t_row		*row_rtack[1000];
	int			r_stack_id;
	int			c_stack_id;

	if (root->down == root)
		return ((f_count == depth) ? 1 : 0);
	node = root->down->head->col->head;
	r_stack_id = 0;
	c_stack_id = 1;
	while (node != root->down->head->col->head || c_stack_id--)
	{
		(*sol)[depth] = node->row;
		row_rtack[0] = root;
		c_stack_id = cover(&row_rtack, &col_stack, node, &r_stack_id);
		if (algorithm_xx(root, sol, f_count, depth + 1) == 1)
		{
			uncover(row_rtack, col_stack, &r_stack_id, &c_stack_id);
			return (1);
		}
		uncover(row_rtack, col_stack, &r_stack_id, &c_stack_id);
		node = node->down;
	}
	return (0);
}
