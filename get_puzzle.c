/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_puzzle.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojustine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/09 15:01:11 by ojustine          #+#    #+#             */
/*   Updated: 2019/11/09 16:25:20 by ojustine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

/*
**	Adds an element to the list. Makes list circular
*/

static void	add_figs_to_list(t_row **root, t_row *fig)
{
	t_row *tmp;

	if (!(*root)->down)
	{
		(*root)->down = *root;
		(*root)->up = *root;
		(*root)->name = '\0';
	}
	tmp = (*root)->up;
	tmp->down = fig;
	tmp->down->down = *root;
	tmp->down->up = tmp;
	(*root)->up = tmp->down;
}

/*
**	Accepts the file descriptor received in the main. Returns a circular doubly
**	linked list, each element of which is one tetramino with parameters
**	(name, coordinates of four objects "#")
*/

t_row		*get_puzzle(int fd)
{
	t_row	*fig;
	t_row	*root;
	ssize_t reads;

	if (read(fd, 0, 0) != 0 || !(root = (t_row*)malloc(sizeof(t_row))))
		error_exit(1);
	root->down = NULL;
	while ((reads = get_next_fig(fd, &fig)) > 0)
		add_figs_to_list(&root, fig);
	if (reads < 0 || !root->down)
		error_exit(1);
	return (root);
}
