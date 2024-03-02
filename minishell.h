/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flverge <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 12:04:35 by glambrig          #+#    #+#             */
/*   Updated: 2024/03/02 10:48:01 by flverge          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# define _GNU_SOURCE

# include "lft/libft.h"
# include <unistd.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <string.h>
# include <stdbool.h>
# include <fcntl.h>
# include <signal.h>
# include <termios.h>
# include <dirent.h>
# include <errno.h>
# include <curses.h>
# include <term.h>
# include <termcap.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/ioctl.h>

# define S_QUOTE '\'' 
# define D_QUOTE '\"'
# define PIPE "|"
# define RED_IN "<"
# define RED_IN_DELIM "<<"
# define RED_OUT ">"
# define RED_OUT_APP ">>"
# define DOLL_ENV '$'
# define EMPTY_EXIT_LIST -999

// --------------------- Parsing ---------------------------------

// Parsing structure
typedef struct s_pars
{
	struct s_command	*cmd;
	struct s_operator	*operator;
	struct s_file		*fl;
	struct s_pars		*prev;
	struct s_pars		*next;
	bool				masterkill;
	bool				is_redir_in;
	int					error_message;
	int					last_exit_status;
	bool				is_command;
	bool				is_file;
	bool				is_operator;
	bool				is_here_doc;
	char				*here_doc;
}						t_pars;

// Sub_node for command
typedef struct s_command
{
	bool	is_builtin;
	char	*command_name;
	char	*command_path;
	char	**name_options_args;
}			t_command;

// Sub_node for file
typedef struct s_file
{
	char	*file_name;
	bool	file_exist;
	bool	auth_r;
	bool	auth_w;
	bool	auth_x;
}	t_file;

// Sub_node for operator
typedef struct s_operator
{
	bool	pipe;
	bool	redir_in;
	bool	redir_in_delim;
	bool	redir_out;
	bool	redir_out_app;
}			t_operator;

// Utils for parsing
typedef struct s_utils
{
	char	**result;
	int		i;
	int		j;
	int		k;
	char	starting_quote;
	char	end_quote;
	int		real_len;
	bool	expansion;
}	t_utils;

// Utils for parsing
typedef struct s_alloc
{
	char	**splitted_prompt;
	char	**cleaned_prompt;
	char	**paths;
}	t_alloc;

// Utils for parsing
typedef struct s_split_utils
{
	size_t	result;
	size_t	j;
	int		start_quote;
	int		end_quote;
	int		i;
	int		start;
}	t_split_utils;

// ENV structure
typedef struct s_env_list
{
	struct s_env_list	*next;
	char				*original_envp;
	char				*key;
	char				*value;
}	t_env_list;

// bools_parsing
bool	is_token_opr(char *splited, char *cleaned);
bool	is_token_redir_delim(char *cleaned);
bool	is_token_pipe(char *splited, char *cleaned);
bool	is_token_redir_out(char *splited, char *cleaned);
bool	is_last_node_operator(t_pars **pars);
bool	is_last_node_redir(t_pars **pars);
bool	is_last_node_r_in_delim(t_pars **pars);
bool	is_last_node_here_doc(t_pars **pars);
bool	is_last_node_cmd(t_pars **pars);
bool	is_last_node_file(t_pars **pars);
bool	is_last_node_redir(t_pars **pars);
bool	is_last_node_r_in_delim(t_pars **pars);
bool	is_last_node_here_doc(t_pars **pars);
bool	is_last_node_cmd(t_pars **pars);
bool	is_last_node_file(t_pars **pars);

// custom_splits
char	**path_split(char const *s, char c);
char	**ft_2_split(char const *s, char c);

// new_nodes
void	new_node_command(t_pars **pars, t_alloc **utils, int *i);
void	new_node_file(t_pars **pars, char *cleaned);
void	new_node_here_doc(t_pars **pars, char *cleaned);
void	new_node_operator(t_pars **pars, char *cleaned);

// splitted_prompt
void	allocation(char **buffer, char *str, size_t len_s);
void	alloc_pars(char *str, t_split_utils *u);
void	loop_sub_quote(char *str, t_split_utils *u);
void	part_1(char *str, int *i, size_t *result);
void	part_2(int *start_quote, int *end_quote, char *str, int *i);
void	part_3(char *str, int *i, size_t *result);
size_t	parsing_countwords(char *str);
char	**parsing_split(char *s);

// utils_parsing
t_utils	*utils_init_struct(int len);
t_pars	*init_1st_node_pars(void);
t_pars	*lstfirst(t_pars *lst);
t_pars	*lstnew(int exit_status);
t_pars	*lstlast(t_pars *lst);
void	lstadd_back(t_pars **lst, t_pars *new);
void	lstadd_front(t_pars **lst, t_pars *new);
int		lstsize(t_pars *lst);
bool	is_any_quote(char c);
bool	is_operator_char(char c);
bool	is_buff_part_1(char *starting_quote, int *i, char *str);
bool	is_buff_valid_doll(char *str);
bool	alloc_part_1(t_alloc *c, int *i, t_pars **pars, t_alloc **u_alloc);
bool	alloc_part_2(t_alloc *cur, int *i, t_pars **pars);
bool	alloc_part_3(t_alloc *cur, int *i, t_pars **pars);
bool	alloc_part_4(t_alloc *cur, int *i, t_pars **pars);
bool	alloc_part_5(t_alloc *cur, int *i, t_pars **pars, t_alloc **u_alloc);
void	calculate_len_doll(char *b, t_utils **u, t_env_list **env, t_pars **p);
char	**clean_prompt(char **b, t_utils **ut, t_env_list **env, t_pars **p);
void	copying_doll(char *bu, t_utils **u, t_env_list **s_env, t_pars **pars);
void	parsing_doll_var(t_utils **ut, char *b, t_env_list **env, t_pars **pa);
void	pars_alloc(t_pars **pars, t_alloc **u_alloc);
void	turbo_parser(char *p, t_pars **pars, t_env_list **env, t_utils **s_u);

// ------------- UTILS ---------------------------------

// 2common_utils.c
int	check_next_operator(t_pars *lst);
t_all	*init_t_all_struct(char **envp);
void	reset_t_pars(t_pars **pars);
char	**convert_env_list_to_array(t_env_list **list);
void	refresh_envp(t_all **all);

// 2free_functions.c
void	free_split(char **to_free);
void	free_s_env(t_env_list **env);
void	free_s_utils(t_utils **utils);
void	free_firstnode_pars(t_pars **pars);
void	free_t_alloc(t_alloc *alloc);



// ------------- EXECUTION ---------------------------------

typedef struct s_all
{
	char	**copy_envp;
	t_env_list	*env_lst;
	char		*readline_line;
}	t_all;


typedef struct s_exit_status_list
{
	int							status;
	struct s_exit_status_list	*next;
}	t_exit_status_list;

/*Norm struct*/
typedef struct s_pipe
{
	int	in_fd;
	int	i;
	int	**fds;
	pid_t	*ch_pid;
} t_pipe;

