/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojustine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 15:27:38 by ojustine          #+#    #+#             */
/*   Updated: 2019/10/17 11:07:38 by ojustine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"
#include <stdio.h>

int	main(int argc, char **argv)
{
	int		fd;
	t_fig	*fig;

	if (argc != 2)
		write(2, "usage: ./fillit source_file", 27);
//	if ((fd = open(argv[1], O_RDONLY) < 0))
//		write(2, "error", 5);
	fd = open("test", O_RDONLY);
//	if ((parts = get_all_figs(fd)) == NULL)
//		write(2, "error", 5);
	fig = get_next_fig(fd);
	//close(fd);
	printf("%d", fig->points[0][0]);
	//write(1, fig->sym, 1);
	//solve();
	return (0);
}
