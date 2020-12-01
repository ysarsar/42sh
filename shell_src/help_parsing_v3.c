/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help_parsing_v3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiantrin <hiantrin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/23 04:27:56 by hiantrin          #+#    #+#             */
/*   Updated: 2020/11/23 11:10:12 by hiantrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/sh.h"

int		count_jobs(char *line)
{
	int		i;
	int		count;
	char	c;

	count = 1;
	i = 0;
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
		else if (c == '&' && line[i - 1] != '>'
			&& line[i - 1] != '<')
			count++;
		if (line[i] != '\0')
			i++;
	}
	return (count);
}

void	help_split_jobs(char *line, char **command, int i)
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
		else if (c == '&' && line[i - 1] != '>'
			&& line[i - 1] != '<')
			command[a++] = help_help_bonus(line, &i, &j);
		if (line[i] != '\0')
			i++;
	}
	command[a] = ft_strsub(line, j, i - j);
}

char	**split_job(char *line)
{
	char	**command;
	int		count;

	count = count_jobs(line);
	command = (char **)malloc(sizeof(char *) * count + 1);
	command[count] = NULL;
	help_split_jobs(line, command, 0);
	return (command);
}
