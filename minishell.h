/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flverge <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 12:04:35 by glambrig          #+#    #+#             */
/*   Updated: 2024/02/01 13:14:35 by flverge          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "lft/libft.h" // libft george
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <stdbool.h> // library for handling bool
# include <fcntl.h>
# include <signal.h>
# include <termios.h>
# include <dirent.h>
# include <curses.h>
# include <term.h>
# include <termcap.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/ioctl.h>

# define S_QUOTE '\'' // backslack for making it a char
# define D_QUOTE '\"'
# define PIPE '|'
# define RED_IN '<'
# define RED_IN_DELIM "<<"
# define RED_OUT '>'
# define RED_OUT_APP ">>"
# define DOLL_ENV '$'

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// * .h Florian


// ! Master Struct for parsing
typedef	struct	s_pars
{
	char test; // to delete once the init is okay
	bool command;
	struct s_command *cmd;
	bool file;
	struct s_file *fl;
	bool pipe;
	bool red_in;
	bool red_in_delim;
	bool red_out;
	bool red_out_app;
	struct s_pars *prev;
	struct s_pars *next;
}	t_pars;

// ! Parsing Substructures

typedef	struct	s_command
{
	char *command;
	char *options;
	char *arguments;
	// check execve for how to parse commands, split from pipex ??
}	t_command;

typedef	struct	s_file
{
	char *file_name;
	bool file_exist;
	bool auth_r;
	bool auth_w;
	bool auth_x;
}	t_file;


// ! Functions prototypes

// turbo_parser
void	turbo_parser(char *prompt, t_pars **pars, char **envp);

// utils_parsing
bool	is_whitespace(char c);
bool	is_any_quote(char c);
void	free_split(char **to_free);
char	*ft_strncpy(char *dest, char const *src, size_t n);

// split_parser
char	**parsing_split(char *s);








/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// * .h George


typedef struct s_exit_status_list
{
	int							status;
	struct s_exit_status_list	*next;
}	t_exit_status_list;

typedef struct s_env_list
{
	char *env_line;
	struct s_env_list *next;
}	t_env_list;

void		free_list(t_env_list *lst);
t_env_list	*copy_env_into_list(char **envp);
t_env_list	*insert_node(char *s);

/*Builtins*/
void	free_tokens(char **t);
int		ft_echo(char *s, char **envp, int fd);
int		ft_cd(char *path, t_env_list *envp);
int		ft_pwd(t_env_list *envp, int fd, bool print);
void	ft_export(t_env_list **envp, char *line);
void	ft_unset(t_env_list **envp, char *line);

#endif
