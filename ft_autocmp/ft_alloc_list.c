/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_alloc_list.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ommadhi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/01 17:49:52 by ommadhi           #+#    #+#             */
/*   Updated: 2020/11/01 17:50:35 by ommadhi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_autocmp.h"

void		ft_alloc_node(t_dlist **node)
{
	*node = (t_dlist *)malloc(sizeof(t_dlist));
	(*node)->next = NULL;
	(*node)->data = NULL;
}
