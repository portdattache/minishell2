/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe_args.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcaumont <bcaumont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 11:31:09 by bcaumont          #+#    #+#             */
/*   Updated: 2025/05/09 11:36:18 by bcaumont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	count_args(t_token *token)
{
	int	count;

	count = 0;
	while (token && token->type != PIPE)
	{
		if (token->type == WORD)
			count++;
		token = token->next;
	}
	return (count);
}

static char	**alloc_args_array(int count)
{
	char	**args;

	args = malloc(sizeof(char *) * (count + 1));
	if (!args)
	{
		g_status = 1;
		return (NULL);
	}
	return (args);
}

static int	fill_args_array(char **args, t_token **token)
{
	int	i;

	i = 0;
	while (*token && (*token)->type != PIPE)
	{
		if ((*token)->type == WORD)
		{
			args[i] = ft_strdup((*token)->value);
			if (!args[i])
			{
				g_status = 1;
				return (-1);
			}
			i++;
		}
		*token = (*token)->next;
	}
	args[i] = NULL;
	return (0);
}

char	**collect_args_until_pipe(t_token **token)
{
	char	**args;
	int		count;

	count = count_args(*token);
	args = alloc_args_array(count);
	if (!args)
		return (NULL);
	if (fill_args_array(args, token) == -1)
		return (args);
	return (args);
}
