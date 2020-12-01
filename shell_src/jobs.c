/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jobs.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiantrin <hiantrin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/23 04:38:42 by hiantrin          #+#    #+#             */
/*   Updated: 2020/11/19 18:48:06 by hiantrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/sh.h"

void	print_pgid_of_job(int id)
{
	ft_putchar('[');
	ft_putnbr(id);
	ft_putstr("] ");
	ft_putnbr(g_shell->job[id]->pgid);
	ft_putchar('\n');
}

int		is_job_completed(int id)
{
	t_process	*process;

	process = g_shell->job[id]->process;
	while (process)
	{
		if (process->status != STATUS_DONE)
			return (0);
		process = process->next;
	}
	return (1);
}

int		get_job_id_by_pid(int pid)
{
	int			i;
	t_process	*process;

	i = 1;
	while (i < NR_J)
	{
		if (g_shell->job[i])
		{
			process = g_shell->job[i]->process;
			while (process)
			{
				if (process->pid == pid)
					return (i);
				process = process->next;
			}
		}
		i++;
	}
	return (-1);
}

void	help_check_zombie(pid_t pid)
{
	int	job_id;

	job_id = get_job_id_by_pid(pid);
	if (job_id > 0 && is_job_completed(job_id) == 1)
	{
		print_job_status(job_id);
		remove_job(job_id);
	}
	else if (job_id < 0)
		kill(pid, SIGKILL);
}

void	check_zombie(int job_id)
{
	int		status;
	pid_t	pid;

	while ((pid = waitpid(-1, &status, WNOHANG | WUNTRACED | WCONTINUED)) > 0)
	{
		if (WIFEXITED(status))
			set_process_status(pid, STATUS_DONE);
		else if (WIFSTOPPED(status))
		{
			set_process_status(pid, STATUS_SUSPENDED);
			job_id = get_job_id_by_pid(pid);
			if (job_id > 0)
				print_job_status(job_id);
			else
				kill(-pid, SIGKILL);
		}
		else if (WIFSIGNALED(status))
		{
			set_process_status(pid, STATUS_DONE);
			set_signal(pid, status);
		}
		else if (WIFCONTINUED(status))
			set_process_status(pid, STATUS_CONTINUED);
		help_check_zombie(pid);
	}
}
