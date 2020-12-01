/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_with_env.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mac <mac@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/23 04:56:00 by hiantrin          #+#    #+#             */
/*   Updated: 2020/11/19 23:22:24 by mac              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/sh.h"

char	*check_env(char *str, t_env *env)
{
	if (ft_strcmp(str, "?") == 0)
		return (ft_itoa(g_the_status));
	while (env)
	{
		if (ft_strcmp(str, env->name) == 0)
			return (ft_strdup(env->environ));
		else
			env = env->next;
	}
	return (NULL);
}

char	*help_replace_env(int *a, char *line, int i, t_env *env)
{
	char	*new;
	char	*str;

	if (line[*a] == '{')
	{
		*a = to_the_end_parent(line, i, '}', '{');
		new = ft_strsub(line, i + 2, *a - (i + 2));
		(*a)++;
	}
	else if (line[*a] == '(')
		return (trait_the_parentheses_help(&a[0], i, line));
	else
	{
		while (line[*a] == '_' || (line[*a] >= 'a' && line[*a] <= 'z') ||
			(line[*a] >= 'A' && line[*a] <= 'Z') ||
			(line[*a] >= '0' && line[*a] <= '9'))
			(*a)++;
		new = ft_strsub(line, i + 1, *a - (i + 1));
	}
	if (new[0] == '\0')
		str = ft_strsub(line, i, *a - i);
	else
		str = check_env(new, env);
	free(new);
	return (str);
}

void	join_with_something(char **line, char *str, int a, int i)
{
	char	*first;
	char	*new;

	first = ft_strsub(*line, 0, i);
	new = ft_strjoin(first, str);
	free(first);
	free(str);
	str = ft_strdup(&line[0][a]);
	free(*line);
	line[0] = ft_strjoin(new, str);
	free(new);
	free(str);
}

void	join_with_anything2(char **line, char *str, int a, int i)
{
	char	*first;

	first = ft_strsub(*line, 0, i);
	str = ft_strdup(&line[0][a]);
	free(*line);
	line[0] = ft_strjoin(first, str);
	free(first);
	free(str);
}

char	*replace_with_env(char *line, t_env *env, int b, int i)
{
	char	*str;
	int		a;
	char	c;

	b = 0;
	while (line[i])
	{
		c = line[i];
		if (c == 39)
			i = count_replace_env(line, i, c) + 1;
		else if (c == 92)
			i = i + 2;
		else if (line[i] == '$')
		{
			a = i + 1;
			str = help_replace_env(&a, line, i, env);
			if (str != NULL)
				b = ft_strlen(str);
			mini_mini_norme(&line, str, a, i);
			i = i + b;
		}
		else if (line[i] != '\0')
			i++;
	}
	return (line);
}
