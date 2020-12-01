/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_file_tools1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrxy <mrxy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/24 15:42:05 by mrxy              #+#    #+#             */
/*   Updated: 2020/11/30 16:16:02 by mrxy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/sh.h"

int		is_socket(char *pathname)
{
	struct stat	sb;

	if (lstat(pathname, &sb) == -1)
		return (EXIT_FAILURE);
	if (S_ISSOCK(sb.st_mode))
		return (EXIT_SUCCESS);
	return (EXIT_FAILURE);
}

int		file_not_empty(char *pathname)
{
	struct stat	sb;

	if (lstat(pathname, &sb) == -1)
		return (EXIT_FAILURE);
	if (sb.st_size)
		return (EXIT_SUCCESS);
	return (EXIT_FAILURE);
}

int		ft_setuid(char *pathname)
{
	struct stat	sb;

	if (lstat(pathname, &sb) == -1)
		return (EXIT_FAILURE);
	if (sb.st_mode & S_ISUID)
		return (EXIT_SUCCESS);
	return (EXIT_FAILURE);
}

int		writeable_by_owner(char *pathname)
{
	struct stat	sb;

	if (lstat(pathname, &sb) == -1)
		return (EXIT_FAILURE);
	if (S_IWUSR & sb.st_mode)
		return (EXIT_SUCCESS);
	return (EXIT_FAILURE);
}

int		executable_by_owner(char *pathname)
{
	struct stat	sb;

	if (lstat(pathname, &sb) == -1)
		return (EXIT_FAILURE);
	if (S_IXUSR & sb.st_mode)
		return (EXIT_SUCCESS);
	return (EXIT_FAILURE);
}
