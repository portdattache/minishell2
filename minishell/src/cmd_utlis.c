/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utlis.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: broboeuf <broboeuf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 18:33:49 by broboeuf          #+#    #+#             */
/*   Updated: 2025/05/07 20:06:24 by broboeuf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

bool	add_argument(char ***cmd_args, int *index, char *value)
{
	(*cmd_args)[*index] = ft_strdup(value);
	if (!(*cmd_args)[*index])
		return (false);
	(*index)++;
	return (true);
}

void	cleanup_arguments(char **args, int count)
{
	while (count-- > 0)
		free(args[count]);
	free(args);
}

bool	process_token(t_data *data, t_token **token)
{
	t_cmd	*cmd;

	cmd = init_new_cmd(data);
	if (!cmd)
		return (false);
	if ((*token)->type == PIPE)
		*token = (*token)->next;
	else
		cmd = get_last_cmd(data->cmd);
	if (!all_redir_in(cmd, *token, data) || !all_redir_out(cmd, *token, data))
		return (false);
	if ((*token)->type == WORD)
	{
		cmd->args = parse_command_arguments(data, *token);
		if (!cmd->args)
			return (false);
	}
	while (*token && (*token)->type != PIPE)
		*token = (*token)->next;
	return (true);
}

t_cmd	*init_new_cmd(t_data *data)
{
	t_cmd	*new_cmd;
	t_cmd	*last;

	new_cmd = ft_calloc(1, sizeof(t_cmd));
	if (!new_cmd)
		return (NULL);
	new_cmd->infile = STDIN_FILENO;
	new_cmd->outfile = STDOUT_FILENO;
	new_cmd->pipefd[0] = -1;
	new_cmd->pipefd[1] = -1;
	if (data->cmd == NULL)
		data->cmd = new_cmd;
	else
	{
		last = get_last_cmd(data->cmd);
		last->next = new_cmd;
		new_cmd->prev = last;
	}
	return (new_cmd);
}

t_cmd	*get_last_cmd(t_cmd *cmd)
{
	if (!cmd)
		return (NULL);
	while (cmd->next)
		cmd = cmd->next;
	return (cmd);
}