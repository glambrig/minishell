/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glambrig <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 13:51:37 by glambrig          #+#    #+#             */
/*   Updated: 2024/01/28 16:21:49 by glambrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_tokens(char **t)
{
	int	i;

	i = 0;
	if (t == NULL)
		return ;
	while (t[i])
	{
		free(t[i]);
		i++;
	}
	free(t);
}

/*
	cd MUST be called with the full line received from readline(),
	otherwise it (probably) won't work.
	This should update the env PWD var (using ft_pwd()).
	
	IMPORTANT: env variables should also work, e.g. cd $HOME
*/
int	ft_cd(char *s, t_env_list *envp)
{
	char 	**tokens;
	char	*homepath;

	tokens = NULL;
	if (ft_strchr(s, ' ') != NULL)
		tokens = ft_split(s, ' ');
	/*cd with no parameters changes to home directory*/
	if ((tokens != NULL && tokens[1] == NULL) || tokens == NULL)
	{
		homepath = ft_strjoin("/home/", getenv("USER"));
		chdir(homepath);
		free(homepath);
		free_tokens(tokens);
		ft_pwd(envp, 1, false);
		return (0);
	}
	else if (tokens != NULL)
	{
		chdir(tokens[1]);
		ft_pwd(envp, 1, false);
	}
	free_tokens(tokens);
	return (0);
}

/*Also changes the env PWD variable to reflect any changes.*/
int	ft_pwd(t_env_list *envp, int fd, bool print)
{
	char		*cwd;
	char		*new_pwd_env;
	t_env_list *temp;

	cwd = NULL;
	cwd = getcwd(cwd, 0);
	if (fd < 0)
		return (free_list(envp), exit(EXIT_FAILURE), 1);
	if (print == true)
	{
		ft_putstr_fd(cwd, fd);
		ft_putchar_fd('\n', fd);	
	}
	new_pwd_env = ft_strjoin("PWD=", cwd);
	temp = envp;
	while (ft_strncmp(envp->env_line, "PWD", 3) != 0)
		envp = envp->next;
	if (envp != NULL)
	{
		free(envp->env_line);
		envp->env_line = new_pwd_env;
	}
	if (cwd != NULL)
		free(cwd);
	envp = temp;
	return (0);
}

/*Displays a list of the environment variables for the
	current terminal session.*/
int	ft_env(t_env_list *envp, int fd)
{
	t_env_list *temp;

	temp = envp;
	if (fd < 0)
	{
		free_list(envp);
		perror("ft_env: fd < 0");
		exit(EXIT_FAILURE);
	}
	while (envp->next)
	{
		ft_putstr_fd(envp->env_line, fd);
		ft_putchar_fd('\n', fd);
		envp = envp->next;
	}
	envp = temp;
	return (0);
}

int main(int ac, char **av, char **envp)//, char **env
{
	(void)ac;
	(void)av;
	char 		*line;
	int			i;
	t_env_list *lst;

	lst = copy_env_into_list(envp);
	i = 0;
	while (i < 5)
	{
		line = readline("minishell$ ");
		if (ft_strncmp(line, "echo", 4) == 0)
			ft_echo(line, envp, 1);	//replace 1 with fd, if appropriate
		else if (ft_strncmp(line, "cd", 2) == 0)
			ft_cd(line, lst);
		else if (ft_strncmp(line, "pwd", 3) == 0)
			ft_pwd(lst, 1, true);	//replace 1 with fd, if appropriate
		else if (ft_strncmp(line, "env", 3) == 0)
			ft_env(lst, 1);
		else if (ft_strncmp(line, "exit", 4) == 0)
			return (free(line), free_list(lst), exit(0), 0);
		add_history(line);
		free(line);
		i++;
	}
	free_list(lst);
	return 0;
}
