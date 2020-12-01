/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_variables.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiantrin <hiantrin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/23 04:50:58 by hiantrin          #+#    #+#             */
/*   Updated: 2020/10/25 10:52:28 by hiantrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/sh.h"

void	help_to_two_table(t_env *save, char ***seto, char ***unseto)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (save)
	{
		if (save->flag == 0 || save->flag == 1)
			j++;
		if (save->flag == 2)
			i++;
		save = save->next;
	}
	seto[0] = (char **)malloc(sizeof(char *) * j + 1);
	seto[0][j] = NULL;
	unseto[0] = (char **)malloc(sizeof(char *) * i + 1);
	unseto[0][i] = NULL;
}

void	list_to_two_table(t_env *save, char ***seto, char ***unseto)
{
	char	*fre;
	int		i;
	int		j;

	help_to_two_table(save, &seto[0], &unseto[0]);
	i = 0;
	j = 0;
	while (save)
	{
		if (save->flag == 1 || save->flag == 0)
		{
			fre = ft_strjoin(save->name, "=");
			seto[0][j] = ft_strjoin(fre, save->environ);
			free(fre);
			j++;
		}
		if (save->flag == 2)
		{
			unseto[0][i] = ft_strdup(save->name);
			i++;
		}
		save = save->next;
	}
}

void	the_last_flag(char *set, t_env *save)
{
	t_env	*list;
	char	*str;

	list = g_shell->env;
	str = get_name(set);
	while (save)
	{
		if (ft_strcmp(save->name, str) == 0)
		{
			while (list)
			{
				if (ft_strcmp(list->name, str) == 0)
				{
					list->flag = save->flag;
					free(str);
					return ;
				}
				list = list->next;
			}
		}
		save = save->next;
	}
}

void	manage_variables2(t_env *save)
{
	char	**set;
	char	**unset;
	int		i;

	i = 0;
	if (save == NULL)
		return ;
	list_to_two_table(save, &set, &unset);
	while (set[i])
	{
		help_setenv(set[i], &g_shell->env);
		the_last_flag(set[i], save);
		i++;
	}
	i = 0;
	while (unset[i])
	{
		help_unsetenv(unset[i]);
		i++;
	}
	if (save != NULL)
		free_env_list(save);
}
