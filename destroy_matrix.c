/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy_matrix.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojustine <ojustine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/31 15:17:01 by ojustine          #+#    #+#             */
/*   Updated: 2019/10/31 17:13:40 by ojustine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

/*
**	Frees all memory allocated for the matrix structures.
*/

void	destroy_matrix(t_row *root, t_col **cols, int size)
{
	t_row	*to_free_row;
	t_row	*last_row;
	t_node	*to_free_node;
	int		i;

	last_row = root->up;
	while (root != last_row)
	{
		to_free_row = root;
		root = root->down;
		free(to_free_row);
	}
	free(root);
	i = -1;
	while (++i < size * size)
	{
		while (cols[i]->length--)
		{
			to_free_node = cols[i]->head;
			cols[i]->head = cols[i]->head->down;
			free(to_free_node);
		}
		free(cols[i]);
	}
	free(cols);
}
