/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiantrin <hiantrin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/23 04:53:13 by hiantrin          #+#    #+#             */
/*   Updated: 2020/11/23 11:13:10 by hiantrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/sh.h"

int		redirect_with_fd(char *line, int *i)
{
	int		j;
	char	*str;
	int		b;

	j = i[0];
	j--;
	while (j != -1 && line[j] && line[j] != ' ' &&
		line[j] != '\t' && line[j] != '\n')
		j--;
	j++;
	if (i[0] == j)
		return (-1);
	else
		str = ft_strsub(line, j, i[0] - j);
	b = -1;
	while (str[++b])
		if (str[b] < 48 || str[b] > 57)
		{
			free(str);
			return (-1);
		}
	i[0] = j;
	j = atoi(str);
	free(str);
	return (j);
}

int		type_pipe(char *line, int i)
{
	int type;

	if (line[i] == '>')
		type = 0;
	else if (line[i] == '<')
		type = 2;
	while (line[i] == '<' || line[i] == '>')
	{
		i++;
		type++;
	}
	return (type);
}

int		check_if_is_num(char *file)
{
	int i;

	i = 0;
	while (file[i])
	{
		if (file[i] < 48 || file[i] > 57)
			return (0);
		i++;
	}
	return (1);
}

int		help_to_parse(char **line, int *j, t_process **process)
{
	int		out;
	int		type;
	char	*file;
	int		a;

	a = j[0];
	type = type_pipe(line[0], j[0]);
	out = redirect_with_fd(line[0], &(j[0]));
	while (line[0][a] == '<' || line[0][a] == '>')
		a++;
	file = take_file(&line[0], &a);
	file = filter_for_file(file, g_shell->env);
	if (type == 4 && check_if_is_num(file) == 1 &&
		(line[0][a] == '<' || line[0][a] == '>'))
		return (print_error_num(file, process[0]->errorput));
	if (parse_to_two(file, out, type, &process[0]) == 0)
	{
		g_the_status = 1;
		return (0);
	}
	join_with_anything(&line[0], a, j[0]);
	free(file);
	return (1);
}

int		redirect(t_process **process, int i)
{
	char	c;

	while (process[0]->command[i])
	{
		c = process[0]->command[i];
		if (c == 34 || c == 39)
			i = count_replace_env(process[0]->command, i, c);
		else if (c == 92)
			i++;
		else if (process[0]->command[i] == '$' &&
			(process[0]->command[i + 1] == '{' ||
			process[0]->command[i + 1] == '('))
			i = jump_cursh_parent(process[0]->command, i);
		else if (process[0]->command[i] == '{' || process[0]->command[i] == '(')
			i = jump_subshell(process[0]->command, i);
		else if (process[0]->command[i] == '>' || process[0]->command[i] == '<')
		{
			if (help_to_parse(&process[0]->command, &i, &process[0]) == 0)
				return (0);
			i = 0;
		}
		if (process[0]->command[i] != '\0')
			i++;
	}
	return (1);
}
