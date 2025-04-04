/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_add.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: broboeuf <broboeuf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 18:49:57 by broboeuf          #+#    #+#             */
/*   Updated: 2025/04/04 16:43:00 by broboeuf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_token	*token_new(t_token_type type, char *value)
{
	t_token	*new;

	if (!value || value[0] == '\0')
		return (NULL);
	new = malloc(sizeof(t_token));
	if (!new)
		return (NULL);
	new->value = value;
	new->type = type;
	new->prev = NULL;
	new->next = NULL;
	return (new);
}

int	token_add(t_token **token_list, char *value, t_token_type type)
{
	t_token	*new;
	t_token	*last;

	new = token_new(type, value);
	if (!new)
		return (0);
	if (!*token_list)
	{
		*token_list = new;
		return (1);
	}
	last = *token_list;
	while (last->next)
		last = last->next;
	last->next = new;
	new->prev = last;
	return (1);
}

int	append_token(t_token **list, char *str, t_token_type type)
{
	t_token	*new;
	t_token	*tmp;

	if (!list)
		return (0);
	new = token_new(type, str);
	if (!new)
		return (0);
	if (!(*list))
		*list = new;
	else
	{
		tmp = *list;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
		new->prev = tmp;
	}
	return (1);
}
