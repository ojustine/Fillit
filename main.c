/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojustine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 15:27:38 by ojustine          #+#    #+#             */
/*   Updated: 2019/10/14 16:29:54 by ojustine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

int	main(int argc, char **argv)
{
	int		fd;
	char	*buf;
	t_fig	*fig;

	if (argc != 2)
		write(2, "usage: ./fillit source_file", 27);
	fd = open(argv[1], O_RDONLY);
	if ((parts = get_all_figs(fd)) == NULL)
		write(2, "error", 5);
	close(fd);
	//solve();
	return (0);
}
