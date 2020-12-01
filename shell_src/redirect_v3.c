/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_v3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiantrin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/23 04:53:36 by hiantrin          #+#    #+#             */
/*   Updated: 2020/10/23 04:53:38 by hiantrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/sh.h"

int		check_number_or_word(char *file)
{
	int i;

	i = 0;
	while (file[i])
	{
		if (file[i] < 48 || file[i] > 57)
			return (0);
		i++;
	}
	return (1);
}

int		trait_the_and(char *file, int out, int type, t_process **process)
{
	char	*file2;

	file2 = &file[1];
	if (file2[0] == '\0')
	{
		ft_putendl_fd("42sh: syntax error near unexpected token `newline'",
			process[0]->errorput);
		return (0);
	}
	else if (file2[0] == '-')
		return (if_two(out, type, &process[0]));
	else if (check_number_or_word(file2) == 0)
		return (if_three(file2, out, type, &process[0]));
	else
		return (if_four(file2, out, type, &process[0]));
	return (1);
}

int		parse_to_two(char *file, int out, int type, t_process **process)
{
	if (file[0] == '&')
	{
		if (trait_the_and(file, out, type, &process[0]) == 0)
		{
			free(file);
			return (0);
		}
	}
	else
	{
		if (trait_the_type(file, out, type, &process[0]) == 0)
		{
			free(file);
			return (0);
		}
	}
	return (2);
}
