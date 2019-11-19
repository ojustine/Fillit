/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojustine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 14:33:12 by ojustine          #+#    #+#             */
/*   Updated: 2019/11/15 11:52:11 by ojustine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLIT_H
# define FILLIT_H
# define X 0
# define Y 1
# define MAX_FIGS_COUNT 26
# define START_SYM 'A'
# define OBJ_SYM '#'
# if (START_SYM < 32 || START_SYM > 126 || START_SYM + MAX_FIGS_COUNT > 126)
#  error "non-printable characters"
# endif
# if (MAX_FIGS_COUNT < 1)
#  error "the number of figures cannot be less than one"
# endif
# if (MAX_FIGS_COUNT > 100)
#  warning "will seek a solution for years"
# endif

# include <stdlib.h>
# include <string.h>
# include <fcntl.h>
# include <unistd.h>

typedef struct		s_row
{
	char			name;
	int				objs[4][2];
	int				length;
	struct s_row	*down;
	struct s_row	*up;
	struct s_node	*head;
}					t_row;

typedef struct		s_col
{
	int				length;
	struct s_node	*head;
}					t_col;

typedef struct		s_node
{
	struct s_node	*up;
	struct s_node	*down;
	struct s_node	*left;
	struct s_node	*right;
	struct s_row	*row;
	struct s_col	*col;
}					t_node;

typedef struct		s_tet_params
{
	int				touches;
	int				nl;
	int				obj;
	int				dot;
	ssize_t			i;
}					t_tet_params;

ssize_t				get_next_fig(int fd, ssize_t prev_reads, t_row **figs);
void				error_exit(int err_code);
t_row				*get_puzzle(int fd);
void				solve(t_row *puzzle);
t_row				*create_cols_rows(t_row *puzzle, t_col ***cols_ptr,
					int *size);
void				link_matrix(t_row *root, t_col **cols, int size);
void				destroy_matrix(t_row *root, t_col **cols, int size);
int					algorithm_xxx(t_row *root, t_row ***sol, int f_count,
					int depth);
void				print_solution(t_row **sol, int figs_count, int size);
#endif
