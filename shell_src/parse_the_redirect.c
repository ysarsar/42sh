/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_the_redirect.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mac <mac@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/25 03:20:30 by hiantrin          #+#    #+#             */
/*   Updated: 2020/11/08 18:35:56 by mac              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/sh.h"

int		type_one(char *file, t_process **process, int out)
{
	int			b;

	if (help_type_one(file, process[0]->errorput) == 0)
		return (0);
	if ((b = help_to_norme_type(file)) == -1)
		return (print_p_d(file, process[0]->errorput));
	if (out == -1 || out == 1)
	{
		if (process[0]->output != 1 && process[0]->output != -1)
			close(process[0]->output);
		process[0]->output = b;
	}
	if (out == 2)
	{
		if (process[0]->errorput != 2 && process[0]->errorput != -1)
			close(process[0]->errorput);
		process[0]->errorput = b;
	}
	if (out == 0)
	{
		if (process[0]->input != 0 && process[0]->input != -1)
			close(process[0]->input);
		process[0]->input = b;
	}
	return (1);
}

int		type_two(char *file, t_process **process, int out)
{
	int b;

	close(open(file, O_CREAT, 0644));
	if ((b = open(file, O_WRONLY | O_APPEND)) == -1)
		return (print_p_d(file, process[0]->errorput));
	if (out == -1 || out == 1)
	{
		if (process[0]->output != 1 && process[0]->output != -1)
			close(process[0]->output);
		process[0]->output = b;
	}
	if (out == 2)
	{
		if (process[0]->errorput != 2 && process[0]->errorput != -1)
			close(process[0]->errorput);
		process[0]->errorput = b;
	}
	if (out == 0)
	{
		if (process[0]->input != 0 && process[0]->input != -1)
			close(process[0]->input);
		process[0]->input = b;
	}
	return (1);
}

int		type_three(char *file, t_process **process, int out)
{
	int			b;

	if (error_type_three(file, process[0]->errorput) == 0)
		return (0);
	if ((b = open(file, O_RDONLY)) == -1)
		return (print_p_d(file, process[0]->errorput));
	if (out == -1 || out == 0)
	{
		if (process[0]->input != 0 && process[0]->input != -1)
			close(process[0]->input);
		process[0]->input = b;
	}
	if (out == 2)
	{
		if (process[0]->errorput != 2 && process[0]->errorput != -1)
			close(process[0]->errorput);
		process[0]->errorput = b;
	}
	if (out == 1)
	{
		if (process[0]->output != 1 && process[0]->output != -1)
			close(process[0]->output);
		process[0]->output = b;
	}
	return (1);
}

int		type_four(char *file, t_process **process, int out)
{
	int b;

	b = help_redirect(file, NULL);
	if (out == -1 || out == 0)
	{
		if (process[0]->input != 0 && process[0]->input != -1)
			close(process[0]->input);
		process[0]->input = b;
	}
	if (out == 2)
	{
		if (process[0]->errorput != 2 && process[0]->errorput != -1)
			close(process[0]->errorput);
		process[0]->errorput = b;
	}
	if (out == 1)
	{
		if (process[0]->output != 1 && process[0]->output != -1)
			close(process[0]->output);
		process[0]->output = b;
	}
	return (1);
}

int		trait_the_type(char *file, int out, int type, t_process **process)
{
	if (type == 1)
	{
		if (type_one(file, &process[0], out) == 0)
			return (0);
	}
	else if (type == 2)
	{
		if (type_two(file, &process[0], out) == 0)
			return (0);
	}
	else if (type == 3)
	{
		if (type_three(file, &process[0], out) == 0)
			return (0);
	}
	else if (type == 4)
	{
		if (type_four(file, &process[0], out) == 0)
			return (0);
	}
	return (1);
}
