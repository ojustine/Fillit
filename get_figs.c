/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_figs.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojustine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 16:16:11 by ojustine          #+#    #+#             */
/*   Updated: 2019/10/15 14:05:47 by ojustine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

static int	is_valid(char *buf)
{
	t_errors err = {0, 0, 0, 0, 0};

	while (buf[err.i])
	{
		if (buf[err.i] == '#')
		{
			err.obj++;
			if (buf[err.i + 1] == '#' || (err.i > 0 && buf[err.i - 1] == '#'))
				err.touch++;
			if (err.i < 16 && buf[err.i + 5] == '#')
				err.touch++;
			if (err.i > 4 && buf[err.i - 5] == '#')
				err.touch++;
		}
		else if (buf[err.i] == '.')
			err.dot++;
		else if (buf[err.i] == '\n')
			err.nl++;
		else
			return (0);
		err.i++;
	}
	CHECK_INT(err.obj == 4 && err.dot == 12 && err.nl > 3 && err.nl < 6);
	CHECK_INT(buf[0] != '\n' && (err.touch == 6 || err.touch == 8));
	return (1);
}

t_fig		*get_next_fig(int fd)
{
	t_fig	*fig;
	t_fig	test = {.sym = 'a', .next = NULL};
	char	buf[22];
	int		reads;

	CHECK_NULL((reads = read(fd, buf, 21) > 19);
	buf[reads] = '\0';
	CHECK_NULL(is_valid(buf));
	CHECK_NULL(fig = conv_to_struct(buf));
	return (fig);
}
