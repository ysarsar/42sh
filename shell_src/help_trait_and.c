/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help_trait_and.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mac <mac@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/26 22:36:57 by hiantrin          #+#    #+#             */
/*   Updated: 2020/10/07 23:01:35 by mac              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/sh.h"

int		if_three(char *file2, int out, int type, t_process **process)
{
	if ((out != 1 && out != -1) || type == 3)
	{
		ft_putstr_fd("42sh: ", process[0]->errorput);
		ft_putstr_fd(file2, process[0]->errorput);
		ft_putendl_fd(": ambiguous redirect", process[0]->errorput);
		return (0);
	}
	else if (type == 2 || type == 4)
	{
		ft_putendl_fd("42sh: syntax error near unexpected token `&'",
				process[0]->errorput);
		return (0);
	}
	else if ((out == 1 || out == -1) && type == 1)
	{
		trait_the_type(file2, out, type, &process[0]);
		process[0]->errorput = process[0]->output;
		return (1);
	}
	return (1);
}

int		if_two(int out, int type, t_process **process)
{
	if (type == 2 || type == 4)
	{
		ft_putendl_fd("42sh: syntax error near unexpected token `&'",
				process[0]->errorput);
		return (0);
	}
	if (out == 0 || (type == 3 && out == -1))
		process[0]->input = -1;
	if (out == 1 || (type == 1 && out == -1))
		process[0]->output = -1;
	if (out == 2)
		process[0]->errorput = -1;
	if (out > 2 && (type == 1 || type == 3))
		close(out);
	return (1);
}

int		print_bad_file(char *file2, int error)
{
	ft_putstr_fd("42sh: ", error);
	ft_putstr_fd(file2, error);
	ft_putendl_fd(": bad file descriptor", error);
	return (0);
}

int		print_syntax_error(int error)
{
	ft_putendl_fd("42sh: syntax error near unexpected token `&'",
			error);
	return (0);
}

int		if_four(char *file2, int out, int type, t_process **process)
{
	if (type == 2 || type == 4)
		return (print_syntax_error(process[0]->errorput));
	else if (atoi(file2) != 1 && atoi(file2) != 0 && atoi(file2) != 2)
		return (print_bad_file(file2, process[0]->errorput));
	else if (type == 1)
	{
		if (out == 1 || out == -1)
			process[0]->output = h_f_f(file2, process[0], process[0]->output);
		else if (out == 0)
			process[0]->input = h_f_f(file2, process[0], process[0]->input);
		else if (out == 2)
			process[0]->errorput = h_f_f(file2, process[0],
				process[0]->errorput);
	}
	else if (type == 3)
	{
		if (out == 0 || out == -1)
			process[0]->input = h_f_f(file2, process[0], process[0]->input);
		else if (out == 1)
			process[0]->output = h_f_f(file2, process[0], process[0]->output);
		else if (out == 2)
			process[0]->errorput = h_f_f(file2, process[0],
				process[0]->errorput);
	}
	return (1);
}
