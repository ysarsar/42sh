/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variables.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiantrin <hiantrin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/02 04:25:12 by hiantrin          #+#    #+#             */
/*   Updated: 2020/10/25 10:53:25 by hiantrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/sh.h"

int		search_if_is_there(char *str, t_env *list)
{
	char	*new;

	new = get_name(str);
	while (list)
	{
		if (ft_strcmp(list->name, new) == 0)
		{
			free(new);
			return (list->flag);
		}
		list = list->next;
	}
	return (2);
}

void	replace_old_env(t_env **save, t_env *list, char *str, int type)
{
	char	*new;
	char	*environ;
	t_env	*head;

	new = get_name(str);
	environ = check_env(new, list);
	head = save[0];
	while (head)
	{
		if (ft_strcmp(head->name, new) == 0 && (type == 0 || type == 1))
		{
			free(head->environ);
			head->environ = environ;
			head->flag = type;
			free(new);
			return ;
		}
		else if (ft_strcmp(head->name, new) == 0 && type == 2)
			head->flag = 2;
		head = head->next;
	}
}

void	replace_variable(char *str, t_env **list, int type)
{
	char	*new;
	t_env	*head;

	new = get_name(str);
	head = list[0];
	while (head)
	{
		if (ft_strcmp(head->name, new) == 0)
		{
			if (type == 1 || type == 2)
				head->flag = 1;
			else if (type == 0)
				head->flag = 0;
			free(new);
			return ;
		}
		head = head->next;
	}
}

void	replace_env_variable(t_env *save)
{
	t_env	*head;
	char	*str;

	head = g_shell->env;
	while (save)
	{
		str = save->name;
		while (head)
		{
			if (ft_strcmp(head->name, str) == 0)
			{
				head->flag = 0;
				return ;
			}
			head = head->next;
		}
		save = save->next;
	}
}

char	**manage_variables(char **argv, t_env **env)
{
	int		i;
	t_env	*save;
	int		type;

	i = 0;
	save = NULL;
	while (argv[i])
	{
		if (ft_strchr(argv[i], '=') == NULL || check_set(argv[i]) == 0)
		{
			env[0] = save;
			replace_env_variable(save);
			return (create_new_argv(argv, i));
		}
		else
		{
			type = search_if_is_there(argv[i], g_shell->env);
			help_setenv(argv[i], &save);
			replace_old_env(&save, g_shell->env, argv[i], type);
			help_setenv(argv[i], &g_shell->env);
			replace_variable(argv[i], &g_shell->env, type);
		}
		i++;
	}
	return (help_re_null(save, &env[0], argv));
}
