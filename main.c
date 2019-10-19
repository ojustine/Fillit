/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojustine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 15:27:38 by ojustine          #+#    #+#             */
/*   Updated: 2019/10/19 12:10:11 by ojustine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"
#include <stdio.h>

int	main(int argc, char **argv)
{
	int		fd;
	t_fig	*figs;
	t_fig	*root;
	ssize_t reads;

//	if (argc != 2)
//		error_exit(0);
//	if ((fd = open(argv[1], O_RDONLY) < 0))
//		write(2, "error", 5);
	fd = open("test", O_RDONLY);
	if (read(fd, 0, 0))
		error_exit(1);
	while ((reads = get_next_fig(fd, &figs)) > 0)
	{
		add_figs_to_list(&root, figs);
	}
	//close(fd);
	//solve();
	return (0);
}
