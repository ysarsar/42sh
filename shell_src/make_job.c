/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_job.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mac <mac@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/23 04:50:43 by hiantrin          #+#    #+#             */
/*   Updated: 2020/11/08 16:40:20 by mac              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/sh.h"

t_process	*make_process(char *line)
{
	t_process	*p;

	p = (t_process *)malloc(sizeof(t_process));
	p->command = ft_strdup(line);
	p->argv = NULL;
	p->next = NULL;
	p->signal = NULL;
	p->pid = -1;
	p->input = 0;
	p->output = 1;
	p->errorput = 2;
	return (p);
}

t_process	*all_process(char *line)
{
	char		**my_pipe;
	int			i;
	t_process	*process;
	t_process	*head;
	t_process	*next;

	i = 0;
	my_pipe = split_command(line, '|');
	process = make_process(my_pipe[i]);
	head = process;
	i++;
	while (my_pipe[i])
	{
		next = make_process(my_pipe[i]);
		process->next = next;
		process = process->next;
		i++;
	}
	free_2d(my_pipe);
	return (head);
}

t_job		*make_job(char *line, int mode)
{
	t_job	*j;

	j = (t_job *)malloc(sizeof(t_job));
	j->mode = mode;
	j->command = ft_strdup(line);
	j->pgid = -1;
	j->process = all_process(line);
	j->p = 0;
	j->p_input = 0;
	j->p_output = 1;
	return (j);
}

int			get_next_job_id(void)
{
	int	i;

	i = 1;
	while (i < NR_J)
	{
		if (g_shell->job[i] == NULL)
			return (i);
		i++;
	}
	return (-1);
}

int			insert_job(t_job *job)
{
	int id;

	id = get_next_job_id();
	job->id = id;
	g_shell->job[id] = job;
	return (id);
}
