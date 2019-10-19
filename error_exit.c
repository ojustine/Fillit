/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojustine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/18 10:56:18 by ojustine          #+#    #+#             */
/*   Updated: 2019/10/18 10:56:18 by ojustine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

void error_exit(int err_code)
{
	if (err_code == 0)
	{
		write(2, "usage: ./fillit source_file", 27);
	}
	else if (err_code == 1)
	{
		write(2, "error", 5);
	}
	exit(err_code);
}
