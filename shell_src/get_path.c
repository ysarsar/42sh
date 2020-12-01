/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mac <mac@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/17 14:26:38 by hiantrin          #+#    #+#             */
/*   Updated: 2020/10/08 01:07:00 by mac              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/sh.h"

int		n_str(char *path)
{
	int				i;
	DIR				*dir;
	struct dirent	*dirent;

	i = 0;
	dir = opendir(path);
	if (dir == NULL)
		return (0);
	while ((dirent = readdir(dir)))
	{
		if (dirent->d_name[0] != '.')
			i++;
	}
	closedir(dir);
	return (i);
}

void	remplir(char **str, char *path)
{
	int				i;
	struct dirent	*dirent;
	DIR				*dir;

	i = 0;
	dir = opendir(path);
	if (dir == NULL)
		return ;
	while ((dirent = readdir(dir)))
	{
		if (dirent->d_name[0] != '.')
		{
			str[i] = ft_strdup(dirent->d_name);
			i++;
		}
	}
	closedir(dir);
}

char	**ls(char *path)
{
	char	**str;
	int		i;

	i = n_str(path);
	str = (char **)malloc(sizeof(char *) * (i + 1));
	str[i] = NULL;
	remplir(str, path);
	return (str);
}
