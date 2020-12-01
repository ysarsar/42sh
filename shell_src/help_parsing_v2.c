/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help_parsing_v2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiantrin <hiantrin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/23 04:26:03 by hiantrin          #+#    #+#             */
/*   Updated: 2020/11/23 11:09:02 by hiantrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/sh.h"

void	help_split_and_and(char *line, char **command, int i, char s)
{
	char	c;
	int		j;
	int		a;

	a = 0;
	j = 0;
	while (line[i])
	{
		c = line[i];
		if (c == 34 || c == 39)
			i = count_replace_env(line, i, c);
		else if (line[i] == 92)
			i++;
		else if (line[i] == '$' && (line[i + 1] == '{' || line[i + 1] == '('))
			i = jump_cursh_parent(line, i);
		else if (line[i] == '{' || line[i] == '(')
			i = jump_subshell(line, i);
		else if (c == s && line[i + 1] == s && line[i + 2] != s)
			command[a++] = help_help_split_and_and(line, &i, &j);
		if (line[i] != '\0')
			i++;
	}
	command[a] = ft_strsub(line, j, i - j);
}

int		count_and_and(char *line, char s, int i)
{
	int		count;
	char	c;

	count = 1;
	while (line[i])
	{
		c = line[i];
		if (c == 34 || c == 39)
			i = count_replace_env(line, i, c);
		else if (line[i] == 92)
			i++;
		else if (line[i] == '$' && (line[i + 1] == '{' || line[i + 1] == '('))
			i = jump_cursh_parent(line, i);
		else if (line[i] == '{' || line[i] == '(')
			i = jump_subshell(line, i);
		else if (c == s && line[i + 1] == s && line[i + 2] != s)
		{
			count++;
			i++;
		}
		if (line[i] != '\0')
			i++;
	}
	return (count);
}

char	**split_and_and(char *line, char c)
{
	char	**command;
	int		count;

	count = count_and_and(line, c, 0);
	command = (char **)malloc(sizeof(char *) * count + 1);
	command[count] = NULL;
	help_split_and_and(line, command, 0, c);
	return (command);
}
