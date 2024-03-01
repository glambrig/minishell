/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2common_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glambrig <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 16:46:42 by glambrig          #+#    #+#             */
/*   Updated: 2024/03/01 16:49:18 by glambrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/*
	Returns:
	1 for pipe
	2 for redir in
	3 for heredoc
	4 for redir out or redir out append
	0 for no operators
*/
int	check_next_operator(t_pars *lst)
{
	t_pars	*temp;

	temp = lst;
	while (lst)
	{
		if (lst->isOperator == true)
		{
			if (lst->operator->pipe == true)
				return (1);
			if (lst->operator->redir_in == true)
				return (2);
			if (lst->operator->redir_in_delim == true)
				return (3);
			if (lst->operator->redir_out == true || lst->operator->redir_out_app == true)
				return (4);
		}
		lst = lst->next;
	}
	lst = temp;
	return (0);
}

t_all	*init_t_all_struct(char **envp)
{
	t_all		*new_all;

	// allocate two nodes for t_all and t_env_list
	new_all = malloc(sizeof(t_all));
	if (!new_all)
		return (NULL);
	
	// Init sub_node to null
	new_all->env_lst = NULL;
	
	// init readline buffer to null
	new_all->readline_line = NULL;

	// init env_list nodes from envp
	copy_env_into_list(&new_all->env_lst, envp);

	new_all->copy_envp = NULL; // ! NEW ALLOCATED STUFF
	
	return (new_all);
}

void	reset_t_pars(t_pars **pars)
{
	(*pars)->MasterKill = false;
	(*pars)->isRedirIn = false;
	(*pars)->error_message = 0;	
}

char	**convert_env_list_to_array(t_env_list **list)
{
	t_env_list	*current;
	char		**result;
	int			size;
	int			j; // buffer index

	current = *list;
	size = 0;
	j = 0;
	while (current)
	{
		size++;
		current = current->next;
	}
	current = *list;
	result = ft_calloc(size + 1, sizeof(char *));
	while (current)
	{
		result[j] = ft_strdup(current->original_envp);
		current = current->next;
		j++;
	}
	return (result);
}

void	refresh_envp(t_all **all)
{
	t_all *current;

	current = *all;
	
	free_split(current->copy_envp);
	current->copy_envp = convert_env_list_to_array(&current->env_lst);
}
