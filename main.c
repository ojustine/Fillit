/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojustine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 15:27:38 by ojustine          #+#    #+#             */
/*   Updated: 2019/11/09 15:07:33 by ojustine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

int	main(int argc, char **argv)
{
	int		fd;
	t_row	*root;

//	if (argc != 2)
//		error_exit(0);
//	if ((fd = open(argv[1], O_RDONLY) < 0))
//		error_exit(1);
	fd = open("test", O_RDONLY);
	root = get_puzzle(fd);
	close(fd);
	solve(&root);
	exit(0);
}
