/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_solution.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojustine <ojustine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 14:13:53 by ojustine          #+#    #+#             */
/*   Updated: 2019/11/13 15:07:35 by ojustine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

/*
**	Converts a solution consisting of several t_row structures with parameters
**	into a string and prints it.
*/

void	print_solution(t_row **sol, int f_count, int size)
{
	char	str_sol[size * size];
	int		i;
	int		obj;
	int		str_obj;

	i = -1;
	while (++i < size * size)
		str_sol[i] = '.';
	i = -1;
	while (++i < f_count)
	{
		obj = -1;
		while (++obj < MODE)
		{
			str_obj = sol[i]->objs[obj][Y] * size + sol[i]->objs[obj][X];
			str_sol[str_obj] = sol[i]->name;
		}
	}
	i = -size;
	while ((i += size) < size * size)
	{
		write(1, str_sol + i, size);
		write(1, "\n", 1);
	}
}
