/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mac <mac@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/23 03:45:49 by hiantrin          #+#    #+#             */
/*   Updated: 2020/11/28 13:32:09 by mac              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/sh.h"

int		get_command_type(char *command)
{
	if (ft_strcmp(command, "exit") == 0)
		return (COMMAND_EXIT);
	else if (ft_strcmp(command, "cd") == 0)
		return (COMMAND_CD);
	else if (ft_strcmp(command, "jobs") == 0)
		return (COMMAND_JOBS);
	else if (ft_strcmp(command, "fg") == 0)
		return (COMMAND_FG);
	else if (ft_strcmp(command, "bg") == 0)
		return (COMMAND_BG);
	else if (ft_strcmp(command, "export") == 0)
		return (COMMAND_EXPORT);
	else if (ft_strcmp(command, "unset") == 0)
		return (COMMAND_UNSET);
	else if (ft_strcmp(command, "set") == 0)
		return (COMMAND_SET);
	else if (ft_strcmp(command, "echo") == 0)
		return (COMMAND_ECHO);
	else if (ft_strcmp(command, "type") == 0)
		return (COMMAND_TYPE);
	else if (ft_strcmp(command, "env") == 0)
		return (COMMAND_ENV);
	else if (ft_strcmp(command, "alias") == 0)
        return (COMMAND_ALIAS);
	else if (ft_strcmp(command, "unalias") == 0)
        return (COMMAND_UNALIAS);
	else if (ft_strcmp(command, "test") == 0)
        return (COMMAND_TEST);
	else if (ft_strcmp(command, "hash") == 0)
        return (COMMAND_HASH);
	else
		return (COMMAND_EXTERNAL);
}

int		to_exit(t_process *process, t_job *j)
{
	int		i;
	int		e;

	i = 0;
	while (process->argv[i])
		i++;
	if (i < 3 && j->mode == FORE && process->next == NULL)
	{
		e = 0;
		if (i == 2)
			e = print_exit_error(process->argv[1]);
		if (g_if_exit == NULL)
		{
			help_to_exit(j);
			exit(e);
		}
	}
	else if (i > 2)
		ft_putendl_fd("exit: too many arguments", process->errorput);
	g_the_status = 1;
	return (-1);
}

int		trait_built(t_job *j, t_process *process)
{
	if (process->type == COMMAND_EXIT)
		to_exit(process, j);
	else if (process->type == COMMAND_JOBS)
		to_jobs();
	else if (process->type == COMMAND_FG)
		to_fg(process, j);
	else if (process->type == COMMAND_BG)
		to_bg(process, j);
	else if (process->type == COMMAND_ENV)
		to_env(process);
	else if (process->type == COMMAND_TYPE)
		to_type(process);
	else if (process->type == COMMAND_ECHO)
		to_echo(process);
	else if (process->type == COMMAND_SET)
		to_set(process);
	else if (process->type == COMMAND_UNSET)
		to_unset(process, j);
	else if (process->type == COMMAND_EXPORT)
		to_export(process, j, process->argv);
	else if (process->type == COMMAND_CD)
		to_cd(process, j);
	else if (process->type == COMMAND_ALIAS)
		ft_alias(process->argv, &g_alias);
	else if (process->type == COMMAND_UNALIAS)
		ft_unalias(process->argv, &g_alias);
	else if (process->type == COMMAND_TEST)
		ft_test(process->argv);
	else if (process->type == COMMAND_HASH)
		ft_hash(process->argv, &g_hashtable);
	return (0);
}

int		count_replace_env(char *line, int i, char c)
{
	i++;
	while (line[i] && line[i] != c)
	{
		if (line[i] == 92 && c == 34)
		{
			i++;
			if (line[i] != '\0')
				i++;
		}
		else if (line[i] == '$' && line[i + 1] == '{' && c == 34)
		{
			i = to_the_end_parent(line, i, '}', '{');
			if (line[i] == '}')
				i++;
		}
		else if (line[i] == '$' && line[i + 1] == '(' && c == 34)
		{
			i = to_the_end_parent(line, i, ')', '(');
			if (line[i] == ')')
				i++;
		}
		else
			i++;
	}
	return (i);
}

void	mini_mini_norme(char **line, char *str, int a, int i)
{
	if (str != NULL)
		join_with_something(&line[0], str, a, i);
	else
		join_with_anything2(&line[0], str, a, i);
}
