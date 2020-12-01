#ifndef FT_AUTOCMP_H
#define FT_AUTOCMP_H

#include "../libft/libft.h"
#include "sh.h"
#include "ft_readline.h"
#include <dirent.h>
#include <sys/types.h>

typedef struct				s_dlist
{
	char					*data;
	struct s_dlist			*next;
}							t_dlist;

typedef struct				s_tocmp
{
	int						type;
	int						index;
	char					*path;
	char					*tocmp;
	char					*fullcmd;
}							t_tocmp;

void        ft_search_in_env(t_tocmp cmp, t_dlist **matchs);
int                     ft_count_list_nodes(t_dlist *matchs);
int							ft_auto_comp(char **cmd, int *index);
void						ft_print_matchs(t_dlist *match, int index);
void						ft_search_for_bin(t_tocmp cmp, t_dlist **matchs);
void						ft_search_in_dirs(t_tocmp cmp, t_dlist **matchs);
int							init_autocmp(char **cmd, int *index);
char						*ft_cutcmd_and_gettype(char *cmd, int index, int *type);
void						ft_get_path(t_tocmp *cmd);
void						ft_alloc_node(t_dlist **node);
#endif
