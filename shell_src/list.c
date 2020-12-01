/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiantrin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/23 04:31:38 by hiantrin          #+#    #+#             */
/*   Updated: 2020/10/23 04:31:39 by hiantrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/sh.h"

char	*get_name(char *environ)
{
	char	*str;
	int		i;

	i = 0;
	while (environ[i] && environ[i] != '=')
		i++;
	str = ft_strsub(environ, 0, i);
	return (str);
}

char	*get_environ(char *environ)
{
	char	*str;
	int		i;
	int		j;

	j = 0;
	while (environ[j] && environ[j] != '=')
		j++;
	j++;
	i = j;
	while (environ[i])
		i++;
	str = ft_strsub(environ, j, i - j);
	return (str);
}

t_env	*create_next(char *environ)
{
	t_env	*env;

	if (environ == NULL)
		env = NULL;
	else
	{
		env = (t_env *)malloc(sizeof(t_env));
		env->name = get_name(environ);
		env->environ = get_environ(environ);
		env->flag = 0;
		env->next = NULL;
	}
	return (env);
}

t_env	*create_env(char **environ)
{
	t_env	*head;
	t_env	*env;
	t_env	*next;
	int		i;

	i = 0;
	env = create_next(environ[i]);
	head = env;
	if (environ[i])
		i++;
	while (environ[i])
	{
		next = create_next(environ[i]);
		env->next = next;
		env = env->next;
		i++;
	}
	return (head);
}
