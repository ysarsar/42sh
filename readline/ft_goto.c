/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_goto.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ommadhi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/03 23:44:49 by ommadhi           #+#    #+#             */
/*   Updated: 2020/03/07 00:20:14 by ommadhi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_readline.h"

void		ft_goto(int i, int j)
{
	tputs(tgoto(tgetstr("cm", NULL), i, j), 0, ft_putsfd);
}