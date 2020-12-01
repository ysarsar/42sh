/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_subshell.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiantrin <hiantrin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/23 02:40:05 by hiantrin          #+#    #+#             */
/*   Updated: 2020/11/23 11:12:06 by hiantrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/sh.h"

int		pipe_sub(char *line)
{
	int		i;
	char	**pipe;

	i = 0;
	pipe = split_command(line, '|');
	while (pipe[i])
	{
		if (check_line(pipe[i]))
		{
			if (checker_subshell(pipe[i]) == 0)
				return (0);
		}
		i++;
	}
	free_2d(pipe);
	pipe = NULL;
	return (1);
}

int		jobs_sub(char *line)
{
	int		i;
	char	**the_jobs;

	i = 0;
	the_jobs = split_job(line);
	while (the_jobs[i])
	{
		if (check_line(the_jobs[i]))
		{
			if (pipe_sub(the_jobs[i]) == 0)
				return (0);
		}
		i++;
	}
	free_2d(the_jobs);
	the_jobs = NULL;
	return (1);
}

int		or_or_sub(char *line)
{
	int		i;
	char	**or_or;

	i = 0;
	or_or = split_and_and(line, '|');
	while (or_or[i])
	{
		if (check_line(or_or[i]))
		{
			if (jobs_sub(or_or[i]) == 0)
				return (0);
		}
		i++;
	}
	free_2d(or_or);
	or_or = NULL;
	return (1);
}

int		and_and_sub(char *line)
{
	int		i;
	char	**and_and;

	i = 0;
	and_and = split_and_and(line, '&');
	while (and_and[i])
	{
		if (check_line(and_and[i]))
		{
			if (or_or_sub(and_and[i]) == 0)
				return (0);
		}
		i++;
	}
	free_2d(and_and);
	and_and = NULL;
	return (1);
}

int		semi_sub(char **str)
{
	int		i;
	char	**semicolon;
	char	*line;

	second_loop_sub(&str[0]);
	i = 0;
	line = ft_strdup(str[0]);
	semicolon = split_command(line, ';');
	free(line);
	while (semicolon[i])
	{
		if (check_line(semicolon[i]))
		{
			if (and_and_sub(semicolon[i]) == 0)
				return (0);
		}
		i++;
	}
	free_2d(semicolon);
	semicolon = NULL;
	return (1);
}
