/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_alias.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ommadhi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 18:37:27 by ommadhi           #+#    #+#             */
/*   Updated: 2020/11/27 09:52:26 by ommadhi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_alias.h"

void			ft_print_one_alias(char *alias, t_alias *g_alias)
{
	int		flag;

	flag = 0;
	while (g_alias)
	{
		if (!ft_strcmp(g_alias->alias, alias))
		{
			ft_putstr("alias ");
			ft_put4str(g_alias->alias, "=", g_alias->value, "\n");
			flag = 1;
		}
		g_alias = g_alias->next;
	}
	if (!flag)
	{
		g_the_status = 1;
		ft_put4str("42sh: alias: ", alias, ": not found", "\n");
	}
	else
		g_the_status = 0;
}

int			ft_tab_len(char **args)
{
	int i;

	i = 0;
	while (args[i])
		i++;
	return (i);
}

int			ft_replace_alias_value(t_alias **h, char **cmd)
{
	t_alias		*head;

	head = *h;
	if (head && !head->next && !ft_strcmp(cmd[0], head->alias))
	{
		ft_strdel(&head->value);
		head->value = ft_strdup(cmd[1]);
		ft_free_tab(cmd);
		return (1);
	}
	while (head && head->next)
	{
		if (!ft_strcmp(cmd[0], head->alias))
		{
			ft_strdel(&head->value);
			head->value = ft_strdup(cmd[1]);
			ft_free_tab(cmd);
			return (1);
		}
		head = head->next;
	}
	return (0);
}

void			ft_set_alias(char *cmd, t_alias **g_alias)
{
	char		**split_cmd;
	t_alias		*head;

	head = NULL;
	if (!(split_cmd = ft_strsplit(cmd, '=')))
		return ;
	if (!*g_alias)
	{
		ft_alloc_alias_node(g_alias);
		(*g_alias)->alias = ft_strdup(split_cmd[0]);
		(*g_alias)->value = ft_strdup(split_cmd[1]);
		ft_free_tab(split_cmd);
		return ;
	}
	head = *g_alias;
	if (ft_replace_alias_value(&head, split_cmd))
	{
		ft_free_tab(split_cmd);
		return ;
	}
	while (head && head->next)
		head = head->next;
	ft_alloc_alias_node(&head->next);
	head = head->next;
	head->alias = ft_strdup(split_cmd[0]);
	head->value = ft_strdup(split_cmd[1]);
	ft_free_tab(split_cmd);
}

void			ft_alias(char **args, t_alias **g_alias)
{
	int		i;

	i = 1;
	if (ft_tab_len(args) == 1)
		ft_print_aliases(*g_alias);
	else
	{
		while (args[i])
		{
			if (ft_strchr(args[i], '='))
				ft_set_alias(args[i], g_alias);
			else
				ft_print_one_alias(args[i], *g_alias);
			i++;
		}
	}
}
