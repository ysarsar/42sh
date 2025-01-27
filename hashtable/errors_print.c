/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_print.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrxy <mrxy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/31 06:11:13 by ysarsar           #+#    #+#             */
/*   Updated: 2020/12/01 00:48:33 by mrxy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/sh.h"

void		ft_hash_error(char *str)
{
	if (str)
	{
		ft_putstr_fd("42sh: hash: ", 2);
		ft_putstr_fd(str, 2);
		ft_putendl_fd(": invalid option", 2);
		ft_putstr_fd("42sh: usage: ", 2);
		ft_putendl_fd("hash [-lr] [-p pathname] [-dt] [name ...]", 2);
	}
	else
	{
		ft_putendl_fd("42sh: hash: -p: option requires an argument", 2);
		ft_putstr_fd("42sh: usage: ", 2);
		ft_putendl_fd("hash [-lr] [-p pathname] [-dt] [name ...]", 2);
	}
}

void		l_flag_error(char *str)
{
	ft_putstr_fd("42sh: hash: ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd(": not found\n", 2);
}

void		l_flag_print(char *value, char *key)
{
	ft_putstr("builtin hash -p ");
	ft_putstr(value);
	ft_putchar(' ');
	ft_putendl(key);
}

char		*absolute_path(char *path, char *command)
{
	char	*str1;
	char	*str2;

	str1 = ft_strjoin(path, "/");
	str2 = ft_strjoin(str1, command);
	ft_strdel(&str1);
	return (str2);
}
