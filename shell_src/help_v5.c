/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help_v5.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrxy <mrxy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/11 18:34:46 by hiantrin          #+#    #+#             */
/*   Updated: 2020/11/29 19:34:48 by mrxy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/sh.h"

void	init_fifo(void)
{
	if (g_fi.fifo != NULL)
	{
		free(g_fi.fifo);
		g_fi.fifo = NULL;
	}
	g_fi.put_out = 0;
}

int		help_to_norme_type(char *file)
{
	struct stat	l;
	int			b;

	b = 0;
	lstat(file, &l);
	if ((l.st_mode & S_IFMT) == S_IFIFO)
	{
		g_fi.fifo = ft_strdup(file);
		g_fi.put_out = 1;
		b = 1;
	}
	else
	{
		b = open(file, O_WRONLY | O_TRUNC);
		g_fi.put_out = 0;
	}
	return (b);
}

int		check_set_curch(char *str, int end, int start)
{
	char	*new;
	char	*error;

	new = ft_strsub(str, start, end - start);
	if (check_set(new) == 0 && ft_strcmp(new, "?") != 0)
	{
		ft_putstr_fd("42sh: ", 2);
		error = ft_strsub(str, start - 2, (end + 1) - (start - 2));
		ft_putstr_fd(error, 2);
		ft_putendl_fd(": bad substitution", 2);
		free(new);
		free(error);
		return (0);
	}
	free(new);
	return (1);
}

void	make_another_and_kill(char *command)
{
	t_save	save;

	open_the_file();
	save.fi = g_fi;
	save.shell = g_shell;
	save.status_string = g_status_string;
	save.semicolon = g_semicolon;
	save.and_and = g_and_and;
	save.or_or = g_or_or;
	save.the_jobs = g_the_jobs;
	save.the_status = g_the_status;
	save.if_exit = g_if_exit;
	save.hashtable = alloc_hash(&g_hashtable);
	g_if_sub = 1;
	semicolon_parse(ft_strdup(command));
	g_if_sub = 0;
	g_fi = save.fi;
	g_shell = save.shell;
	g_status_string = save.status_string;
	g_semicolon = save.semicolon;
	g_and_and = save.and_and;
	g_or_or = save.or_or;
	g_the_jobs = save.the_jobs;
	g_the_status = save.the_status;
	g_if_exit = save.if_exit;
	delete_hashtable(&g_hashtable, 2);
	free(g_hashtable->list);
	free(g_hashtable);
	g_hashtable = save.hashtable;
}

char	*trait_the_parentheses(char *new)
{
	char	*command;
	char	*tmp;
	int		i;

	if (mini_checker_e_parent(new, 0) == 0)
		return (NULL);
	make_another_and_kill(new);
	tmp = check_env("HOME", g_shell->env);
	command = ft_strjoin(tmp, "/my");
	i = open(command, O_RDONLY);
	free(command);
	free(tmp);
	command = return_the_sub(i);
	remove_the_file();
	return (command);
}
