/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_figs.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojustine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 16:16:11 by ojustine          #+#    #+#             */
/*   Updated: 2019/10/16 13:52:59 by ojustine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

static int		is_valid(char *buf)
{
	t_errors err = {0, 0, 0, 0, 0};

	CHECK_INT(buf[4] == '\n' && buf[9] == '\n' && buf[14] == '\n'
	&& buf[19] == '\n');
	while (buf[err.i])
	{
		if (buf[err.i] == '#')
		{
			err.obj++;
			if (buf[err.i + 1] == '#' || (err.i > 0 && buf[err.i - 1] == '#')
			|| (err.i < 16 && buf[err.i + 5] == '#')
			|| (err.i > 4 && buf[err.i - 5] == '#'))
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

static t_fig	*conv_str_to_fig(char *buf, char sym)
{
	t_fig	*fig;
	int		i;
	int		j;
	int		shift_x;
	int		shift_y;

	CHECK_NULL(fig = (t_fig*)malloc(sizeof(t_fig)));
	fig->sym = sym;
	shift_x = shift_fig(buf, X);
	shift_y = shift_fig(buf, Y);
	i = 0;
	while (++i < 4)
	{
		j = 0;
		while (++j < 4)
		{
			if (buf[i * 5 + j] == '#') {
				fig->points[i][X] = (j - shift_x);
				fig->points[i][Y] = (i - shift_y);
			}
			j++;
		}
		i++;
	}
	return (fig);
}

t_fig			*get_next_fig(int fd)
{
	t_fig	*fig;
	char	buf[22];
	int		reads;

	CHECK_NULL((reads = read(fd, buf, 21) > 19);
	if (reads == 20)
		reads++
	buf[reads] = '\0';
	CHECK_NULL(is_valid(buf));
	CHECK_NULL(fig = conv_str_to_fig(buf));
	return (fig);
}