typedef struct s_hrdoc
{
	int		open_fd;
	pid_t	ch_pid;
	char	*rl_buff;
}	t_hrdoc;

/*Env*/
void	copy_env_into_list(t_env_list **env, char **envp);

/*Builtins*/
void	free_tokens(char **t);
int		ft_echo(char **args, t_pars *pars);//char *s, t_all *all, 
void	ft_cd(t_pars **pars, t_env_list **envp);
void	ft_pwd(char **name_args, t_pars **pars);
void	ft_export(t_env_list **envp, char **args, t_all *all, t_pars **pars);
void	ft_unset(t_env_list **envp, char **name_args, t_pars **parsing);
void	ft_env(char **args, t_all *all, t_pars **pars);
void	ft_exit(char **name_option, t_all *all, t_pars **pars);



/*Signal handler*/
int		signals(t_pars *all);

/*Pipes, redirections*/

int		check_next_operator(t_pars *lst);
void	exec_builtin(t_pars *pars, t_all *all, int pid);
int		pipes(t_pars **lst, t_all *all, int fd_stdin);
int		pipes_child_func(t_pars **lst, t_all *all, int input_fd, t_pipe pippy);
int		pipes_helper_1(t_pars **lst, t_all *all, int input_fd);
void	pipes_helper_2(t_pars **lst, t_all *all, t_pipe pippy, int ifd);
int		pipes_helper_3(t_pars **lst, t_all *all);
int		redirect_input_delimitor(t_pars **lst, t_all *all);
void	heredoc_helper_1(t_hrdoc *doc);
void	set_temp_perms(t_pars **lst);
void	handle_eof_edgecase(t_pars **lst, char **rl_buff);
void	heredoc_helper_2(t_pars **lst, t_all *all, char **rl, int open_fd);
int		redirect_input(t_pars **lst, t_all *all);
int		redirect_output(t_pars **lst, t_all *all, int input_fd);

/*Utils*/
size_t	size_of_ptr_ptr(void **arr);
void	free_arr(void **array, int size);
void	free_t_pars(t_pars **lst);
size_t	lstlen(t_pars *lst);
void	fork_error(int **fds, pid_t **ch_pid);
size_t	num_of_pipes(t_pars *lst);
int		num_of_out_redirs(t_pars *lst);
void	del_t_pars_node(t_pars *lst);

/*Main helpers*/
void	check_ops(t_pars **pars, t_all *all, int *k);
void	main_init(t_all **all, t_pars **pars, t_utils **u, char **envp);
void	check_ctrl_d(t_all *all, t_pars *pars);
void	masterkill_false(t_pars *pars, t_all *all, int *k);
int		exec_external_func(t_pars *lst, t_all *all);
void	exec_builtin(t_pars *pars, t_all *all, int pid);

/*Flo, but i don't want to touch his part of this .h*/
t_pars	*init_1st_node_pars(void);
void	free_firstnode_pars(t_pars **pars);
t_all	*init_t_all_struct(char **envp);
void	reset_t_pars(t_pars **pars);
char	**convert_env_list_to_array(t_env_list **list);
void	refresh_envp(t_all **all);

void	free_all(t_all **all);

#endif
