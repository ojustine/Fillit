/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_figs.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojustine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 16:16:11 by ojustine          #+#    #+#             */
/*   Updated: 2019/10/14 19:20:37 by ojustine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

t_fig	*get_fig(int fd, char sym)
{
	t_fig	*root;
	char	buf[22];
	int		reads;

	while ((reads = read(fd, buf, 21)) > 0)
	{
		buf[reads] = '\0';
		if (reads < 20 || !is_valid_map(buf) || !is_valid_fig(buf))
			return (NULL);
	}
	return (root);
}
