/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_help.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiantrin <hiantrin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/23 04:51:32 by hiantrin          #+#    #+#             */
/*   Updated: 2020/10/25 11:00:33 by hiantrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/sh.h"

int		print_error_num(char *file, int error)
{
	ft_putstr_fd("42sh: syntax error near unexpected token `",
		error);
	ft_putstr_fd(file, error);
	ft_putendl_fd("'", error);
	g_the_status = 1;
	return (0);
}

int		help_type_one(char *file, int error)
{
	struct stat	l;
	int			i;

	if (lstat(file, &l) == -1)
	{
		i = open(file, O_CREAT, 0644);
		close(i);
	}
	lstat(file, &l);
	if (S_ISDIR(l.st_mode))
		return (print_i_d(file, error));
	return (1);
}

int		print_p_d(char *file, int pipe)
{
	ft_putstr_fd("42sh: ", pipe);
	ft_putstr_fd(file, pipe);
	ft_putendl_fd(": Permission denied", pipe);
	return (0);
}

int		print_i_d(char *file, int pipe)
{
	ft_putstr_fd("42sh: ", pipe);
	ft_putstr_fd(file, pipe);
	ft_putendl_fd(": Is a directory", pipe);
	return (0);
}

int		error_type_three(char *file, int error)
{
	struct stat l;

	if (lstat(file, &l) == -1)
		return (print_n_x(file, error));
	if (S_ISDIR(l.st_mode))
		return (print_i_d(file, error));
	return (1);
}
