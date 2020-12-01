/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   all_command_jobs.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiantrin <hiantrin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/23 03:24:09 by hiantrin          #+#    #+#             */
/*   Updated: 2020/11/23 10:41:41 by hiantrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/sh.h"

int		to_jobs(void)
{
	int		i;

	i = 1;
	if (g_if_sub == 0)
	{
		while (i < NR_J)
		{
			if (g_shell->job[i] != NULL)
				print_job_status(i);
			i++;
		}
	}
	g_the_status = 0;
	return (0);
}

int		check_bug_fg_bg(t_process *process, int type)
{
	int id;
	int i;

	i = 0;
	while (process->argv[i])
		i++;
	if (i > 2)
		return (put_error_fg(type));
	if ((i == 1 && search_last() == 0) ||
		(i != 1 && (id = if_numeric_or_percent(process->argv[1])) == 0))
		return (put_error_no_such(type));
	if (i == 1)
		id = search_last();
	return (id);
}

int		to_fg(t_process *process, t_job *j)
{
	pid_t	pid;
	int		id;

	if (j->mode == FORE && g_fi.next == 0 && g_if_sub == 0)
	{
		if ((id = check_bug_fg_bg(process, COMMAND_FG)) == -1)
			return (-1);
		pid = g_shell->job[id]->pgid;
		if (kill(-pid, SIGCONT) < 0)
			return (put_error_not_found(COMMAND_FG));
		help_to_fg(pid, id);
		g_the_status = 0;
	}
	else if (j->mode == BACK || g_fi.next != 0 || g_if_sub != 0)
	{
		ft_putendl_fd("42sh: fg: no job control", process->errorput);
		g_the_status = 1;
	}
	return (0);
}

int		to_bg(t_process *process, t_job *j)
{
	pid_t	pid;
	int		id;

	if (j->mode == FORE && g_fi.next == 0 && g_if_sub == 0)
	{
		if ((id = check_bug_fg_bg(process, COMMAND_BG)) == -1)
			return (-1);
		pid = g_shell->job[id]->pgid;
		if (kill(-pid, SIGCONT) < 0)
			return (put_error_not_found(COMMAND_BG));
		set_job_status(id, STATUS_CONTINUED);
		print_job_status(id);
		g_the_status = 0;
	}
	else if (j->mode == BACK || g_fi.next != 0 || g_if_sub != 0)
	{
		ft_putendl_fd("42sh: bg: no job control", process->errorput);
		g_the_status = 1;
	}
	return (-1);
}
