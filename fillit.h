/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojustine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 14:33:12 by ojustine          #+#    #+#             */
/*   Updated: 2019/10/19 11:27:35 by ojustine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLIT_H
# define FILLIT_H
# define X 0
# define Y 1
# define CHECK_NULL(x) if (!(x)) return (NULL);
# define CHECK_INT(x) if (!(x)) return (0);

# include <stdlib.h>
# include <string.h>
# include <fcntl.h>
# include <unistd.h>

typedef struct		s_fig
{
	char			sym;
	int				points[4][2];
	struct s_fig	*next;
	struct s_fig	*prev;
}					t_fig;

typedef struct		s_errors
{
	int				touch;
	int				nl;
	int				obj;
	int				dot;
	ssize_t			i;
}					t_errors;
ssize_t				get_next_fig(int fd, t_fig **figs);
void				error_exit(int err_code);
void				add_figs_to_list(t_fig **root, t_fig *figs);
#endif
