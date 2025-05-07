/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_files.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: broboeuf <broboeuf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 15:04:07 by broboeuf          #+#    #+#             */
/*   Updated: 2025/05/07 20:06:28 by broboeuf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	opening(t_data *data, char *filename, t_TokenType type)
{
	int	fd;

	fd = -1;
	if (!filename)
		return (perror("Minishell: null filename"), -1);
	if (type == REDIRECTION_IN)
		fd = open(filename, O_RDONLY);
	else if (type == HEREDOC)
		fd = handle_heredoc(data, filename);
	else if (type == REDIRECTION_OUT)
		fd = open(filename, O_CREAT | O_WRONLY | O_TRUNC, 0777);
	else if (type == APPEND)
		fd = open(filename, O_CREAT | O_WRONLY | O_APPEND, 0777);
	if (fd < 0)
		perror(filename);
	return (fd);
}

bool	redir_in(t_cmd *cmd, t_token *token, t_data *data)
{
	if (!token->next || token->next->type != WORD)
	{
		perror("Minishell: syntax error");
		return (false);
	}
	cmd->infile = opening(data, token->next->value, token->type);
	if (cmd->infile < 0)
		return (false);
	if (token->type == HEREDOC)
		cmd->heredoc = 1;
	return (true);
}

bool	all_redir_in(t_cmd *cmd, t_token *start, t_data *data)
{
	t_token	*token;

	token = start;
	while (token && token->type != PIPE)
	{
		if (token->type == REDIRECTION_IN || token->type == HEREDOC)
		{
			if (!redir_in(cmd, token, data))
				return (false);
		}
		token = token->next;
	}
	return (true);
}

bool	redir_out(t_cmd *cmd, t_token *token, t_data *data)
{
	int	fd;

	if (!token->next || token->next->type != WORD)
	{
		perror("Minishell: syntax error");
		return (false);
	}
	if (cmd->outfile >= 0)
		close(cmd->outfile);
	fd = opening(data, token->next->value, token->type);
	if (fd == -1)
		return (false);
	cmd->outfile = fd;
	return (true);
}

bool	all_redir_out(t_cmd *cmd, t_token *start, t_data *data)
{
	t_token	*token;

	token = start;
	while (token && token->type != PIPE)
	{
		if (token->type == REDIRECTION_OUT || token->type == APPEND)
		{
			if (!redir_out(cmd, token, data))
				return (false);
		}
		token = token->next;
	}
	return (true);
}
