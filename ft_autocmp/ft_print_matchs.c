/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_matchs.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ommadhi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/15 19:13:28 by ommadhi           #+#    #+#             */
/*   Updated: 2020/11/01 17:52:06 by ommadhi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_autocmp.h"

int						ft_count_list_nodes(t_dlist *matchs)
{
	int					nb;

	nb = 0;
	while (matchs && matchs->next)
	{
		matchs = matchs->next;
		nb++;
	}
	return (nb);
}

static int				ft_get_max_lent(t_dlist *match)
{
	int					maxlent;

	maxlent = 0;
	while (match)
	{
		if (maxlent < (int)ft_strlen(match->data))
			maxlent = ft_strlen(match->data);
		match = match->next;
	}
	return (maxlent);
}

void					ft_print_matchs(t_dlist *match, int index)
{
	int					i;
	int					j;
	int					maxlent;
	struct winsize		w;
	int					select;

	select = 0;
	ioctl(1, TIOCGWINSZ, &w);
	i = 0;
	j = g_pos.y;
	maxlent = ft_get_max_lent(match);
	while (match && w.ws_row > j)
	{
		if ((i + maxlent) > w.ws_col)
		{
			i = 0;
			j++;
		}
		tputs(tgoto(tgetstr("cm", NULL), i, j), 0, ft_putsfd);
		if (index == select)
			ft_put4str(tgetstr("us", NULL), "\033[7m", match->data, "\033[0m");
		else
			ft_putstr(match->data);
		i = i + maxlent + 1;
		match = match->next;
		select++;
	}
	tputs(tgoto(tgetstr("cm", NULL), i, j + 1), 0, ft_putsfd);
}
