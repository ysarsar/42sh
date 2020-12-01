/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiantrin <hiantrin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/23 04:51:12 by hiantrin          #+#    #+#             */
/*   Updated: 2020/11/23 12:58:34 by hiantrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/sh.h"

char	*join_the_sub(char *str)
{
	char	*tmp;
	char	*new;

	tmp = check_env("HOME", g_shell->env);
	new = ft_strjoin(tmp, "/my ");
	free(tmp);
	tmp = new;
	new = ft_strjoin(">> ", new);
	free(tmp);
	tmp = new;
	new = ft_strjoin(new, str);
	free(tmp);
	free(str);
	return (new);
}

void	jobs_parse(char *line)
{
	int i;

	i = 0;
	g_the_jobs = split_job(line);
	while (g_the_jobs[i])
	{
		if (check_line(g_the_jobs[i]))
		{
			if (g_the_jobs[i + 1] != NULL && g_if_sub != 1)
				trait(g_the_jobs[i], BACK, 0);
			else
				trait(g_the_jobs[i], FORE, 0);
		}
		i++;
	}
	free_2d(g_the_jobs);
	g_the_jobs = NULL;
}

void	or_or_parse(char *line, int fo)
{
	int i;

	i = 0;
	g_or_or = split_and_and(line, '|');
	while (g_or_or[i])
	{
		if (check_line(g_or_or[i]))
		{
			if (fo == 0 || (i == 0 && g_the_status == 0)
				|| (i != 0 && g_the_status != 0))
				jobs_parse(g_or_or[i]);
			if (g_the_status == 0)
				break ;
		}
		i++;
	}
	free_2d(g_or_or);
	g_or_or = NULL;
}

void	and_and_parse(char *line)
{
	int i;

	i = 0;
	g_and_and = split_and_and(line, '&');
	while (g_and_and[i])
	{
		if (check_line(g_and_and[i]))
			or_or_parse(g_and_and[i], i);
		i++;
	}
	free_2d(g_and_and);
	g_and_and = NULL;
}

void	semicolon_parse(char *line)
{
	int	i;

	i = 0;
	g_semicolon = split_command(line, ';');
	free(line);
	while (g_semicolon[i])
	{
		g_if_exit = g_semicolon[i + 1];
		if (check_line(g_semicolon[i]))
			and_and_parse(g_semicolon[i]);
		i++;
	}
	free_2d(g_semicolon);
	g_semicolon = NULL;
}
