/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_param.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: broboeuf <broboeuf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 18:23:08 by broboeuf          #+#    #+#             */
/*   Updated: 2025/05/07 20:06:23 by broboeuf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

bool	is_valid_argument(t_token *token)
{
	return (token->type == WORD);
}

int	count_arguments(t_data *data, t_token *token)
{
	int		count;
	t_token	*current;

	(void)data;
	count = 0;
	current = token;
	while (current && current->type != PIPE)
	{
		if (current->type == WORD)
			count++;
		current = current->next;
	}
	return (count);
}

char	**parse_command_arguments(t_data *data, t_token *token)
{
	char	**args;
	int		arg_count;
	int		i;
	t_token	*current;

	i = 0;
	current = token;
	arg_count = count_arguments(data, token);
	args = malloc(sizeof(char *) * (arg_count + 1));
	if (!args)
		return (NULL);
	while (current && current->type != PIPE)
	{
		if (current->type == WORD && !add_argument(&args, &i, current->value))
			return (cleanup_arguments(args, i), NULL);
		current = current->next;
	}
	args[i] = NULL;
	return (args);
}

bool	create_command_list(t_data *data)
{
	t_token	*current;

	current = data->token;
	while (current)
	{
		if (!process_token(data, &current))
			return (false);
		current = current->next;
	}
	return (true);
}
