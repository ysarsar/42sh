/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_search_in_env.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ommadhi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/31 16:31:43 by ommadhi           #+#    #+#             */
/*   Updated: 2020/10/31 16:53:10 by ommadhi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_autocmp.h"

void		ft_search_in_env(t_tocmp cmp, t_dlist **matchs)
{
	t_env	*env;
	t_dlist	*head;

	ft_alloc_node(matchs);
	head = *matchs;
	env = g_shell->env;
	while (env)
	{
		if (!ft_strncmp(env->name, cmp.tocmp, ft_strlen(cmp.tocmp)))
		{
			head->data = ft_strdup(env->name);
			ft_alloc_node(&(head)->next);
			head = head->next;
		}
		env = env->next;
	}
	ft_memdel((void**)head);
}
