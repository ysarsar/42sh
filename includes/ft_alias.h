/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_alias.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ommadhi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 18:38:02 by ommadhi           #+#    #+#             */
/*   Updated: 2020/11/27 09:56:38 by ommadhi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_ALIAS_H
#define FT_ALIAS_H

#include "ft_readline.h"
#include "sh.h"
#include "ft_autocmp.h"

typedef struct s_alias
{
	char		*alias;
	char		*value;
	struct s_alias		*next;
}				t_alias;

t_alias *g_alias;

void            ft_set_alias(char *cmd, t_alias **g_alias);
void            ft_save_aliases_in_file();
void		ft_free_aliases_list(t_alias **aliases);
void            ft_get_aliases_from_file(t_alias  **aliases);
void            ft_alloc_alias_node(t_alias **alias);
void                    ft_print_one_alias(char *alias, t_alias *g_alias);
void                            ft_alias(char **args, t_alias **g_alias);
void            ft_print_aliases(t_alias *aliases);
void            ft_unalias(char **args, t_alias **alias);

#endif
