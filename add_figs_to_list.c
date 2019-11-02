/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_figs_to_list.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojustine <ojustine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/18 17:48:04 by ojustine          #+#    #+#             */
/*   Updated: 2019/10/29 15:53:01 by ojustine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

void	add_figs_to_list(t_row **root, t_row *fig)
{
	t_row *tmp;

	if (!(*root)->down)
	{
		(*root)->down = *root;
		(*root)->up = *root;
		(*root)->name = '*';
	}
	tmp = (*root)->up;
	tmp->down = fig;
	tmp->down->down = *root;
	tmp->down->up = tmp;
	(*root)->up = tmp->down;
}
