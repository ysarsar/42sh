/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filter_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mac <mac@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/23 03:47:03 by hiantrin          #+#    #+#             */
/*   Updated: 2020/11/28 11:20:42 by mac              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/sh.h"

int		jump_quote(char *s, int end)
{
	char	c;

	c = s[end];
	if (c == 92)
		end++;
	else if (c == 34 || c == 39)
	{
		end++;
		while (s[end] && s[end] != c)
		{
			if (s[end] == 92 && c == 34)
				end = end + 2;
			else
				end++;
		}
	}
	if (s[end] != '\0')
		end++;
	return (end);
}

int		leno(char *s)
{
	int	start;
	int end;
	int i;

	i = 0;
	end = 0;
	start = 0;
	while (s[start] != '\0')
	{
		while (s[start] != '\0' && (s[start] == ' ' || s[start] == '\t'))
			start++;
		if (s[start] == '\0')
			break ;
		end = start;
		while (s[end] != ' ' && s[end] != '\0' && s[start] != '\t')
			end = jump_quote(s, end);
		start = end;
		i++;
	}
	return (i);
}

char	*help_move_s_q(char *str, int start, int type, int end)
{
	char	c;

	while (str[start])
	{
		c = str[start];
		if (c == 34 || c == 39)
		{
			if (type == 0)
				str = replace_by_s_q(str, &start, &end, 0);
			str = to_move_s_q(&str, c, &start, &end);
			type = 1;
		}
		else if (c == 92)
			another_help_f_s_q(&start, &type);
		else
		{
			start++;
			type = 0;
		}
	}
	if (type == 0)
		str = replace_by_s_q(str, &start, &end, 0);
	return (str);
}

char	**ft_strsplito(char *s)
{
	int		start;
	int		end;
	char	**str;
	int		i;

	i = 0;
	start = 0;
	end = 0;
	str = (char **)malloc(sizeof(char *) * (leno(s) + 1));
	while (i < leno(s))
	{
		while (s[start] != '\0' && (s[start] == ' ' || s[start] == '\t'))
			start++;
		end = start;
		while (s[end] != ' ' && s[end] != '\0' && s[start] != '\t')
			end = jump_quote(s, end);
		str[i] = ft_strsub(s, start, (end - start));
		str[i] = help_move_s_q(str[i], 0, 0, 0);
		start = end;
		i++;
	}
	str[i] = NULL;
	return (str);
}

char	**mini_filter_h(char **str, t_env *env)
{
	int			i;
	char		**tabb;

	i = 0;
	str[0] = replace_with_env(str[0], env, i, 0);
	str[0] = replace_home(str[0], env);
	str[0] = switch_to_alias(str[0]);
	if (search_no_espace(str[0]) == 0)
		return (NULL);
	tabb = ft_strsplito(str[0]);
	return (tabb);
}
