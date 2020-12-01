/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subshell.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiantrin <hiantrin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/21 23:25:46 by hiantrin          #+#    #+#             */
/*   Updated: 2020/11/23 12:25:29 by hiantrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/sh.h"

int		print_error_sub(char *tmp)
{
	if (tmp != NULL)
		free(tmp);
	ft_putendl("bash: syntax error near unexpected token `()'");
	return (0);
}

int		trait_it_sub(char *str, int i, int *b)
{
	char	c;
	int		j;
	char	*tmp;

	j = i;
	tmp = NULL;
	while (str[i])
	{
		c = str[i];
		if (c == 34 || c == 39)
			i = count_replace_env(str, i, c);
		else if (str[i] == 92)
			i++;
		else if (str[i] == '$' && (str[i + 1] == '{' || str[i + 1] == '('))
			i = jump_cursh_parent(str, i);
		else if (str[i] == ')')
			return (help_trait_it_sub(str, i, j, &b[0]));
		if (str[i] != '\0')
			i++;
	}
	return (1);
}

int		loop_sub(char *str, int *b)
{
	int i;
	int c;

	i = 0;
	c = 0;
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n')
		i++;
	if (str[i] == '(')
	{
		c = trait_it_sub(str, i, &b[0]);
		return (c);
	}
	b[0] = 0;
	return (2);
}

int		checker_subshell(char *str)
{
	int		i;

	i = 0;
	if (loop_sub(str, &i) == 0)
		return (0);
	if (i == 0)
		return (checker_for_anyparent(str));
	else
		return (checker_for_re_sub(str, i));
}
