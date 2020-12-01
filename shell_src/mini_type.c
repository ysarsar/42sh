/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_type.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiantrin <hiantrin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/12 23:53:03 by hiantrin          #+#    #+#             */
/*   Updated: 2020/10/28 02:20:08 by ommadhi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/sh.h"

int		mini_type1(char *str, t_process *process)
{
	if (ft_strcmp(str, ".") == 0 || ft_strcmp(str, "..") == 0 ||
			ft_strcmp(str, "alias") == 0 || ft_strcmp(str, "bg") == 0 ||
			ft_strcmp(str, "break") == 0 || ft_strcmp(str, "builtin") == 0 ||
			ft_strcmp(str, "caller") == 0 || ft_strcmp(str, "cd") == 0 ||
			ft_strcmp(str, "command") == 0 || ft_strcmp(str, "compgen") == 0 ||
			ft_strcmp(str, "complete") == 0 || ft_strcmp(str, "continue") == 0
			|| ft_strcmp(str, "declare") == 0 || ft_strcmp(str, "dirs") == 0 ||
			ft_strcmp(str, "disown") == 0 || ft_strcmp(str, "echo") == 0 ||
			ft_strcmp(str, "[") == 0 || ft_strcmp(str, "bind") == 0 ||
			ft_strcmp(str, "enable") == 0 || ft_strcmp(str, "eval") == 0 ||
			ft_strcmp(str, "exec") == 0 || ft_strcmp(str, "exit") == 0 ||
			ft_strcmp(str, "export") == 0 || ft_strcmp(str, "false") == 0 ||
			ft_strcmp(str, "fc") == 0 || ft_strcmp(str, "fg") == 0 ||
			ft_strcmp(str, "getopts") == 0 || ft_strcmp(str, "hash") == 0 ||
			ft_strcmp(str, "help") == 0 || ft_strcmp(str, "history") == 0 ||
			ft_strcmp(str, "jobs") == 0 || ft_strcmp(str, "kill") == 0 ||
			ft_strcmp(str, "let") == 0 || ft_strcmp(str, "local") == 0 ||
			ft_strcmp(str, "logout") == 0 || ft_strcmp(str, "popd") == 0)
	{
		ft_putstr_fd(str, process->output);
		ft_putendl_fd(" is a shell builtin", process->output);
		g_the_status = 0;
		return (1);
	}
	return (0);
}

int		mini_type1v2(char *str, t_process *process)
{
	if (ft_strcmp(str, "printf") == 0 || ft_strcmp(str, "pushd") == 0 ||
			ft_strcmp(str, "pwd") == 0 || ft_strcmp(str, "read") == 0 ||
			ft_strcmp(str, "readonly") == 0 || ft_strcmp(str, "return") == 0 ||
			ft_strcmp(str, "set") == 0 || ft_strcmp(str, "shift") == 0 ||
			ft_strcmp(str, "shopt") == 0 || ft_strcmp(str, "source") == 0 ||
			ft_strcmp(str, "suspend") == 0 || ft_strcmp(str, "test") == 0 ||
			ft_strcmp(str, "times") == 0 || ft_strcmp(str, "trap") == 0 ||
			ft_strcmp(str, "true") == 0 || ft_strcmp(str, "type") == 0 ||
			ft_strcmp(str, "typeset") == 0 || ft_strcmp(str, "ulimit") == 0 ||
			ft_strcmp(str, "umask") == 0 || ft_strcmp(str, "unalias") == 0 ||
			ft_strcmp(str, "unset") == 0 || ft_strcmp(str, "wait") == 0)
	{
		ft_putstr_fd(str, process->output);
		ft_putendl_fd(" is a shell builtin", process->output);
		g_the_status = 0;
		return (1);
	}
	return (0);
}

int		mini_type2(char *str, t_process *process)
{
	if (ft_strcmp(str, "if") == 0 || ft_strcmp(str, "then") == 0 ||
			ft_strcmp(str, "else") == 0 || ft_strcmp(str, "elif") == 0 ||
			ft_strcmp(str, "fi") == 0 || ft_strcmp(str, "case") == 0 ||
			ft_strcmp(str, "esac") == 0 || ft_strcmp(str, "for") == 0 ||
			ft_strcmp(str, "select") == 0 || ft_strcmp(str, "while") == 0 ||
			ft_strcmp(str, "until") == 0 || ft_strcmp(str, "do") == 0 ||
			ft_strcmp(str, "done") == 0 || ft_strcmp(str, "in") == 0 ||
			ft_strcmp(str, "function") == 0 || ft_strcmp(str, "time") == 0 ||
			ft_strcmp(str, "}") == 0 || ft_strcmp(str, "{") == 0 ||
			ft_strcmp(str, "!") == 0 || ft_strcmp(str, "[[") == 0 ||
			ft_strcmp(str, "]]") == 0)
	{
		ft_putstr_fd(str, process->output);
		ft_putendl_fd(" is a shell keyword", process->output);
		g_the_status = 0;
		return (1);
	}
	return (0);
}

int		mini_type3(char *str, t_env *list, t_process *process)
{
	char	**tabb;
	char	*path;

	tabb = ft_strsplit(search_env(list), ':');
	path = check_if_exist(str, tabb);
	free_2d(tabb);
	if (path == NULL)
		return (0);
	else
	{
		ft_putstr_fd(str, process->output);
		ft_putstr_fd(" is ", process->output);
		ft_putendl_fd(path, process->output);
		free(path);
		g_the_status = 0;
		return (1);
	}
	return (0);
}

void	to_type(t_process *process)
{
	int		i;

	i = 0;
	while (process->argv[++i])
	{
		if (mini_type1(process->argv[i], process) == 1)
		{
		}
		else if (mini_type1v2(process->argv[i], process) == 1)
		{
		}
		else if (mini_type2(process->argv[i], process) == 1)
		{
		}
		else if (mini_type3(process->argv[i], g_shell->env, process) == 1)
		{
		}
		else
		{
			ft_putstr_fd("42sh: type: ", process->errorput);
			ft_putstr_fd(process->argv[i], process->errorput);
			ft_putendl_fd(": not found", process->errorput);
			g_the_status = 1;
		}
	}
}
