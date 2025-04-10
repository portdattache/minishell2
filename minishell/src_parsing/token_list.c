/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: broboeuf <broboeuf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 18:49:57 by broboeuf          #+#    #+#             */
/*   Updated: 2025/04/04 16:42:51 by broboeuf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

bool	create_list_token(t_token **begin, char *cmd)
{
	*begin = NULL;
	while (*cmd)
	{
		skip_spaces(&cmd);
		if (*cmd && !is_special(cmd) && !add_cmd(begin, &cmd))
			return (free_and_return_false(begin));
		if (*cmd && is_special(cmd) && !add_special(begin, &cmd))
			return (free_and_return_false(begin));
	}
	return (true);
}

size_t	token_list(t_token *first)
{
	size_t	count;
	t_token	*current;

	count = 0;
	if (!first)
		return (0);
	current = first;
	while (current != first || count == 0)
	{
		count++;
		current = current->next;
	}
	return (count);
}

t_token	*token_last(t_token *head)
{
	if (!head)
		return (NULL);
	return (head->prev);
}

void	token_add_front(t_token **first, t_token *new_token)
{
	if (!first || !new_token)
		return ;
	if (!*first)
	{
		*first = new_token;
		return ;
	}
	new_token->next = *first;
	(*first)->prev = new_token;
	*first = new_token;
}
