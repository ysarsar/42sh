/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_env_echo.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiantrin <hiantrin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/23 03:25:00 by hiantrin          #+#    #+#             */
/*   Updated: 2020/10/25 11:00:33 by hiantrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/sh.h"

void	print_env(int output)
{
	t_env	*env;

	env = g_shell->env;
	while (env)
	{
		if (env->flag != 1)
		{
			ft_putstr_fd(env->name, output);
			ft_putchar_fd('=', output);
			ft_putendl_fd(env->environ, output);
		}
		env = env->next;
	}
}

void	to_env(t_process *process)
{
	int i;

	i = 0;
	while (process->argv[i])
		i++;
	if (i > 1)
	{
		ft_putendl_fd("env: too many arguments", process->errorput);
		g_the_status = 1;
	}
	else
	{
		if (process->output != -1)
			print_env(process->output);
	}
}

void	to_echo(t_process *process)
{
	int		i;

	i = 1;
	while (process->argv[i])
	{
		if (process->output > 0)
		{
			ft_putstr_fd(process->argv[i], process->output);
			if (process->argv[i + 1] != NULL)
				ft_putstr_fd(" ", process->output);
		}
		i++;
	}
	if (process->output > 0)
		ft_putstr_fd("\n", process->output);
	g_the_status = 0;
	if (process->output == -1)
	{
		ft_putendl_fd("42sh: echo: write error: Bad file descriptor",
			process->errorput);
		g_the_status = 1;
	}
}

void	print_set(int output)
{
	t_env	*env;

	env = g_shell->env;
	while (env)
	{
		ft_putstr_fd(env->name, output);
		ft_putchar_fd('=', output);
		ft_putendl_fd(env->environ, output);
		env = env->next;
	}
}

void	to_set(t_process *process)
{
	int i;

	i = 0;
	while (process->argv[i])
		i++;
	if (i > 1)
	{
		ft_putendl_fd("set: too many arguments", process->errorput);
		g_the_status = 1;
	}
	else
	{
		if (process->output != -1)
			print_set(process->output);
	}
}
