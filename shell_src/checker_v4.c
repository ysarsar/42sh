/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_v4.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiantrin <hiantrin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/23 03:26:45 by hiantrin          #+#    #+#             */
/*   Updated: 2020/11/23 00:18:58 by hiantrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/sh.h"

int		help_check_curch(char **str, int *count)
{
	int i;

	i = count[0];
	i = to_the_end_parent(str[0], i, '}', '{');
	if (str[0][i] != '}')
	{
		str[0] = complte_parent_cursh(str[0]);
		return (-1);
	}
	if (check_set_curch(str[0], i, count[0] + 1) == 0)
		return (0);
	count[0] = i;
	return (1);
}

int		error_check_cursh(void)
{
	ft_putendl_fd("42sh: parse error near `}'", 2);
	return (0);
}

int		check_cursh(char **str, int i, char c, int f)
{
	while (str[0][i])
	{
		c = str[0][i];
		if (c == 39)
			i = count_replace_env(str[0], i, c) + 1;
		else if (c == 92)
			i = i + 2;
		else if (str[0][i] == '$' && str[0][i + 1] == '(')
		{
			i = to_the_end_parent(str[0], i, ')', '(');
			if (str[0][i] == ')')
				i++;
		}
		else if (str[0][i] == '$' && str[0][i + 1] == '{')
		{
			i++;
			if ((f = help_check_curch(&str[0], &i)) == 0 || f == -1)
				return (f);
			i++;
		}
		else if (str[0][i] != '\0')
			i++;
	}
	return (1);
}

int		help_check_if_and_and(char **str, int i)
{
	if (((str[0][i] != ' ' && str[0][i] != '\t' && str[0][i] != '\n')
		|| ((str[0][i] == ' ' || str[0][i] == '\t' || str[0][i] == '\n')
		&& str[0][i - 1] && str[0][i - 1] == 92)) && str[0][i] != '&'
		&& str[0][i] != '|')
		return (1);
	else if ((str[0][i] == '|' ||
		(str[0][i] == '&' && str[0][i + 1] == '&'))
		&& check_if_there_slash(str[0], i))
	{
		help_to_finish_the_pipe(&str[0]);
		return (-1);
	}
	else if (str[0][i] == 92 && str[0][i + 1] == '\0'
		&& check_if_there_slash(str[0], i))
	{
		str[0] = finish_slach(str[0]);
		return (-1);
	}
	return (1);
}
