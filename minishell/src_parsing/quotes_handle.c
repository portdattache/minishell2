/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_handle.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: broboeuf <broboeuf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 16:27:42 by broboeuf          #+#    #+#             */
/*   Updated: 2025/04/04 16:43:04 by broboeuf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	handle_quotes(char *cmd, int *i, int *quotes)
{
	char	quote;

	quote = cmd[*i];
	(*quotes)++;
	(*i)++;
	while (cmd[*i] && cmd[*i] != quote)
		(*i)++;
	if (cmd[*i] == quote)
		(*i)++;
	return (*i);
}

int	get_token_length(char *cmd, int *quotes)
{
	int	i;

	i = 0;
	*quotes = 0;
	while (cmd[i]
		&& !is_space(cmd[i])
		&& !is_special(cmd + i))
	{
		if (cmd[i] == '"' || cmd[i] == '\'')
		{
			handle_quotes(cmd, &i, quotes);
		}
		else
		{
			i++;
		}
	}
	return (i);
}
