/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrxy <mrxy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/23 03:44:45 by hiantrin          #+#    #+#             */
/*   Updated: 2020/11/29 17:57:03 by mrxy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/sh.h"

char	**list_to_tab(t_env *env)
{
	int		i;
	char	**tabb;
	char	*new;
	t_env	*head;

	head = env;
	i = 0;
	while (env != NULL)
	{
		i++;
		env = env->next;
	}
	tabb = (char **)malloc(sizeof(char *) * i + 1);
	tabb[i] = NULL;
	i = 0;
	while (head != NULL)
	{
		new = ft_strjoin(head->name, "=");
		tabb[i++] = ft_strjoin(new, head->environ);
		free(new);
		head = head->next;
	}
	return (tabb);
}

char	*join_path(char *path1, char *path2)
{
	char	*tmp;
	char	*tmp2;

	tmp = ft_strjoin(path1, "/");
	tmp2 = ft_strjoin(tmp, path2);
	free(tmp);
	return (tmp2);
}

char	*search_join(char **path, char *str, char **print)
{
	int			i;
	char		*command;
	struct stat	l;
	DIR			*dir;

	i = 0;
	dir = NULL;
	print[0] = NULL;
	while (path[i])
	{
		command = join_path(path[i], str);
		if (lstat(command, &l) > -1)
			return (command);
		free(command);
		i++;
	}
	if (ft_strchr(str, '/') && (lstat(str, &l) > -1))
		return (help_search_join(str, dir, &print[0]));
	print[0] = ft_strjoin("42sh : command not found: ", str);
	return (NULL);
}

char	*search_env(t_env *list)
{
	t_env	*first;

	first = list;
	while (first)
	{
		if (ft_strcmp(first->name, "PATH") == 0)
			return (first->environ);
		first = first->next;
	}
	return (NULL);
}

void	exec_command(t_job **job, t_process **process)
{
	char	**envp;
	char	*command;
	char	*print;

	process[0]->status = STATUS_DONE;
	print = NULL;
	if (search_env(g_shell->env))
	{
		envp = list_to_tab(g_shell->env);
		command = ft_hashtable(process[0]->argv, envp, &g_hashtable, &print);
		free_2d(envp);
		execve_help(&process[0], &job[0], command, print);
		if (command != NULL)
			free(command);
		else
			g_the_status = 127;
		if (print != NULL)
			free(print);
		else
			process[0]->status = STATUS_RUNNING;
	}
}
