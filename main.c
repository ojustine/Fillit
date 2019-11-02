/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojustine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 15:27:38 by ojustine          #+#    #+#             */
/*   Updated: 2019/10/29 15:53:01 by ojustine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

int	main(int argc, char **argv)
{
	int		fd;
	t_row	*fig;
	t_row	*root;
	ssize_t reads;

//	if (argc != 2)
//		error_exit(0);
//	if ((fd = open(argv[1], O_RDONLY) < 0))
//		error_exit(1);
	fd = open("test", O_RDONLY);
	if (read(fd, 0, 0) != 0 || !(root = (t_row*)malloc(sizeof(t_row))))
		error_exit(1);
	root->down = NULL;
	while ((reads = get_next_fig(fd, &fig)) > 0)
		add_figs_to_list(&root, fig);
	close(fd);
	if (reads < 0 || !root->down)
	{
		//!free();//!!!!!!!!!!!
		error_exit(1);
	}
	solve(&root);
	return (0);
}
