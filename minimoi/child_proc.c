/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_proc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: broboeuf <broboeuf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 12:19:28 by broboeuf          #+#    #+#             */
/*   Updated: 2025/04/29 15:48:58 by broboeuf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	child_process(t_data *data, t_cmd *cmd, int *pipefd)
{
	if (cmd->skip_cmd)
		handle_skip_cmd(data);
	if (is_builtin(cmd->cmd_param[0]))
		handle_builtin(data, cmd, pipefd);
	else
		exec_ext(data, cmd, pipefd);
	free_all(data, NULL, data->exit_code);
}

static void	handle_skip_cmd(t_data *data)
{
	data->exit_code = 1;
	free_all(data, NULL, data->exit_code);
}

static void	handle_builtin(t_data *data, t_cmd *cmd, int *pipefd)
{
	redir_builtin(cmd, pipefd);
	launch_builtin(data, cmd);
	free_all(data, NULL, data->exit_code);
}

void	redir_builtin(t_cmd *cmd, int *pipefd)
{
	close(pipefd[0]);
	if (cmd->outfile == -1 && cmd->next != NULL)
		cmd->outfile = pipefd[1];
	else
		close(pipefd[1]);
}