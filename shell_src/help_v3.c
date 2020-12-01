/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help_v3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiantrin <hiantrin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/23 04:30:40 by hiantrin          #+#    #+#             */
/*   Updated: 2020/11/18 17:43:33 by hiantrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/sh.h"

void	help_to_wait(t_job *j, int *status)
{
	tcsetpgrp(0, j->pgid);
	status[0] = wait_for_job(j->id, 0);
	signal(SIGTTOU, SIG_IGN);
	tcsetpgrp(0, getpid());
	signal(SIGTTOU, SIG_DFL);
}

void	final_help(t_process **process, t_job **j, int *count)
{
	t_env	*save;

	process[0]->argv = manage_variables(process[0]->argv, &save);
	if (process[0]->argv)
	{
		process[0]->type = get_command_type(process[0]->argv[0]);
		if (process[0]->type == COMMAND_EXTERNAL)
			help_trait(&j[0], &process[0], &count[0]);
		else
			back_or_fore(&j[0], &process[0]);
	}
	manage_variables2(save);
}

int		print_exit_error(char *str)
{
	int i;

	i = 0;
	if (str[i] == '-')
		i++;
	if ((i == 1 && str[1] == '\0') || check_if_is_num(&str[i]) == 0)
	{
		ft_putstr("42sh: exit: ");
		ft_putstr(str);
		ft_putendl(" : numeric argument required");
		return (-1);
	}
	else
		return (atoi(str));
}

int		if_numeric_or_percent(char *str)
{
	int i;
	int id;

	i = 0;
	while (str[i] == '%')
		i++;
	if (str[i] == '\0' && search_last() == 0)
		return (0);
	if (str[i] == '\0' && search_last() != 0)
		return (search_last());
	if (if_numeric(&str[i]) == 0 || (id = atoi(&str[i])) > 29
			|| g_shell->job[id] == NULL)
		return (0);
	else
		return (id);
}

void	help_wait_for_job(int wait_pid, int status)
{
	char	**signalmsg;

	set_process_status(wait_pid, STATUS_TERMINATED);
	if (WTERMSIG(status) != 2 && WTERMSIG(status) != 13)
	{
		signalmsg = my_tab_signalmsg();
		ft_putstr(signalmsg[WTERMSIG(status)]);
		ft_putstr(": ");
		ft_putnbr(WTERMSIG(status));
		ft_putchar('\n');
	}
}
