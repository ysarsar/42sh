/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help_command_jobs.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiantrin <hiantrin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/23 03:45:23 by hiantrin          #+#    #+#             */
/*   Updated: 2020/10/25 11:00:33 by hiantrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/sh.h"

int		put_error_fg(int type)
{
	if (type == COMMAND_FG)
		ft_putendl("42sh: fg: too many arguments");
	else if (type == COMMAND_BG)
		ft_putendl("42sh: bg: too many arguments");
	g_the_status = 1;
	return (-1);
}

int		put_error_no_such(int type)
{
	if (type == COMMAND_FG)
		ft_putendl("42sh: fg: no such job");
	else if (type == COMMAND_BG)
		ft_putendl("42sh: bg: no such job");
	g_the_status = 1;
	return (-1);
}

int		search_last(void)
{
	int i;

	i = 29;
	while (i > 0)
	{
		if (g_shell->job[i])
			return (i);
		i--;
	}
	return (0);
}

int		put_error_not_found(int type)
{
	if (type == COMMAND_FG)
		ft_putendl("42sh: fg: job not found");
	else if (type == COMMAND_BG)
		ft_putendl("42sh: bg: job not found");
	g_the_status = 1;
	return (-1);
}

void	set_job_status(int id, int status)
{
	t_process *process;

	process = g_shell->job[id]->process;
	while (process)
	{
		if (process->status != STATUS_DONE)
			process->status = status;
		process = process->next;
	}
}
