/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrxy <mrxy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/23 04:31:55 by hiantrin          #+#    #+#             */
/*   Updated: 2020/11/29 17:59:07 by mrxy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/sh.h"

void	alloc_shell(void)
{
	int i;

	g_shell = (t_shell *)malloc(sizeof(t_shell));
	i = 0;
	while (i < NR_J)
		g_shell->job[i++] = NULL;
	g_status_string = (char **)malloc(sizeof(char *) * 6);
	g_status_string[5] = NULL;
	g_status_string[0] = ft_strdup("running");
	g_status_string[1] = ft_strdup("done");
	g_status_string[2] = ft_strdup("suspended");
	g_status_string[3] = ft_strdup("continued");
	g_status_string[4] = ft_strdup("terminated");
}

void	init_shell(void)
{
	pid_t	pid;

	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGTSTP, SIG_IGN);
	pid = getpid();
	setpgid(pid, pid);
	tcsetpgrp(0, pid);
	g_semicolon = NULL;
	g_the_status = 0;
	g_the_jobs = NULL;
	g_or_or = NULL;
	g_and_and = NULL;
	g_if_exit = NULL;
	g_hashtable = ht_create();
	alloc_shell();
}

void	free_jobs(void)
{
	t_job	*j;
	int		i;

	i = 1;
	while (i < NR_J)
	{
		j = g_shell->job[i];
		if (j != NULL)
			remove_job(i);
		i++;
	}
}

void	free_env_list(t_env *env)
{
	t_env	*next;
	t_env	*list;

	list = env;
	while (list != NULL)
	{
		free(list->name);
		free(list->environ);
		next = list->next;
		free(list);
		list = next;
	}
}

void	help_to_exit(t_job *job)
{
	ft_putendl("exit");
	ft_save_aliases_in_file();
	ft_save_his_in_file();
	ft_free_aliases_list(&g_alias);
	ft_free_his(&g_his);
	free_job(job);
	free_jobs();
	free_env_list(g_shell->env);
	free_2d(g_status_string);
	free(g_shell);
	free_2d(g_semicolon);
	free_2d(g_and_and);
	free_2d(g_or_or);
	free_2d(g_the_jobs);
	delete_hashtable(&g_hashtable, 2);
	free(g_hashtable->list);
	free(g_hashtable);
}
