/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glambrig <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/28 07:26:07 by flverge           #+#    #+#             */
/*   Updated: 2024/02/13 16:33:01 by glambrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	free_firstnode_pars(t_pars **pars)
{
	free(*pars);
}

t_pars	*init_1st_node_pars(void)
{
	t_pars	*new;

	new = (t_pars *)malloc(sizeof(t_pars));
	if (!new)
		return (NULL);
	new->last_exit_status = 0;
	new->cmd = NULL;
	new->fl = NULL;
	new->operator = NULL;
	new->prev = NULL;
	new->next = NULL;
	return (new);
}

// int main(int ac, char **av, char **envp)//, char **env
// {
// 	(void)ac;
// 	(void)av;
// 	t_env_list	*s_env;
// 	t_utils		*utils;
// 	t_pars		*pars;

// 	char *line;

// 	s_env = NULL;
// 	utils = NULL;
// 	pars = NULL;
	
// 	copy_env_into_list(&s_env, envp);

// 	line = readline("minishell$ ");


// 	// ! init the first node
// 	if (!pars)
// 		pars = init_1st_node_pars();
	
// 	turbo_parser(line, &pars, &s_env, &utils);

// 	// ! execution function
// 	// execution(&pars, &s_env, s)
	
// 	free_s_env(&s_env);

// 	// ! need to differienciate freeing the first node from the whole list 
// 	free_firstnode_pars(&pars);
	
	
// 	free(line);

// }