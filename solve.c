/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solve.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojustine <ojustine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/26 15:08:37 by ojustine          #+#    #+#             */
/*   Updated: 2019/11/01 14:45:42 by ojustine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

static int	get_min_matrix_size(char name)
{
	int size;
	int count;

	count = name - START_SYM + 1;
	size = 2;
	while (size * size / 4 < count)
		size++;
	return (size);
}

void		solve(t_row **figs_lst)
{
	int		size;
	int 	figs_count;
	t_row	*root;
	t_col	**cols_ptr;
	t_row	*sol[(*figs_lst)->up->name - START_SYM + 1];

	cols_ptr = NULL;
	figs_count = (*figs_lst)->up->name - START_SYM + 1;
	size = get_min_matrix_size((*figs_lst)->up->name);
	root = create_cols_rows(*figs_lst, &cols_ptr, size);
	link_matrix(root, cols_ptr, size);
	int i = 1;
	while (algorithm_x(root, sol, figs_count, 0) != 1)
	{
		destroy_matrix(root, cols_ptr, size);
		size++;
		root = create_cols_rows(*figs_lst, &cols_ptr, size);
		link_matrix(root, cols_ptr, size);
	}
}
