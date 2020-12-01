/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_search_for_bin.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ommadhi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/15 11:47:17 by ommadhi           #+#    #+#             */
/*   Updated: 2020/11/01 17:45:01 by ommadhi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_autocmp.h"

static char				**ft_get_env_path(void)
{
	t_env				*env;
	char				*path;
	char				**pathtab;

	env = g_shell->env;
	path = NULL;
	pathtab = NULL;
	while (env)
	{
		if (!ft_strcmp(env->name, "PATH"))
			break ;
		env = env->next;
	}
	if (env)
		if (!(path = ft_strdup(env->environ)))
			return (NULL);
	if (!(pathtab = ft_strsplit(path, ':')))
		return (NULL);
	ft_strdel(&path);
	return (pathtab);
}

void					ft_search_for_bin(t_tocmp cmp, t_dlist **matchs)
{
	char				**envpaths;
	int					i;
	DIR					*dir;
	struct dirent		*dirdata;
	t_dlist				*head;

	i = -1;
	if (!(envpaths = ft_get_env_path()))
		return ;
	ft_alloc_node(matchs);
	head = *matchs;
	while (envpaths[++i])
	{
		if (!(dir = opendir(envpaths[i])))
			return ;
		while ((dirdata = readdir(dir)))
			if (!ft_strncmp(dirdata->d_name, cmp.tocmp, ft_strlen(cmp.tocmp)))
			{
				head->data = ft_strdup(dirdata->d_name);
				ft_alloc_node(&(head)->next);
				head = head->next;
			}
		closedir(dir);
	}
	ft_free_tab(envpaths);
	ft_memdel((void**)head);
}
