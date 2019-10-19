/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_figs_to_list.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojustine <ojustine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/18 17:48:04 by ojustine          #+#    #+#             */
/*   Updated: 2019/10/19 11:57:59 by ojustine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

void	add_figs_to_list(t_fig **root, t_fig *figs)
{
	t_fig *tmp;

	if (!*root)
	{
		*root = figs;
		(*root)->next = *root;
		(*root)->prev = *root;
	}
	tmp = (*root)->prev;
	tmp->next = figs;
	tmp->next->next = *root;
	tmp->next->prev = tmp;
	(*root)->prev = tmp->next;
}
