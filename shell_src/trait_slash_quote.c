/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trait_slash_quote.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiantrin <hiantrin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/21 03:47:38 by hiantrin          #+#    #+#             */
/*   Updated: 2020/10/31 18:50:09 by ommadhi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/sh.h"

char	*help_replace_by_s_q(char *str, int *end, int start, char *trait)
{
	char	*first;
	char	*twoo;
	char	*tmp;

	first = ft_strsub(str, 0, end[0]);
	twoo = ft_strjoin(first, trait);
	tmp = str;
	str = ft_strjoin(twoo, &str[start]);
	end[0] = ft_strlen(twoo);
	free(tmp);
	free(twoo);
	free(trait);
	free(first);
	return (str);
}

char	*replace_by_s_q(char *str, int *start, int *end, int type)
{
	char	*trait;
	char	*twoo;
	char	*tmp;

	trait = ft_strsub(str, end[0], start[0] - end[0]);
	if (type == 0)
		trait = move_slash(trait);
	if (type == 1)
		trait = move_quote(trait, 0);
	if (end[0] != 0)
		str = help_replace_by_s_q(str, &end[0], start[0], trait);
	else
	{
		twoo = trait;
		tmp = str;
		str = ft_strjoin(twoo, &str[start[0]]);
		end[0] = ft_strlen(twoo);
		free(tmp);
		free(twoo);
	}
	start[0] = end[0];
	return (str);
}
