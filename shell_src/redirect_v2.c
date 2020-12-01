/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_v2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiantrin <hiantrin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/23 04:55:41 by hiantrin          #+#    #+#             */
/*   Updated: 2020/10/23 05:01:45 by hiantrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/sh.h"

char	*filter_for_file(char *file, t_env *env)
{
	int	i;

	i = 0;
	file = replace_with_env(file, env, i, 0);
	file = replace_home(file, env);
	file = move_slash(file);
	file = move_quote(file, 0);
	return (file);
}

void	join_with_anything(char **line, int a, int i)
{
	char	*first;
	char	*str;

	first = ft_strsub(*line, 0, i);
	str = ft_strdup(&line[0][a]);
	free(*line);
	line[0] = ft_strjoin(first, str);
	free(first);
	free(str);
}

int		help_to_take_file(int j, char **file)
{
	int i;

	i = j + 1;
	while (file[0][i] && (file[0][i] == ' ' || file[0][i] == '\t'
		|| file[0][i] == '\n'))
		i++;
	join_with_anything(&file[0], i, j + 1);
	i = j + 1;
	if (file[0][i] == '-')
		return (i + 1);
	while (file[0][i] && file[0][i] != ' ' && file[0][i] != '\t'
		&& file[0][i] != '\n')
		i++;
	return (i);
}

char	*take_file(char **file, int *j)
{
	int		i;
	int		b;
	char	*line;

	while (file[0][*j] == ' ' || file[0][*j] == '\t' || file[0][*j] == '\n')
		(*j)++;
	i = *j;
	if (file[0][i] == '&')
		(*j) = help_to_take_file(*j, &file[0]);
	else
	{
		while (file[0][*j] != '\0' && file[0][*j] != ' ' && file[0][*j] != '\t'
			&& file[0][*j] != '\n' && file[0][*j] != '<' && file[0][*j] != '>')
			(*j)++;
	}
	b = (*j - i);
	line = ft_strsub(file[0], i, b);
	return (line);
}
