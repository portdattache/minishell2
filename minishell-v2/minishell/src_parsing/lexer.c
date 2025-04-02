/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: broboeuf <broboeuf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 10:46:24 by broboeuf          #+#    #+#             */
/*   Updated: 2025/04/02 11:13:05 by broboeuf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_token_type	is_token(char *str)
{
	if (ft_strcmp(str, "|") == 0)
		return (PIPE);
	if (ft_strcmp(str, "||") == 0)
		return (OR);
	if (ft_strcmp(str, "&&") == 0)
		return (AND);
	if (ft_strcmp(str, "<") == 0)
		return (DIR_IN);
	if (ft_strcmp(str, ">") == 0)
		return (DIR_OUT);
	if (ft_strcmp(str, "<<") == 0)
		return (DIR_HEREDOC);
	if (ft_strcmp(str, ">>") == 0)
		return (DIR_OUT_APPEND);
	if (ft_strcmp(str, "$") == 0)
		return (ENV_VAR);
	if (ft_strcmp(str, "#") == 0)
		return (COMMENT);
	if (str[0] == '\'' || str[0] == '\"')
		return (STRING);
	return (WORD);
}