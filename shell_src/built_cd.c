/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_cd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiantrin <hiantrin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/23 03:25:41 by hiantrin          #+#    #+#             */
/*   Updated: 2020/11/23 05:21:10 by hiantrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/sh.h"

char	**jump_options(char **argv, int error)
{
	int i;
	int j;

	i = 1;
	while (argv[i])
	{
		j = 0;
		if (argv[i][j] == '-' && argv[i][j + 1] != '\0')
			j++;
		else
			break ;
		while (argv[i][j])
		{
			if (argv[i][j] != 'L' && argv[i][j] != 'P')
			{
				print_error_jump_options(argv[i][j], error);
				g_the_status = 1;
				return (NULL);
			}
			j++;
		}
		i++;
	}
	return (&argv[i - 1]);
}

void	mini_norme_mini_cd(int error)
{
	ft_putendl_fd("42sh: cd: Too many arguments.", error);
	g_the_status = 1;
}

void	help_saloupi_to_treat_cd2(t_env *list, int error)
{
	if (list == NULL)
		ft_putendl_fd("42sh: cd: OLDPWD not set", error);
	else
		ft_putendl_fd("42sh: cd: no such file or directory", error);
	g_the_status = 1;
}

void	mini_cd2(t_process *process, t_job *job)
{
	char	*old;
	t_env	*first;

	first = g_shell->env;
	while (first)
	{
		if (ft_strcmp(first->name, "OLDPWD") == 0)
		{
			if (access(first->environ, F_OK) == 0)
			{
				old = ft_strdup(first->environ);
				add_pwd(process, job, "OLDPWD");
				chdir(old);
				add_pwd(process, job, "PWD");
				free(old);
				return ;
			}
			else
				break ;
		}
		first = first->next;
	}
	help_saloupi_to_treat_cd2(first, process->errorput);
}

void	to_cd(t_process *process, t_job *job)
{
	int			i;
	char		**argv;

	i = 1;
	argv = process->argv;
	if ((argv = jump_options(argv, process->errorput)) == NULL)
		return ;
	while (argv[i])
		i++;
	i--;
	if (i > 1)
		mini_norme_mini_cd(process->errorput);
	if (i == 1 && ft_strcmp(argv[1], "-") == 0 && process->next == NULL
			&& job->mode == FORE && g_if_sub == 0)
		mini_cd2(process, job);
	else if (i == 1 && test_dir(argv[1], process) == 0)
		return ;
	else if (process->next == NULL && job->mode == FORE
			&& g_if_sub == 0)
		norme_to_cd(process, job, argv, i);
}
