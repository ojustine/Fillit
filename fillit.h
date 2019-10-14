/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojustine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 14:33:12 by ojustine          #+#    #+#             */
/*   Updated: 2019/10/14 16:19:24 by ojustine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLIT_H
# define FILLIT_H
# define MALLCHECK(x) if (!(x)) return (NULL);
# define ISNEG(X) (((X) < 0) ? (1) : (0))

//# include <limits.h>
# include <stdlib.h>
# include <string.h>
# include <fcntl.h>
# include <unistd.h>

typedef struct		s_fig
{
	char			sym;
	int				points[4][2];
	struct s_part	*next;
}					t_fig;

//# if (BUFF_SIZE < 1)
//#  error "BUFF_SIZE must be strictly positive"
//# endif
//# if (BUFF_SIZE > SSIZE_MAX)
//#  warning "BUFF_SIZE current value may cause a stack overflow"
//# endif
#endif
