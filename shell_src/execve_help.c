/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve_help.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiantrin <hiantrin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/23 03:44:37 by hiantrin          #+#    #+#             */
/*   Updated: 2020/11/18 18:17:13 by hiantrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/sh.h"

char	*help_search_join(char *str, DIR *dir, char **print)
{
	if (access(str, X_OK) == 0 &&
		(dir = opendir(str)) == NULL)
		return (ft_strdup(str));
	else
	{
		if (dir != NULL)
			closedir(dir);
		print[0] = ft_strjoin("42sh : permission denied: ", str);
		return (NULL);
	}
}

void	help_execve_help(t_job **job, t_process **process)
{
	process[0]->pid = getpid();
	if (job[0]->pgid > 0)
		setpgid(0, job[0]->pgid);
	else
	{
		job[0]->pgid = job[0]->process->pid;
		setpgid(0, job[0]->pgid);
	}
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	signal(SIGTSTP, SIG_DFL);
	signal(SIGTTIN, SIG_DFL);
	signal(SIGTTOU, SIG_DFL);
	signal(SIGCHLD, SIG_DFL);
}

void	execve_help(t_process **process, t_job **job,
		char *command, char *print)
{
	pid_t	pid;
	char	**tabb;

	tabb = list_to_tab(g_shell->env);
	pid = fork();
	if (pid == 0)
	{
		help_execve_help(&job[0], &process[0]);
		pipe_execve(process[0], job[0]);
		execve(command, process[0]->argv, tabb);
		ft_putendl_fd(print, process[0]->errorput);
		exit(0);
	}
	else
	{
		process[0]->pid = pid;
		if (job[0]->pgid > 0)
			setpgid(pid, job[0]->pgid);
		else
		{
			job[0]->pgid = pid;
			setpgid(pid, job[0]->pgid);
		}
	}
	free_2d(tabb);
}
