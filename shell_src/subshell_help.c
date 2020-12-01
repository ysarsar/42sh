/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subshell_help.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiantrin <hiantrin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/22 00:54:24 by hiantrin          #+#    #+#             */
/*   Updated: 2020/11/23 12:43:10 by hiantrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/sh.h"

void	help_print_error_parenthesis(char *line, int i)
{
	int		save;
	char	*tmp;

	save = i;
	while (line[i] != ')')
		i++;
	if (i == save + 1)
		ft_putendl_fd("bash: syntax error near unexpected token `()'", 2);
	else
	{
		tmp = ft_strsub(line, save + 1, i - (save + 1));
		ft_putstr_fd("bash: syntax error near unexpected token `", 2);
		ft_putstr_fd(tmp, 2);
		ft_putendl_fd("'", 2);
		free(tmp);
	}
}

int		print_error_parenthesis(char *line, char c, int i)
{
	if (c == ')')
	{
		ft_putendl_fd("bash: syntax error near unexpected token `)'", 2);
		return (0);
	}
	else if (c == '(' & line[i + 1] == '\0')
	{
		ft_putendl_fd("bash: syntax error near unexpected token `('", 2);
		return (0);
	}
	else if (c == '(')
		help_print_error_parenthesis(line, i);
	return (0);
}

int		checker_for_anyparent(char *str)
{
	int		i;
	int		c;

	i = 0;
	while (str[i])
	{
		c = str[i];
		if (c == 34 || c == 39)
			i = count_replace_env(str, i, c);
		else if (str[i] == 92)
			i++;
		else if (str[i] == '$' && (str[i + 1] == '{' || str[i + 1] == '('))
			i = jump_cursh_parent(str, i);
		else if (c == '(' || c == ')')
			return (print_error_parenthesis(str, c, i));
		if (str[i] != '\0')
			i++;
	}
	return (1);
}

int		print_error_one_word(char *str, int i)
{
	int		j;
	char	*tmp;

	j = i;
	while (str[i] != ' ' && str[i] != '\t' && str[i] != '\n')
		i++;
	tmp = ft_strsub(str, j, i - j);
	ft_putstr_fd("bash: syntax error near unexpected token `", 2);
	ft_putstr_fd(tmp, 2);
	ft_putendl_fd("'", 2);
	free(tmp);
	return (0);
}

int		checker_for_re_sub(char *str, int i)
{
	int		j;
	char	*tmp;

	j = 0;
	while (str[j] && (str[j] == ' ' || str[j] == '\t' || str[j] == '\n'))
		j++;
	tmp = ft_strsub(str, j + 1, (i - 1) - (j + 1));
	if (checker_for_anyparent(tmp) == 0 || check_count_and(tmp, 0, 0) == 0
			|| check_for_end_pipe(tmp, 0, 'a', NULL) == 0)
	{
		free(tmp);
		return (0);
	}
	free(tmp);
	return (half_checker_for_re_sub(str, i));
}
