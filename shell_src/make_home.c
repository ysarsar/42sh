/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_home.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mac <mac@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/25 13:52:12 by hiantrin          #+#    #+#             */
/*   Updated: 2020/11/19 02:12:16 by mac              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/sh.h"

char	*help_to_concate(char *first, char **str, int j)
{
	char	*new;

	if (first != NULL)
	{
		new = concate(first, str[j]);
		free_2d(str);
	}
	else
	{
		if (str != NULL)
			free_2d(str);
		new = NULL;
	}
	return (new);
}

char	*check_if_exist(char *command, char **env)
{
	char	**str;
	int		i;
	int		j;

	i = 0;
	str = NULL;
	while (env[i])
	{
		if (str != NULL)
			free_2d(str);
		str = ls(env[i]);
		j = 0;
		while (str[j])
		{
			if (ft_strcmp(str[j], command) == 0)
				break ;
			j++;
		}
		if (str[j] != NULL)
			break ;
		i++;
	}
	return (help_to_concate(env[i], str, j));
}

int		help_replace_home(char **line, int i)
{
	char	**command;
	int		a;
	char	*str;
	char	*new;

	a = i;
	while (line[0][a] && line[0][a] != ' ' && line[0][a] != '\t')
		a++;
	str = ft_strsub(line[0], i + 1, a - (i + 1));
	command = (char **)malloc(sizeof(char *) * 2);
	command[1] = NULL;
	command[0] = ft_strdup("/Users");
	new = str;
	str = check_if_exist(str, command);
	free(new);
	free_2d(command);
	if (str != NULL)
		join_with_something(&line[0], str, a, i);
	i = a;
	return (i);
}

int		help_replace_home2(char **line, int i, t_env *env)
{
	char	*str;
	int		a;

	if (line[0][i + 1] == '/' || line[0][i + 1] == ' ' ||
		line[0][i + 1] == '\0' || line[0][i + 1] == '\t')
	{
		str = check_env("HOME", env);
		a = i + 1;
		if (str != NULL)
			join_with_something(&line[0], str, a, i);
		else
			join_with_anything2(&line[0], str, a, i);
		i = a;
	}
	else
		i = help_replace_home(&line[0], i);
	return (i);
}

char	*replace_home(char *line, t_env *env)
{
	int		i;
	char	c;

	i = 0;
	while (line[i])
	{
		c = line[i];
		if (c == 39)
			i = count_replace_env(line, i, c) + 1;
		else if (c == 92)
			i = i + 2;
		else if (line[i] == '~' && (i == 0 || line[i - 1] == ' ' ||
			line[i - 1] == '\t'))
			i = help_replace_home2(&line, i, env);
		else if (line[i] != '\0')
			i++;
	}
	return (line);
}
