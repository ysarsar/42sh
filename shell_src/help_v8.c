/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help_v8.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiantrin <hiantrin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/23 10:51:42 by hiantrin          #+#    #+#             */
/*   Updated: 2020/11/23 12:59:03 by hiantrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/sh.h"

char	*help_help_bonus(char *line, int *i, int *j)
{
	char *tmp;

	tmp = ft_strsub(line, j[0], i[0] - j[0]);
	j[0] = i[0] + 1;
	return (tmp);
}

char	*help_help_split_and_and(char *line, int *i, int *j)
{
	char *tmp;

	tmp = ft_strsub(line, j[0], i[0] - j[0]);
	i[0] = i[0] + 1;
	j[0] = i[0] + 1;
	return (tmp);
}

int		help_trait_it_sub(char *str, int i, int j, int *b)
{
	char	*tmp;

	tmp = ft_strsub(str, j + 1, i - (j + 1));
	if (i == j + 1 || search_no_espace(tmp) == 0)
		return (print_error_sub(tmp));
	if (tmp != NULL)
		free(tmp);
	b[0] = i + 1;
	return (1);
}

int		half_checker_for_re_sub(char *str, int i)
{
	int j;

	j = i;
	while (str[i])
	{
		while (str[i] && (str[i] == ' ' || str[i] == '\t' || str[i] == '\n'))
			i++;
		if (str[i] == '\0')
			return (1);
		if ((str[i] == '>' || str[i] == '<')
			&& check_that_number(str, j, i) == 1)
		{
			i = jump_re_forsub(str, i);
			j = i;
		}
		else
			return (print_error_one_word(str, i));
	}
	return (1);
}

int		help_trait_v3(t_process **process, t_job **j, int *count, int a)
{
	init_fifo();
	make_the_put(&process[0], &j[0]);
	if (g_if_sub == 2 && a == 0)
		process[0]->input = g_re.input;
	if (g_if_sub == 2 && process[0]->next == NULL)
		process[0]->command = make_sub_happen(process[0]->command, &process[0]);
	if (g_if_sub == 1 && process[0]->next == NULL)
		process[0]->command = join_the_sub(process[0]->command);
	if (final_trait(process[0]->command, &process[0], &j[0]) == 1)
	{
		count[0] = count[0] + 1;
		process[0]->type = COMMAND_EXTERNAL;
		process[0] = process[0]->next;
		return (1);
	}
	return (0);
}
