/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_search_in_dirs.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ommadhi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/15 13:28:06 by ommadhi           #+#    #+#             */
/*   Updated: 2020/11/01 17:44:47 by ommadhi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_autocmp.h"

void					ft_search_in_dirs(t_tocmp cmp, t_dlist **matchs)
{
	DIR					*dir;
	struct dirent		*dirdata;
	t_dlist				*head;

	ft_alloc_node(matchs);
	head = *matchs;
	if (!(dir = opendir(cmp.path)))
		return ;
	while ((dirdata = readdir(dir)))
		if (!ft_strncmp(dirdata->d_name, cmp.tocmp,
		ft_strlen(cmp.tocmp)) && ft_strcmp(".", cmp.tocmp)
		&& ft_strcmp("..", cmp.tocmp))
		{
			head->data = ft_strdup(dirdata->d_name);
			ft_alloc_node(&(head)->next);
			head = head->next;
		}
	closedir(dir);
	ft_memdel((void**)head);
}
