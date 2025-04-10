/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_debug.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: broboeuf <broboeuf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 10:59:29 by broboeuf          #+#    #+#             */
/*   Updated: 2025/04/04 16:42:58 by broboeuf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	token_print_l(t_token *head)
{
	t_token	*current;

	if (!head)
		return ;
	current = head;
	while (current != head)
	{
		printf("Type: %d, [%s]\n", current->type, current->value);
		current = current->next;
	}
	printf("Type: %d, [%s]\n", current->type, current->value);
}

void	token_print_t(t_token_type type)
{
	const char	*type_names[] = {"WORD", "PIPE", "INPUT", "OUTPUT",
		"APPEND", "HEREDOC", "ERROR"};

	if (type >= WORD && type <= ERROR)
		printf("%s\n", type_names[type]);
	else
		printf("UNKNOWN\n");
}
