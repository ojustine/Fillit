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

t_row			*choose_row(t_row *root, int depth)
{
	t_row	*chosen_one;

	chosen_one = root->down;
	while (chosen_one != root && chosen_one->name != START_SYM + depth)
		chosen_one = chosen_one->down;
	return (chosen_one);
}

int				algorithm_xxx(t_row *root, t_row ***sol, int f_count, int depth)
{
	t_col *col_stack[1000];
	t_row *row_stack[1000];
	int r_stack_id;
	int c_stack_id;

	t_row *row = choose_row(root, depth);
	while (row->name == (START_SYM + depth) && row != root)
	{
		c_stack_id = 0;
		r_stack_id = 0;
		(*sol)[depth] = row;
		row_stack[0] = root;
//			print_solution(*sol, depth + 1, size);
//			write(1, "\n", 1);
		c_stack_id = cover(&row_stack, &col_stack, row->head, &r_stack_id);
		c_stack_id = 0;
		if (algorithm_xxx(root, sol, f_count, depth + 1) == 1) {
			uncover(row_stack, col_stack, &r_stack_id, &c_stack_id);
			return (1);
		}
		uncover(row_stack, col_stack, &r_stack_id, &c_stack_id);
		row = row->down;
	}
	return ((f_count == depth) ? 1 : 0);
}
