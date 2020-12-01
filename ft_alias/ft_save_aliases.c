#include "../includes/ft_alias.h"

void				ft_save_aliases_in_file(void)
{
	int			fd;
	t_alias			*nd;

	nd = g_alias;
	fd = open("ressources/.42sh_alias.txt", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	while (nd)
	{
		ft_putstr_fd("alias ^", fd);
		ft_putstr_fd(nd->alias, fd);
		ft_putstr_fd("=", fd);
		ft_putendl_fd(nd->value, fd);
		nd = nd->next;
	}
	close(fd);
}

void				ft_get_aliases_from_file(t_alias **aliases)
{
	char			*line;
	int			fd;

	if (!(fd = open("ressources/.42sh_alias.txt", O_RDONLY)))
		return ;
	while (get_next_line(fd, &line) > 0)
	{
		if (line && *line)
			ft_set_alias(ft_strrchr(line, '^'), aliases);
		ft_strdel(&line);
	}
	close(fd);
}
