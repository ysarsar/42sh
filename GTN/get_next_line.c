/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szakaria <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/22 19:25:12 by szakaria          #+#    #+#             */
/*   Updated: 2019/05/07 18:39:44 by szakaria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*g_line(char *cont)
{
	int		len;
	char	*line;

	len = 0;
	while (cont[len] && cont[len] != '\n')
		len++;
	line = ft_strsub(cont, 0, len);
	return (line);
}

static char	*g_rest(char *cont)
{
	char	*rest;

	if (!ft_strchr(cont, '\n'))
		return (ft_strnew(0));
	rest = ft_strdup(ft_strchr(cont, '\n') + 1);
	return (rest);
}

int			get_next_line(int const fd, char **line)
{
	static char	*cont[4864];
	char		buff[BUFF_SIZE + 1];
	char		*tmp;
	int			i;

	if (fd < 0 || fd > 4864 || !line || BUFF_SIZE < 1)
		return (-1);
	if (!cont[fd])
		cont[fd] = ft_strnew(0);
	while (!ft_strchr(cont[fd], '\n') && (i = read(fd, buff, BUFF_SIZE)) > 0)
	{
		buff[i] = '\0';
		tmp = cont[fd];
		cont[fd] = ft_strjoin(cont[fd], buff);
		free(tmp);
	}
	if (i < 1 && !*cont[fd])
		return (i);
	*line = g_line(cont[fd]);
	tmp = cont[fd];
	cont[fd] = g_rest(cont[fd]);
	free(tmp);
	return (1);
}
