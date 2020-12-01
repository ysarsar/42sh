/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subshell_help2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiantrin <hiantrin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/22 02:32:34 by hiantrin          #+#    #+#             */
/*   Updated: 2020/11/23 12:43:15 by hiantrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/sh.h"

int		jump_re_forsub(char *str, int i)
{
	while (str[i] && (str[i] == '>' || str[i] == '<' || str[i] == '&'))
		i++;
	while (str[i] && (str[i] == ' ' || str[i] == '\t' || str[i] == '\n'))
		i++;
	while (str[i] && (str[i] != ' ' && str[i] != '\t' && str[i] != '\n'))
		i++;
	return (i);
}

int		check_that_number(char *str, int j, int i)
{
	char	*tmp;

	tmp = ft_strsub(str, j, i - j);
	i = 0;
	while (tmp[i] && (tmp[i] == ' ' || tmp[i] == '\t' || tmp[i] == '\n'))
		i++;
	while (tmp[i])
	{
		if (tmp[i] < '0' || tmp[i] > '9')
		{
			free(tmp);
			return (0);
		}
		i++;
	}
	if (tmp != NULL)
		free(tmp);
	return (1);
}

int		search_for_pa(char *str, int i, char a)
{
	char	c;
	int		s;

	s = i;
	while (str[i])
	{
		c = str[i];
		if (c == 34 || c == 39)
			i = count_replace_env(str, i, c);
		else if (c == 92)
			i++;
		else if (str[i] == '$' && (str[i + 1] == '{' || str[i + 1] == '('))
			i = jump_cursh_parent(str, i);
		if (str[i] == a)
			return (i);
		if (str[i] != '\0')
			i++;
	}
	if (a == '}')
		return (s);
	i = i - 1;
	return (i);
}

int		jump_subshell(char *str, int i)
{
	char	c;

	c = str[i];
	if (c == '(')
		i = search_for_pa(str, i, ')');
	else if (c == '{')
		i = search_for_pa(str, i, '}');
	else
		return (0);
	return (i);
}

int		check_for_end_pipe(char *str, int i, char c, char *tmp)
{
	while (str[i])
	{
		c = str[i];
		if (c == 34 || c == 39)
			i = count_replace_env(str, i, c);
		else if (str[i] == 92)
			i++;
		else if (str[i] == '$' && (str[i + 1] == '{' || str[i + 1] == '('))
			i = jump_cursh_parent(str, i);
		if ((str[i] == '&' && str[i + 1] == '&') || str[i] == '|' ||
			(str[i] == '|' && str[i + 1] == '|'))
		{
			while (str[i] == '|' || str[i] == '&')
				i++;
			tmp = ft_strsub(str, i, ft_strlen(str) - i);
			if (search_no_espace(tmp) == 0)
				return (free_and_error(tmp));
			free(tmp);
			i--;
		}
		if (str[i] != '\0')
			i++;
	}
	return (1);
}
