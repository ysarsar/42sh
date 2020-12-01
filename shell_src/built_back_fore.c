/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_back_fore.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiantrin <hiantrin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/23 03:24:38 by hiantrin          #+#    #+#             */
/*   Updated: 2020/11/18 18:11:18 by hiantrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/sh.h"

void	help_back_built(t_job **job, t_process **process)
{
	int b;

	process[0]->pid = getpid();
	if (job[0]->pgid > 0)
		setpgid(0, job[0]->pgid);
	else
	{
		job[0]->pgid = process[0]->pid;
		setpgid(0, job[0]->pgid);
	}
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	signal(SIGTSTP, SIG_DFL);
	signal(SIGTTIN, SIG_DFL);
	signal(SIGTTOU, SIG_DFL);
	signal(SIGCHLD, SIG_DFL);
	if (g_fi.fifo != NULL)
	{
		b = open(g_fi.fifo, O_WRONLY | O_TRUNC);
		if (g_fi.put_out == 1)
			process[0]->output = b;
	}
	trait_built(job[0], process[0]);
	exit(0);
}

void	mini_help_back_fore(t_process *process, t_job *job)
{
	int b;

	if (g_fi.fifo != NULL)
	{
		b = open(g_fi.fifo, O_WRONLY | O_TRUNC);
		if (g_fi.put_out == 1)
			process->output = b;
	}
	trait_built(job, process);
}

void	back_or_fore(t_job **job, t_process **process)
{
	pid_t	pid;

	pid = 0;
	if (job[0]->mode == BACK || g_fi.next == 1)
	{
		pid = fork();
		if (pid == 0)
			help_back_built(&job[0], &process[0]);
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
	}
	else
		mini_help_back_fore(process[0], job[0]);
}
