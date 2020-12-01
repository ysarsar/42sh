/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_v3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mac <mac@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/23 03:26:27 by hiantrin          #+#    #+#             */
/*   Updated: 2020/11/19 03:05:30 by mac              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/sh.h"

void	help_to_finish_the_pipe(char **line)
{
	char	*new;
	char	*str;
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
		ft_strdel(&line[0]);
	str = line[0];
	line[0] = ft_strjoin(line[0], new);
	free(new);
	free(str);
}

int		ft_filter_2eme(int len, char *cont, int index)
{
	len++;
	while (cont[len])
	{
		if (cont[len] == 92 && index == 34)
			len++;
		else if (cont[len] == '$' && cont[len + 1] == '{' && index == 34)
		{
			len = to_the_end_parent(cont, len, '}', '{');
			if (cont[len] != '}')
				len--;
		}
		else if (cont[len] == '$' && cont[len + 1] == '(' && index == 34)
		{
			len = to_the_end_parent(cont, len, ')', '(');
			if (cont[len] != ')')
				len--;
		}
		else if (cont[len] == index)
			return (len);
		if (cont[len] != '\0')
			len++;
	}
	return (0);
}

char	*read_quote(char *cont, int index)
{
	char	*lire;
	char	*tmp;
	char	*tmp2;

	lire = NULL;
	if (index == 39)
		lire = my_readline(&g_his, "quote>");
	else
		lire = my_readline(&g_his, "dquote>");
	if (!lire)
	{
		ft_strdel(&cont);
		return (NULL);
	}
	tmp = ft_strjoin(cont, "\n");
	tmp2 = ft_strjoin(tmp, lire);
	free(cont);
	ft_strdel(&tmp);
	ft_strdel(&lire);
	return (tmp2);
}

char	*ft_filter_quote(char *cont, int c, int *fi, int len)
{
	int		resul;

	resul = 0;
	while (cont[len])
	{
		if (cont[len] == 92)
			len++;
		else if (cont[len] == 34 || cont[len] == 39)
		{
			c = ((int)cont[len]);
			if ((resul = ft_filter_2eme(len, cont, c)) == 0)
				cont = read_quote(cont, c);
			if (!cont)
				return (NULL);
			len = -1;
			if (resul != 0)
				len = resul;
			else
				fi[0] = -1;
		}
		if (cont[len] != '\0' || len == -1)
			len++;
	}
	return (cont);
}
