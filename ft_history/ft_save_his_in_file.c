/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_save_his_in_file.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ommadhi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 17:45:04 by ommadhi           #+#    #+#             */
/*   Updated: 2020/11/27 09:59:39 by ommadhi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_readline.h"

void		ft_save_his_in_file()
{
	int		fd;
	int		i;

	i = 1;
	fd = open("ressources/.42sh_history.txt", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd < 0)
		return ;
	while (g_his && g_his->prev)
		g_his = g_his->prev;
	while (g_his)
	{
		ft_putendl_fd(g_his->data, fd);
		i++;
		g_his = g_his->next;
	}
	close(fd);
}

void		ft_get_history_from_file(t_his	**his)
{
	char	*line;
	int		fd;

	if (!(fd = open("ressources/.42sh_history.txt", O_RDONLY)))
		return ;
	while (get_next_line(fd, &line) > 0)
	{
		if (line && *line)
			ft_add_his(his, line);
		ft_strdel(&line);
	}
	close(fd);
}
