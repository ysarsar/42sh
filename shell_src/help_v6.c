/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help_v6.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiantrin <hiantrin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/11 18:35:04 by hiantrin          #+#    #+#             */
/*   Updated: 2020/11/23 00:19:09 by hiantrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/sh.h"

int		to_end_parenthesis(int i, char **line)
{
	i++;
	i = to_the_end_parent(line[0], i, ')', '(');
	if (line[0][i] == '\0')
	{
		line[0] = complte_parent_cursh(line[0]);
		return (-1);
	}
	return (i);
}

int		check_parenthesis(char **line)
{
	int		i;
	char	c;

	i = 0;
	while (line[0][i])
	{
		c = line[0][i];
		if (c == 39)
			i = count_replace_env(line[0], i, c) + 1;
		else if (c == 92)
			i = i + 2;
		else if (line[0][i] == '$' && line[0][i + 1] == '{')
			i = mini_norme_check_parenthesis(line[0], i);
		else if (line[0][i] == '$' && line[0][i + 1] == '(')
		{
			if ((i = to_end_parenthesis(i, &line[0])) == -1)
				return (-1);
			i++;
		}
		else if (line[0][i] != '\0')
			i++;
	}
	return (1);
}

char	*complte_parent_cursh(char *str)
{
	char	*new;
	char	*tmp;
	int		i;

	i = 0;
	new = NULL;
	while (!i || search_no_espace(new) == 0)
	{
		i++;
		ft_strdel(&new);
		new = my_readline(&g_his, "> ");
	}
	if (!new && i)
		ft_strdel(&str);
	tmp = str;
	str = ft_strjoin(tmp, "\n");
	free(tmp);
	tmp = str;
	str = ft_strjoin(tmp, new);
	free(tmp);
	free(new);
	return (str);
}
