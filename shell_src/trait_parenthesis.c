/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trait_parenthesis.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiantrin <hiantrin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/21 23:26:12 by hiantrin          #+#    #+#             */
/*   Updated: 2020/11/23 00:35:59 by hiantrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/sh.h"

int		to_the_end_parent(char *str, int i, char c, char a)
{
	char	b;

	i++;
	while (str[i] && str[i] != c)
	{
		b = str[i];
		if (b == 34 || b == 39)
			i = count_replace_env(str, i, b) + 1;
		else if (str[i] == 92)
		{
			i++;
			if (str[i] != '\0')
				i++;
		}
		else if (str[i] == '$' && str[i + 1] == a)
		{
			i = to_the_end_parent(str, i, c, a);
			if (str[i] == c)
				i++;
		}
		else
			i++;
	}
	return (i);
}

int		print_the_error_sub(void)
{
	ft_putstr_fd("42sh: command substitution: line 1:", 2);
	ft_putendl_fd("unexpected EOF while looking for matching `}'", 2);
	ft_putstr_fd("42sh: command substitution: line 2:", 2);
	ft_putendl_fd("syntax error: unexpected end of file", 2);
	return (0);
}

int		help1_e_parent(char *str)
{
	ft_putstr_fd("42sh: command substitution: line 1: `", 2);
	ft_putstr_fd(str, 2);
	ft_putendl_fd("'", 2);
	return (0);
}

int		mini_checker_e_parent(char *str, int i)
{
	if (check_count_and(str, 0, 0) == 0)
		return (help1_e_parent(str));
	while (str[i])
	{
		if (str[i] == 39)
			i = count_replace_env(str, i, 39) + 1;
		else if (str[i] == 92)
			i = i + 2;
		else if (str[i] == '$' && str[i + 1] == '{')
		{
			i = to_the_end_parent(str, i, '}', '{');
			if (str[i] == '}')
				i++;
			else
				return (print_the_error_sub());
		}
		else if (str[i] == '$' && str[i + 1] == '(')
			i = to_the_end_parent(str, i, ')', '(') + 1;
		else if (str[i] == '(' || str[i] == ')')
			return (print_error_parenthesis(str, str[i], i));
		else if (str[i] != '\0')
			i++;
	}
	return (1);
}
