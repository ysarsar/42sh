/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help_v4.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mac <mac@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/23 03:52:07 by hiantrin          #+#    #+#             */
/*   Updated: 2020/11/28 12:45:08 by mac              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/sh.h"

char	*to_move_s_q(char **str, char c, int *start, int *end)
{
	start[0] = start[0] + 1;
	while (str[0][start[0]] && str[0][start[0]] != c)
	{
		if (str[0][start[0]] == 92 && c == 34)
			start[0] = start[0] + 2;
		else
			start[0] = start[0] + 1;
	}
	start[0] = start[0] + 1;
	str[0] = replace_by_s_q(str[0], &start[0], &end[0], 1);
	return (str[0]);
}

void	another_help_f_s_q(int *start, int *type)
{
	start[0] = start[0] + 2;
	type[0] = 0;
}

int		while_for_q_s(char **str)
{
	int fi;

	fi = 0;
	str[0] = ft_filter_quote(str[0], 0, &fi, 0);
	if (fi == -1)
		return (-1);
	if ((fi = check_cursh(&str[0], 0, 'a', 0)) == -1)
		return (-1);
	if (fi == 0)
		return (0);
	return (check_parenthesis(&str[0]));
}
