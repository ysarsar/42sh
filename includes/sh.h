/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrxy <mrxy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/24 23:31:18 by szakaria          #+#    #+#             */
/*   Updated: 2020/12/01 00:42:48 by mrxy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SH_H
# define SH_H
# include "ft_alias.h"
# include "ft_autocmp.h"
# include "ft_readline.h"
# include "../libft/libft.h"
# include "../GTN/get_next_line.h"
# include <sys/types.h>
# include <sys/stat.h>
# include <dirent.h>
# include <sys/types.h>
# include <unistd.h>
# include <time.h>
# include <pwd.h>
# include <grp.h>
# include <time.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <signal.h>
# include <termios.h>

# include <sys/types.h>
# include <sys/stat.h>
# include <stdint.h>
# include <time.h>

# define BUFF_SIZE 1024
# define NR_J 30
# define TABLE_SIZE 1000

# define STATUS_RUNNING 0
# define STATUS_DONE 1
# define STATUS_SUSPENDED 2
# define STATUS_CONTINUED 3
# define STATUS_TERMINATED 4

# define COMMAND_EXTERNAL 0
# define COMMAND_EXIT 1
# define COMMAND_CD 2
# define COMMAND_JOBS 3
# define COMMAND_FG 4
# define COMMAND_BG 5
# define COMMAND_EXPORT 6
# define COMMAND_UNSET 7
# define COMMAND_SET 8
# define COMMAND_ECHO 9
# define COMMAND_TYPE 10
# define COMMAND_ENV 11
# define COMMAND_ALIAS 12
# define COMMAND_UNALIAS 13
# define COMMAND_TEST 14
# define COMMAND_HASH 15

# define BACK 0
# define FORE 1

typedef	struct				s_ht
{
	char					*value;
	char					*key;
	int						hits;
	struct	s_ht			*next;
}							t_ht;

typedef	struct				s_hash
{
	t_ht					**list;
}							t_hash;

typedef struct	s_env
{
	char			*name;
	char			*environ;
	int				flag;
	struct s_env	*next;
}				t_env;

typedef struct	s_process
{
	char				*command;
	char				**argv;
	pid_t				pid;
	int					type;
	int					status;
	int					input;
	int					output;
	int					errorput;
	char				*signal;
	struct s_process	*next;
}				t_process;

typedef struct	s_job
{
	int				id;
	t_process		*process;
	char			*command;
	pid_t			pgid;
	int				mode;
	int				p_input;
	int				p_output;
	int				p;
}				t_job;

typedef struct	s_shell
{
	t_job	*job[NR_J + 1];
	t_env	*env;
}				t_shell;

typedef struct	s_some_norme
{
	char	c;
	char	count;
	int		b;
	char	*str;
}				t_some_norme;

typedef struct	s_check_fifo
{
	int		put_out;
	char	*fifo;
	int		next;
}				t_fifo;

typedef	struct	s_save
{
	t_fifo		fi;
	t_shell		*shell;
	char		**status_string;
	char		**semicolon;
	char		**and_and;
	char		**or_or;
	char		**the_jobs;
	int			the_status;
	char		*if_exit;
	t_hash		*hashtable;
	
}				t_save;

typedef struct	s_re
{
	int		input;
	int		output;
	char	*redirect;
}				t_re;

t_re		g_re;
t_fifo		g_fi;
t_shell		*g_shell;
char		**g_status_string;
char		**g_semicolon;
char		**g_and_and;
char		**g_or_or;
char		**g_the_jobs;
int			g_the_status;
char		*g_if_exit;
int			g_if_sub;
t_hash		*g_hashtable;

t_job			*make_job(char *line, int mode);

t_env			*create_env(char **environ);
t_env			*create_next(char *environ);

void			trait(char *line, int mode, int count);
void			init_shell();
void			exec_command(t_job **job, t_process **process);
void			remove_job(int id);
void			print_pgid_of_job(int id);
void			set_process_status(int pid, int status);
void			print_job_status(int id);
void			check_zombie(int job_id);
void			print_job_status(int id);
void			set_job_status(int id, int status);
void			execve_help(t_process **process, t_job **job,
				char *command, char *print);
void			help_to_fg(pid_t pid, int id);
void			free_2d(char **str);
void			free_job(t_job *job);
void			help_to_finish_the_pipe(char **line);
void			semicolon_parse(char *line);
void			help_to_exit(t_job *job);
void			make_the_put(t_process **process, t_job **j);
void			pipe_execve(t_process *process, t_job *job);
void			close_pipe(t_process *process, t_job *job);
void			join_with_anything(char **line, int a, int i);
void			join_with_something(char **line, char *str, int a, int i);
void			join_with_anything2(char **line, char *str, int a, int i);
void			mini_mini_norme(char **line, char *str, int a, int i);
void			help_trait(t_job **j, t_process **process, int *count);
void			to_env(t_process *process);
void			back_or_fore(t_job **job, t_process **process);
void			to_type(t_process *process);
void			to_echo(t_process *process);
void			to_set(t_process *process);
void			to_unset(t_process *process, t_job *job);
void			to_export(t_process *process, t_job *job, char **argv);
void			add_pwd(t_process *process, t_job *job, char *str);
void			to_cd(t_process *process, t_job *job);
void			add_pwd(t_process *process, t_job *job, char *str);
int				test_dir(char *argv, t_process *process);
void			print_error_jump_options(char c, int error);
void			norme_to_cd(t_process *process, t_job *job, char **argv, int i);
void			help_setenv(char *command, t_env **list);
void			free_env_list(t_env *env);
void			help_unsetenv(char *command);
void			manage_variables2(t_env *save);
void			help_to_wait(t_job *j, int *status);
void			final_help(t_process **process, t_job **j, int *count);
void			set_signal(pid_t pid, int status);
void			another_help_f_s_q(int *start, int *type);
void			alloc_shell(void);
void			help_wait_for_job(int wait_pid, int status);
void			init_fifo(void);
void    		open_the_file(void);
void			remove_the_file(void);
void			second_loop_sub(char **str);
void			help_execve_help(t_job **job, t_process **process);

char			*help_search_join(char *str, DIR *dir, char **print);
char			**make_2d_table(char *line);
char			**list_to_tab(t_env *env);
char			*ft_filter_quote(char *cont, int c, int *fi, int len);
char			**split_command(char *line, char s);
char			**split_and_and(char *line, char c);
char			**split_job(char *line);
char			*replace_with_env(char *line, t_env *env, int b, int i);
char			*concate(char *path, char *str);
char			*replace_home(char *line, t_env *env);
char			*move_quote(char *line, int i);
char			*move_slash(char *line);
char			*filter_for_file(char *file, t_env *env);
char			*take_file(char **file, int *j);
char			**ls(char *path);
char			*check_env(char *str, t_env *env);
char			**mini_filter_h(char **str, t_env *env);
char			*check_if_exist(char *command, char **env);
char			*search_env(t_env *list);
char			*get_name(char *environ);
char			*get_environ(char *environ);
char			*check(char *str);
char			*search_home(t_env *list);
char			**manage_variables(char **argv, t_env **env);
char			**create_new_argv(char **argv, int i);
char			**help_re_null(t_env *save, t_env **env, char **argv);
char			*replace_by_s_q(char *str, int *start, int *end, int type);
char			*finish_slach(char *str);
int				while_for_q_s(char **str);
char			*to_move_s_q(char **str, char c, int *start, int *end);
char			*help_finish_slach(char *str, int i, char *new);
char			**my_tab_signalmsg(void);
char			*trait_the_parentheses(char *new);
char			*complte_parent_cursh(char *str);
char			*return_the_sub(int fd);
char			*trait_the_parentheses_help(int *a, int i, char *line);
char			*join_the_sub(char *str);
char			*make_sub_happen(char *str, t_process **process);
char			*help_help_bonus(char *line, int *i, int *j);
char			*help_help_split_and_and(char *line, int *i, int *j);
char			*switch_to_alias(char *str);

int				insert_job(t_job *job);
int				wait_for_job(int id, int wait_count);
int				get_command_type(char *command);
int				to_jobs(void);
int				to_fg(t_process *process, t_job *j);
int				to_bg(t_process *process, t_job *j);
int				put_error_not_found(int type);
int				search_last(void);
int				put_error_no_such(int type);
int				put_error_fg(int type);
int				trait_built(t_job *j, t_process *process);
int				print_and_of_number(char s, int count);
int				check_if_and_and(char **str, int i, int j);
int				print_fu_redirect_error(void);
int				some_name(int *i, int *j, char *str, char c);
int				check_cursh(char **str, int i, char c, int f);
int				check_line(char *line);
int				if_numeric(char *str);
int				help_check_if_and_and(char **str, int i);
int				print_error_num(char *file, int error);
int				trait_the_type(char *file, int out, int type,
				t_process **process);
int				redirect(t_process **process, int i);
int				parse_to_two(char *file, int out, int type,
				t_process **process);
int				if_two(int out, int type, t_process **process);
int				if_three(char *file2, int out, int type, t_process **process);
int				if_four(char *file2, int out, int type, t_process **process);
int				help_type_one(char *file, int error);
int				print_p_d(char *file, int pipe);
int				error_type_three(char *file, int error);
int				help_redirect(char *file, char *line);
int				print_n_x(char *file, int pipe);
int				print_i_d(char *file, int pipe);
int				count_replace_env(char *line, int i, char c);
int				h_f_f(char *file2, t_process *process, int ifnot);
int				check_set(char *new);
int				check_if_is_num(char *file);
int				if_numeric_or_percent(char *str);
int				print_exit_error(char *str);
int				check_if_there_slash(char *str, int i);
int				help_c_c_and(char *str, char c, int i);
int				norme_s_q(int i, char *line, char c);
int				jump_for_move_quote(char *line, char c, int i);
int				help_to_norme_type(char *file);
int				check_set_curch(char *str, int end, int start);
int     		to_end_parrentheses(int i, char *line);
int				check_parenthesis(char **line);
int				print_error_parenthesis(char *line, char c, int i);
int				mini_checker_e_parent(char *str, int i);
int				to_the_end_parent(char *str, int i, char c, char a);
int				check_count_and(char *str, int count, int j);
int				jump_cursh_parent(char *str, int i);
int				mini_norme_check_parenthesis(char *line, int i);
int				jump_subshell(char *str, int i);
int				checker_subshell(char *str);
int     		checker_for_anyparent(char *str);
int				checker_for_re_sub(char *str, int i);
int 			jump_re_forsub(char *str, int i);
int				search_no_espace(char *str);
int				check_that_number(char *str, int j, int i);
int				free_and_error(char *tmp);
int				semi_sub(char **str);
int     		final_trait(char *str, t_process **process, t_job **job);
int				help_trait_it_sub(char *str, int i, int j, int *b);
int				half_checker_for_re_sub(char *str, int i);
int				print_error_sub(char *tmp);
int				print_error_one_word(char *str, int i);
int				check_for_end_pipe(char *str, int i, char c, char *tmp);
int				help_trait_v3(t_process **process, t_job **j, int *count, int a);

int				ft_test(char **args);
int				test_file(char **args);
int				block_special(char *pathname);
int				character_special(char *pathname);
int				is_dir(char *pathname);
int				file_exist(char *pathname);
int				ft_setgid(char *pathname);
int				is_symlink(char *pathname);
int				is_fifo(char *pathname);
int				is_file(char *pathname);
int				readable_by_owner(char *pathname);
int				is_socket(char *pathname);
int				file_not_empty(char *pathname);
int				ft_setuid(char *pathname);
int				writeable_by_owner(char *pathname);
int				executable_by_owner(char *pathname);
int				test_string(char **args);
int				ft_equal(char *str1, char *str2);
int				ft_not_equal(char *str1, char *str2);
int				ft_integer_equal(char *s1, char *s2);
int				ft_integer_not_equal(char *s1, char *s2);
int				ft_integer_ge(char *s1, char *s2);
int				ft_integer_lt(char *s1, char *s2);
int				ft_integer_le(char *s1, char *s2);
int				ft_argslen(char **args);
int				ft_is_numeric(char *str);
int				test_file_complete(char **args);
void			error_test(char *str);

t_hash			*ht_create(void);
char			*ft_hashtable(char **args, char **tabs, t_hash **h_table, char **print);
void			ft_hash(char **args, t_hash **h_table);
void			reset_hits(char **args, t_hash **h_table);
void			delete_hashtable(t_hash **h_table, int len);
void			aff_hashtable(t_hash **h_table);
t_ht			*del_list(t_ht **list, int len);
int				hash_function(char *str);
t_ht			*ht_insert(char *str, char **tabs, char **print);
void			l_flag(t_hash **h_table, char **args);
void			del_hash(t_hash **h_table, char **args);
int				delete_list(t_ht *list, t_ht **main_head, char *arg);
void			d_flag(t_hash **h_table, char **args);
void			t_flag(t_hash **h_table, char **args);
void			p_flag(t_hash **h_table, char **args);
void			search_hash(t_hash **h_table, char **args, int len);
t_ht			*hash_p_insert(char *arg, char *path);
void			ft_hash_error(char *str);
void			l_flag_error(char *str);
void			l_flag_print(char *value, char *key);
void			l_flag_mini(char *str, t_ht *current);
void			l_flag_valid(t_hash *hashtable, int slot);
void			p_flag_mini(char **args, t_hash **h_table);
void			p_flag_free(t_ht **h_list, char *str, char *path);
int				free_node(t_ht **list);
void			del_list_mini(t_ht **list, int len);
void			search_hash_mini(t_hash **h_table, char **args);
char			*valid_path(char *cmd_name, char **tabs, char **print);
char			*absolute_path(char *path, char *command);
int				ft_hash_complete(char **print, char **args);
t_ht			*alloc_list(t_ht *list);
t_hash			*alloc_hash(t_hash **h_table);
char			*ft_hash_complete_s(t_hash *hashtable, char **args, char **tabs, char **print);

#endif
