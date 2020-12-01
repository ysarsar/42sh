/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ommadhi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/16 18:52:34 by ommadhi           #+#    #+#             */
/*   Updated: 2019/04/18 22:10:44 by ommadhi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*new;
	t_list	*head;

	if (lst != NULL)
	{
		head = f(lst);
		new = head;
		lst = lst->next;
		while (lst)
		{
			new->next = f(lst);
			new = new->next;
			lst = lst->next;
		}
		return (head);
	}
	return (NULL);
}
