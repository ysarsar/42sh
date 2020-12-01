/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_aliases.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ommadhi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/26 12:18:23 by ommadhi           #+#    #+#             */
/*   Updated: 2020/11/26 12:25:37 by ommadhi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_alias.h"

void		ft_print_aliases(t_alias *aliases)
{
	while (aliases)
	{
		ft_putstr("alias ");
		ft_put4str(aliases->alias, "=", aliases->value, "\n");
		aliases = aliases->next;
	}
}
