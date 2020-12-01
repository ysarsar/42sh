/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help_v7.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mac <mac@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/19 18:25:33 by hiantrin          #+#    #+#             */
/*   Updated: 2020/11/19 23:21:46 by mac              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/sh.h"

void	open_the_file(void)
{
	int		i;
	char	*tmp;
	char	*file;

	tmp = check_env("HOME", g_shell->env);
	file = ft_strjoin(tmp, "/my");
	i = open(file, O_CREAT, 0644);
	close(i);
	free(tmp);
	free(file);
}

char	*return_the_sub(int fd)
{
	char	*tmp;
	char	*command;
	char	*f;

	while (get_next_line(fd, &tmp))
	{
		if (command == NULL)
			command = ft_strdup(tmp);
		else
		{
			f = command;
			command = ft_strjoin(command, " ");
			free(f);
			f = command;
			command = ft_strjoin(command, tmp);
			free(f);
		}
		free(tmp);
	}
	close(fd);
	return (command);
}

void	remove_the_file(void)
{
	char	*tmp;
	char	*file;

	tmp = check_env("HOME", g_shell->env);
	file = ft_strjoin(tmp, "/my");
	remove(file);
	free(tmp);
	free(file);
}

int		mini_norme_check_parenthesis(char *line, int i)
{
	i = to_the_end_parent(line, i, '}', '{');
	if (line[i] == '}')
		i++;
	return (i);
}

char	*trait_the_parentheses_help(int *a, int i, char *line)
{
	char	*new;

	*a = to_the_end_parent(line, i, ')', '(');
	new = ft_strsub(line, i + 2, *a - (i + 2));
	(*a)++;
	return (trait_the_parentheses(new));
}
