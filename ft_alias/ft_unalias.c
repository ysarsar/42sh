/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unalias.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ommadhi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/26 12:28:27 by ommadhi           #+#    #+#             */
/*   Updated: 2020/11/26 12:44:29 by ommadhi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_alias.h"

void			ft_del_node(t_alias **alias)
{
	free((*alias)->alias);
	free((*alias)->value);
	free(*alias);
	*alias = NULL;
}

int			ft_unset_alias(char *cmd, t_alias **aliases)
{
	t_alias		*prev;
	t_alias		*tmp;

	tmp = *aliases;
	if (tmp && !ft_strcmp(cmd, tmp->alias))
	{
		*aliases = tmp->next;
		ft_del_node(&tmp);
		return (1);
	}
	while (tmp && ft_strcmp(cmd, tmp->alias))
	{
		prev = tmp;
		tmp = tmp->next;
	}
	if (!tmp)
		return (0);
	prev->next = tmp->next;
	ft_del_node(&tmp);
	return (1);
}

void			ft_unalias(char **args, t_alias **alias)
{
	int		i;

	i = 1;
	if (!args[1])
	{
		g_the_status = 1;
		ft_putendl("42sh: unalias: usage: unalias name [name ...]");
		return ;
	}
	else
		while (args[i])
		{
			if (!ft_unset_alias(args[i], alias))
			{
				ft_put4str("42sh: unalias: no such element:",
				args[i], "\n", "");
				g_the_status = 1;
			}
			else
				g_the_status = 0;
			i++;
		}
}
