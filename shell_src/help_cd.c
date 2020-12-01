/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help_cd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiantrin <hiantrin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/23 03:45:04 by hiantrin          #+#    #+#             */
/*   Updated: 2020/10/25 11:00:33 by hiantrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/sh.h"

void	add_pwd(t_process *process, t_job *job, char *str)
{
	char		**argv;
	char		cwd[BUFF_SIZE];
	char		*new;

	argv = (char **)malloc(sizeof(char *) * 3);
	argv[2] = NULL;
	getcwd(cwd, sizeof(cwd));
	argv[0] = ft_strdup("export");
	new = ft_strjoin(str, "=");
	argv[1] = ft_strjoin(new, cwd);
	free(new);
	to_export(process, job, argv);
	free_2d(argv);
}

int		print_cd_error(char *argv, int error, char *new)
{
	ft_putstr_fd("42sh: cd: permission denied: ", error);
	ft_putendl_fd(argv, error);
	g_the_status = 1;
	free(new);
	return (0);
}

void	change_lien(char **new, char *str)
{
	if (new[0] != NULL && new[0][0] == 'l')
	{
		if (access(str, F_OK) == 0)
		{
			new[0][0] = 'd';
			if (access(str, X_OK) == -1)
			{
				new[0][0] = 'x';
			}
		}
		else
			new[0] = NULL;
	}
}

int		test_dir(char *argv, t_process *process)
{
	char *new;

	new = check(argv);
	change_lien(&new, argv);
	if (new == NULL)
	{
		ft_putstr_fd("42sh: cd: no such file or directory: ",
			process->errorput);
		ft_putendl_fd(argv, process->errorput);
		g_the_status = 1;
		return (0);
	}
	else if (new[0] != 'x' && new[0] != 'd' && new[0] != 'r')
	{
		ft_putstr_fd("42sh: cd: not a directory: ", process->errorput);
		ft_putendl_fd(argv, process->errorput);
		g_the_status = 1;
		free(new);
		return (0);
	}
	else if (new[0] == 'x')
		return (print_cd_error(argv, process->errorput, new));
	free(new);
	return (1);
}

void	print_error_jump_options(char c, int error)
{
	ft_putstr_fd("42sh: cd -", error);
	ft_putchar_fd(c, error);
	ft_putstr_fd(": invalid option\ncd: usage: cd [-L|-P] [dir]\n", error);
}
