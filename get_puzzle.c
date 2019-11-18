/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_puzzle.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojustine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/09 15:01:11 by ojustine          #+#    #+#             */
/*   Updated: 2019/11/14 11:04:04 by ojustine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

/*
**	Adds an element to the list. Makes it circular
*/

static void	add_figs_to_list(t_row **puzzle_root, t_row *fig)
{
	if (!(*puzzle_root)->down)
	{
		(*puzzle_root)->down = *puzzle_root;
		(*puzzle_root)->up = *puzzle_root;
		(*puzzle_root)->name = '\0';
	}
	fig->down = *puzzle_root;
	fig->up = (*puzzle_root)->up;
	fig->up->down = fig;
	fig->down->up = fig;
}

/*
**	Accepts the file descriptor received in the main. Returns a circular doubly
**	linked list, each element of which is one tetramino with parameters
**	(name, coordinates of four objects "#")
*/

t_row		*get_puzzle(int fd)
{
	t_row	*fig;
	t_row	*puzzle_root;
	ssize_t reads;

	puzzle_root = (t_row*)malloc(sizeof(t_row));
	if (!puzzle_root || read(fd, 0, 0) != 0)
		error_exit(1);
	puzzle_root->down = NULL;
	reads = 0;
	while ((reads = get_next_fig(fd, reads, &fig)) > 0)
		add_figs_to_list(&puzzle_root, fig);
	if (reads < 0 || puzzle_root->down == NULL)
		error_exit(1);
	return (puzzle_root);
}
