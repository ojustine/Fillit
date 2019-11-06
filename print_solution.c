/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_solution.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojustine <ojustine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 14:13:53 by ojustine          #+#    #+#             */
/*   Updated: 2019/11/05 15:29:45 by ojustine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

void	print_solution(t_row **sol, int f_count, int size)
{
	char	solution[size * size];
	int 	i;
	int 	j;

	i = -1;
	while (++i < size * size)
		solution[i] = '.';
	i = -1;
	while (++i < f_count)
	{
		j = -1;
		while (++j < 4)
			solution[sol[i]->points[j][Y] * size + sol[i]->points[j][X]] = sol[i]->name;
	}
	i = -size;
	while ((i += size) < size * size)
	{
		write(1, solution + i, size);
		write(1, "\n", 1);
	}
}
