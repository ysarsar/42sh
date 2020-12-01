/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help_slash_quote.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiantrin <hiantrin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/23 05:19:21 by hiantrin          #+#    #+#             */
/*   Updated: 2020/10/23 05:35:48 by hiantrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/sh.h"

int		check_if_there_slash(char *str, int i)
{
	while (i > 0)
	{
		i--;
		if (str[i] == 92 && (i - 1 < 0 || str[i - 1] != 92))
			return (0);
		else if (str[i] != 92)
			return (1);
		i--;
	}
	return (1);
}

int		jump_for_move_quote(char *line, char c, int i)
{
	i++;
	while (line[i] != c)
	{
		if (line[i] == 92 && c == 34)
			i = i + 2;
		else
			i++;
	}
	return (i);
}

char	*help_finish_slach(char *str, int i, char *new)
{
	char	*tmp;

	tmp = str;
	str = ft_strsub(str, 0, i);
	free(tmp);
	tmp = str;
	str = ft_strjoin(str, new);
	free(tmp);
	free(new);
	return (str);
}
