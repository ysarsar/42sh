/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_aliases_list.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ommadhi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/26 12:12:21 by ommadhi           #+#    #+#             */
/*   Updated: 2020/11/26 12:25:57 by ommadhi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_alias.h"

void			ft_free_aliases_list(t_alias **aliases)
{
	t_alias		*nd;
	t_alias		*tmp;

	nd = *aliases;
	if (!*aliases)
		ft_putendl("NOGHTHING!!!");
	while (nd)
	{
		tmp = nd;
		nd = nd->next;
		ft_strdel(&tmp->alias);
		ft_strdel(&tmp->value);
		ft_memdel((void**)tmp);
	}
}
