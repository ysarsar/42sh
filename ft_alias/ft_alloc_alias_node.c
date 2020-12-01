/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_alloc_alias_node.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ommadhi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/26 12:14:03 by ommadhi           #+#    #+#             */
/*   Updated: 2020/11/26 12:24:34 by ommadhi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_alias.h"

void		ft_alloc_alias_node(t_alias **alias)
{
	*alias = (t_alias *)malloc(sizeof(t_alias));
	(*alias)->next = NULL;
	(*alias)->alias = NULL;
	(*alias)->value = NULL;
}
