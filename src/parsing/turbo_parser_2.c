/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   turbo_parser_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flverge <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 11:47:47 by flverge           #+#    #+#             */
/*   Updated: 2024/02/09 11:33:44 by flverge          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	search_redir_in(t_pars **pars, char **splited, char **cleaned)
{
	int i;

	i = 0;
	while (splited[i])
	{
		if (!ft_strncmp(cleaned[i], RED_IN, 2) && !ft_strncmp(cleaned[i], splited[i], 2))
		{
			(*pars)->isRedirIn = true;
			break ;	
		} 
		else if (!ft_strncmp(cleaned[i], RED_IN_DELIM, 3) && !ft_strncmp(cleaned[i], splited[i], 3))
		{
			(*pars)->isRedirIn = true;
			break ;
		}
		i++;
	}
}

bool	testing_builtin(char *cleaned)
{
	if (!ft_strcmp(cleaned, "echo"))
		return (true);
	else if (!ft_strcmp(cleaned, "cd"))
		return (true);
	else if (!ft_strcmp(cleaned, "pwd"))
		return (true);
	else if (!ft_strcmp(cleaned, "export"))
		return (true);
	else if (!ft_strcmp(cleaned, "unset"))
		return (true);
	else if (!ft_strcmp(cleaned, "env"))
		return (true);
	else if (!ft_strcmp(cleaned, "exit"))
		return (true);
	return (false);
}

bool	is_token_command(char *splited, char *cleaned, char **paths)
{
	int j; // paths index

	j = 0;
	char *supposed_command;
	
	supposed_command = NULL;
	// ! IMPORTANT : builtin needs to be tested first
	// ! because access will trow a false positive on builtin commands anyway
	// testing builtin presence first, for avoiding access 
	if (testing_builtin(cleaned))
	{
		printf("Command is a builtin\n");
		return true;
	}
		
	// testing paths for regular commands with access
	while (paths[j])
	{
		supposed_command = ft_strjoin(paths[j], cleaned);
		if (!access(supposed_command, F_OK))
		{
			free(supposed_command);
			return true;
		}
		j++;
		free(supposed_command);
	}
	return false;
}

void	new_node_command(t_pars **pars, char **splited, char **cleaned, int *i)
{
	// ! Allocate a new node;
	t_pars	*new_node;
	t_command *new_node_command;

	new_node = (t_pars *)malloc(sizeof(t_pars));
	if (!new_node)
		return (NULL);
	new_node_command = (t_command *)malloc(sizeof(t_command));
	if (!new_node_command)
		return (NULL);
	
	// -------------------global init node--------------------

	// ! STEP 1 : init bools switches
	new_node->isCommand = true;
	new_node->isFile = false;
	new_node->isOperator = false;

	// ! STEP 2 :connecting the t_command node
	new_node->cmd = new_node_command;
	
	// ! STEP 3 : NULL init other substructures nodes
	new_node->fl = NULL;
	new_node->operator = NULL;

	// ! STEP 4 : init prev and next both to NULL
	new_node->prev = NULL;
	new_node->next = NULL;
	// -------------------global init node--------------------
	
	
	// -------------------init substructure--------------------
	
	// ! STEP 1 :  init name of command
	new_node->cmd->command_name = cleaned[*i];
	
	// ! STEP 2 : is command builtin ??
	if (testing_builtin(cleaned[*i]))
	{
		new_node->cmd->isBuiltin = true;
		new_node->cmd->command_path = NULL;
	}
	else
		new_node->cmd->isBuiltin = false;

	
	// -------------------init substructure--------------------
	
	
}

bool	is_token_file(char *splited, char *cleaned)
{
	
}

void	new_node_file(t_pars **pars, char *splited, char *cleaned)
{
	
}

bool	is_token_operator(char *splited, char *cleaned)
{
	
	
}

void	new_node_operator(t_pars **pars, char *splited, char *cleaned)
{
	
}

void	pars_alloc(t_pars **pars, char **splited, char **cleaned, char **paths)
{
	int i; // index of both split and cleaned

	i = 0;
	
	// ! step 1 : detect redir in operator, matching splited and cleaned
	search_redir_in(pars, splited, cleaned);


	// ! allocate the struct whatsoever
	while (cleaned[i]) // iterate over all tokens	
	{
		if (is_token_command(splited[i], cleaned[i], paths))
			new_node_command(pars, splited, cleaned, &i);
		else if (is_token_file(splited[i], cleaned[i]))
			new_node_file(pars, splited[i], cleaned[i]);
		else if (is_token_operator(splited[i], cleaned[i]))
			new_node_operator(pars, splited[i], cleaned[i]);
		// ! maybe another edge case ???
		i++;
	}
	
	// ! print the whole struct
}