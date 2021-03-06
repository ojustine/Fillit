/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojustine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 15:27:38 by ojustine          #+#    #+#             */
/*   Updated: 2019/11/13 15:09:09 by ojustine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

/*
**	Just main function.
*/

int	main(int argc, char **argv)
{
	int		fd;
	t_row	*puzzle;

	if (argc == 2)
	{
		fd = open(argv[1], O_RDONLY);
		if (fd < 0)
			error_exit(1);
		puzzle = get_puzzle(fd);
		close(fd);
		solve(puzzle);
	}
	else
		error_exit(0);
	return (0);
}
