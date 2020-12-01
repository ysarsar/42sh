/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiantrin <hiantrin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/19 00:57:10 by hiantrin          #+#    #+#             */
/*   Updated: 2020/10/25 11:15:32 by hiantrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/sh.h"

void	set_signal(pid_t pid, int status)
{
	int			i;
	t_process	*process;
	char		**signalmsg;

	i = 1;
	while (i < NR_J)
	{
		if (g_shell->job[i])
		{
			process = g_shell->job[i]->process;
			while (process)
			{
				if (process->pid == pid)
				{
					signalmsg = my_tab_signalmsg();
					process->signal = signalmsg[WTERMSIG(status)];
					return ;
				}
				process = process->next;
			}
		}
		i++;
	}
}
