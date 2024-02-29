/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flverge <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 11:57:43 by flverge           #+#    #+#             */
/*   Updated: 2024/02/29 18:52:35 by flverge          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

bool	is_any_quote(char c)
{
	if (c == S_QUOTE || c == D_QUOTE)
		return (true);
	return (false);
}

bool	is_operator_char(char c)
{
	if (c == '<' || c == '>' || c == '|')
		return (true);
	return (false);
}
