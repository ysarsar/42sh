/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ctr_c.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ommadhi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/04 08:12:52 by ommadhi           #+#    #+#             */
/*   Updated: 2020/10/28 02:30:43 by ommadhi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_readline.h"

void					sig_c(int sig)
{
	struct termios		config;
	struct termios		def;
	int					fd;

	fd = open("/dev/tty", O_RDWR);
	(void)sig;
	tcgetattr(fd, &def);
	tcgetattr(fd, &config);
	ft_strclr(g_l.str);
	g_l.i = 0;
	ft_putstr("\n(42sh)$> ");
	config.c_lflag &= ~(ECHO | ICANON);
	tcsetattr(fd, TCSANOW, &config);
	get_cur_position();
	tcsetattr(fd, TCSANOW, &def);
	close(fd);
}
