/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solve.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojustine <ojustine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/26 15:08:37 by ojustine          #+#    #+#             */
/*   Updated: 2019/11/06 16:06:09 by ojustine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

static int	get_min_matrix_size(int figs_count)
{
	int size;

	size = 2;
	while (size * size / 4 < figs_count)
		size++;
	return (size);
}

void		solve(t_row **figs_lst)
{
	int		size;
	int 	figs_count;
	t_row	*root;
	t_col	**cols_ptr;
	t_row	**sol;

	cols_ptr = NULL;
	figs_count = (*figs_lst)->up->name - START_SYM + 1;
	if (!(sol = (t_row**)malloc(sizeof(t_row*) * figs_count)))
		error_exit(1);
	size = get_min_matrix_size(figs_count);
	root = create_cols_rows(*figs_lst, &cols_ptr, &size);
	link_matrix(root, cols_ptr, size);
	while (algorithm_x(root, &sol, figs_count, 0) != 1)
	{
		destroy_matrix(root, cols_ptr, size);
		size++;
		root = create_cols_rows(*figs_lst, &cols_ptr, &size);
		link_matrix(root, cols_ptr, size);
	}
	print_solution(sol, figs_count, size);
}
