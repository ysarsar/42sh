/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrxy <mrxy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/23 06:52:20 by mrxy              #+#    #+#             */
/*   Updated: 2020/11/30 16:38:33 by mrxy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/sh.h"

int		test_file(char **args)
{
	int		args_len;

	args_len = ft_argslen(args);
	if (args_len < 4)
	{
		if (ft_strcmp(args[1], "-b") == 0)
			return (block_special(args[2]));
		else if (ft_strcmp(args[1], "-c") == 0)
			return (character_special(args[2]));
		else if (ft_strcmp(args[1], "-d") == 0)
			return (is_dir(args[2]));
		else if (ft_strcmp(args[1], "-e") == 0)
			return (file_exist(args[2]));
		else if (ft_strcmp(args[1], "-f") == 0)
			return (is_file(args[2]));
		else if (ft_strcmp(args[1], "-g") == 0)
			return (ft_setgid(args[2]));
		else
			return (test_file_complete(args));
	}
	else
		ft_putendl_fd("42sh: test: too many arguments", 2);
	return (2);
}

int		block_special(char *pathname)
{
	struct stat	sb;

	if (lstat(pathname, &sb) == -1)
		return (EXIT_FAILURE);
	if (S_ISBLK(sb.st_mode))
		return (EXIT_SUCCESS);
	return (EXIT_FAILURE);
}

int		character_special(char *pathname)
{
	struct stat	sb;

	if (lstat(pathname, &sb) == -1)
		return (EXIT_FAILURE);
	if (S_ISCHR(sb.st_mode))
		return (EXIT_SUCCESS);
	return (EXIT_FAILURE);
}

int		is_dir(char *pathname)
{
	struct stat	sb;

	if (lstat(pathname, &sb) == -1)
		return (EXIT_FAILURE);
	if (S_ISDIR(sb.st_mode))
		return (EXIT_SUCCESS);
	return (EXIT_FAILURE);
}

int		file_exist(char *pathname)
{
	if (access(pathname, F_OK) == 0)
		return (EXIT_SUCCESS);
	return (EXIT_FAILURE);
}
