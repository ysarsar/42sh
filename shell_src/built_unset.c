/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_unset.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiantrin <hiantrin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/23 03:25:57 by hiantrin          #+#    #+#             */
/*   Updated: 2020/11/23 05:19:13 by hiantrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/sh.h"

int		check_unset(char *str)
{
	int i;

	i = 0;
	if (str[0] >= '0' && str[0] <= '9')
		return (0);
	while (str[i])
	{
		if (str[i] == '_' || (str[i] >= 'a' && str[i] <= 'z') ||
			(str[i] >= 'A' && str[i] <= 'Z') ||
			(str[i] >= '0' && str[i] <= '9'))
			i++;
		else
			return (0);
	}
	return (1);
}

void	help_unsetenv(char *command)
{
	t_env	*str;
	t_env	*next;
	t_env	*head;

	head = g_shell->env;
	str = NULL;
	while (head && ft_strcmp(command, head->name) != 0)
	{
		str = head;
		head = head->next;
	}
	if (head && (ft_strcmp(command, head->name) == 0))
	{
		next = head->next;
		free(head->name);
		free(head->environ);
		free(head);
		if (str != NULL)
			str->next = next;
		else
			g_shell->env = next;
	}
}

void	to_unset(t_process *process, t_job *job)
{
	int			i;
	char		*new;

	i = 1;
	while (process->argv[i])
	{
		if (check_unset(process->argv[i]) == 0)
		{
			ft_putstr_fd("minishell: unsetenv: `", process->errorput);
			ft_putstr_fd(process->argv[i], process->errorput);
			ft_putendl_fd("': not a valid identifier", process->errorput);
			g_the_status = 1;
		}
		else if (job->mode == FORE && g_if_sub == 0 &&
			(new = check_env(process->argv[i], g_shell->env)) != NULL
			&& g_fi.next == 0)
		{
			free(new);
			help_unsetenv(process->argv[i]);
		}
		i++;
	}
}
