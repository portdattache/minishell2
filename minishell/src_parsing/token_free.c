/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: broboeuf <broboeuf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 11:13:23 by broboeuf          #+#    #+#             */
/*   Updated: 2025/04/04 16:42:54 by broboeuf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	token_del(t_token **token)
{
	if (!token || !*token)
		return ;
	if ((*token)->value)
	{
		free((*token)->value);
		(*token)->value = NULL;
	}
	free(*token);
	*token = NULL;
}

void	tokens_free(t_token **token_list)
{
	t_token	*current;
	t_token	*next;

	if (!token_list || !*token_list)
		return ;
	current = *token_list;
	while (current)
	{
		next = current->next;
		free(current->value);
		free(current);
		if (next == *token_list)
			break ;
		current = next;
	}
	*token_list = NULL;
}
