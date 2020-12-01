/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help_cd_v2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiantrin <hiantrin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/23 03:46:06 by hiantrin          #+#    #+#             */
/*   Updated: 2020/10/25 11:00:33 by hiantrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/sh.h"

void	print_type(mode_t st_mode, char *perm)
{
	if ((st_mode & S_IFMT) == S_IFDIR)
		perm[0] = 'd';
	else if ((st_mode & S_IFMT) == S_IFREG)
		perm[0] = '-';
	else if ((st_mode & S_IFMT) == S_IFLNK)
		perm[0] = 'l';
	else if ((st_mode & S_IFMT) == S_IFIFO)
		perm[0] = 'p';
	else if ((st_mode & S_IFMT) == S_IFCHR)
		perm[0] = 'c';
	else if ((st_mode & S_IFMT) == S_IFBLK)
		perm[0] = 'b';
	else if ((st_mode & S_IFMT) == S_IFSOCK)
		perm[0] = 's';
}

char	*check(char *str)
{
	struct stat	l;
	char		*mine;

	mine = (char *)malloc(sizeof(char) * 2);
	mine[1] = '\0';
	if (lstat(str, &l) == 0)
	{
		print_type(l.st_mode, mine);
		if (!(l.st_mode & S_IRUSR) && mine[0] == 'd')
			mine[0] = 'r';
		if (!(l.st_mode & S_IXUSR) && (mine[0] == 'd' || mine[0] == 'r'))
			mine[0] = 'x';
	}
	else if (lstat(str, &l) == -1)
	{
		free(mine);
		mine = NULL;
	}
	return (mine);
}

int		mylen(char *str)
{
	int i;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	return (i);
}

char	*search_home(t_env *list)
{
	t_env	*first;

	first = list;
	while (first)
	{
		if (ft_strncmp(first->name, "HOME", mylen(first->name)) == 0)
			return (first->environ);
		first = first->next;
	}
	return (NULL);
}

void	norme_to_cd(t_process *process, t_job *job, char **argv, int i)
{
	add_pwd(process, job, "OLDPWD");
	if ((i == 0 || ft_strcmp(argv[1], "~") == 0)
		&& access(search_home(g_shell->env), F_OK) == 0)
		chdir(search_home(g_shell->env));
	if (access(argv[1], F_OK) == 0)
		chdir(argv[1]);
	add_pwd(process, job, "PWD");
	g_the_status = 0;
}
