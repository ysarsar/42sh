/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subshell_help3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiantrin <hiantrin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/23 02:16:39 by hiantrin          #+#    #+#             */
/*   Updated: 2020/11/23 12:37:28 by hiantrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/sh.h"

int		free_and_error(char *tmp)
{
	free(tmp);
	ft_putendl_fd("bash: syntax error near unexpected token `)'", 2);
	return (0);
}

char	*read_the_sub(char *str, int j, int i)
{
	char	*tmp;
	int		a;
	char	*new;

	a = 0;
	new = NULL;
	while (!a || search_no_espace(new) == 0)
	{
		a = 1;
		if (new != NULL)
			free(new);
		new = my_readline(&g_his, "> ");
	}
	tmp = ft_strsub(str, j, i - j);
	if (search_no_espace(tmp) == 0)
		str = ft_strjoin(str, " ");
	else
		str = ft_strjoin(str, "; ");
	free(tmp);
	tmp = str;
	str = ft_strjoin(str, new);
	free(tmp);
	return (str);
}

int		return_read_the_parent(char **str, int i, int j, int a)
{
	char	*tmp;

	if (a == 1)
	{
		tmp = str[0];
		str[0] = read_the_sub(str[0], j + 1, i);
		free(tmp);
		return (-1);
	}
	return (1);
}

int		read_the_parent(char **str, int a, int i, int j)
{
	char	c;

	while (str[0][i])
	{
		c = str[0][i];
		if (c == 34 || c == 39)
			i = count_replace_env(str[0], i, c);
		else if (str[0][i] == 92)
			i++;
		else if (str[0][i] == '$' && (str[0][i + 1] == '{'
			|| str[0][i + 1] == '('))
			i = jump_cursh_parent(str[0], i);
		else if (str[0][i] == '(')
		{
			j = i;
			a = 1;
		}
		else if (a == 1 && str[0][i] == ')')
			a = 0;
		if (str[0][i] != '\0')
			i++;
	}
	return (return_read_the_parent(&str[0], i, j, a));
}

void	second_loop_sub(char **str)
{
	int a;

	a = -1;
	while (a == -1)
		a = read_the_parent(&str[0], 0, 0, 0);
}
