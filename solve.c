/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solve.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojustine <ojustine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/26 15:08:37 by ojustine          #+#    #+#             */
/*   Updated: 2019/11/15 11:52:11 by ojustine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

/*
**	Accepts a figures list. Free it.
*/

static void	free_puzzle(t_row *puzzle)
{
	t_row	*tmp;
	t_row	*last_fig;

	last_fig = puzzle->up;
	while (puzzle != last_fig)
	{
		tmp = puzzle;
		puzzle = puzzle->down;
		free(tmp);
	}
	free(puzzle);
}

/*
**	Accepts a number of figures. Returns the size of the minimum square
**	in which these figures can be placed.
**	Explanation:
**	All figures consist of four objects ("#").
**	That is, a square with side N can contain (N ^ 2) / 4 figures,
**	if all of them are squares (at best case).
*/

static int	get_min_matrix_size(int figs_count)
{
	int size;

	size = MODE / 2;
	while (size * size / MODE < figs_count)
		size++;
	return (size);
}

/*
**	It brings together all parts of the program.
**	Using an algorithm X, tries to place the figures in a square with side size.
**	If the figures do not fit, increase the size and try again.
**	Repeats until solution is found.
**	Before exiting, cleans the memory.
*/

void		solve(t_row *puzzle)
{
	int		size;
	int		figs_count;
	t_row	*root;
	t_col	**cols_ptr;
	t_row	**sol;

	cols_ptr = NULL;
	figs_count = puzzle->up->name - START_NAME + 1;
	if (!(sol = (t_row**)malloc(sizeof(t_row*) * figs_count)))
		error_exit(1);
	size = get_min_matrix_size(figs_count);
	root = create_cols_rows(puzzle, &cols_ptr, &size);
	link_matrix(root, cols_ptr, size);
	while (algorithm_xxx(root, &sol, figs_count, 0) != 1)
	{
		destroy_matrix(root, cols_ptr, size);
		size++;
		root = create_cols_rows(puzzle, &cols_ptr, &size);
		link_matrix(root, cols_ptr, size);
	}
	print_solution(sol, figs_count, size);
	free(sol);
	free_puzzle(puzzle);
	destroy_matrix(root, cols_ptr, size);
}
