/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help_variable.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiantrin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/23 04:29:56 by hiantrin          #+#    #+#             */
/*   Updated: 2020/10/23 04:29:58 by hiantrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/sh.h"

char	**create_new_argv(char **argv, int i)
{
	int		count;
	int		j;
	char	**str;

	count = 0;
	j = i;
	while (argv[j])
	{
		count++;
		j++;
	}
	str = (char **)malloc(sizeof(char *) * (count + 1));
	str[count] = NULL;
	count = 0;
	while (argv[i])
		str[count++] = ft_strdup(argv[i++]);
	free_2d(argv);
	return (str);
}

char	**help_re_null(t_env *save, t_env **env, char **argv)
{
	if (save != NULL)
		free_env_list(save);
	env[0] = NULL;
	free_2d(argv);
	return (NULL);
}
