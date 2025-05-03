/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: broboeuf <broboeuf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 12:14:31 by broboeuf          #+#    #+#             */
/*   Updated: 2025/04/29 14:40:34 by broboeuf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execution(t_data *data)
{
	t_exec	ex;

	init_execution(&ex, data);
	while (true)
	{
		setup_pipes(&ex);
		ex.cmd->pid = fork();
		if (ex.cmd->pid < 0)
			free_all(data, ERR_FORK, EXT_FORK);
		else if (ex.cmd->pid == 0)
			child_process(data, ex.cmd, ex.pipefd);
		else
			parent_cleanup(&ex);
		if (ex.is_last)
			break ;
		ex.is_first = false;
		ex.cmd = ex.cmd->next;
		ex.is_last = (ex.cmd->next == data->cmd);
	}
	wait_children(data);
}

static void	init_execution(t_exec *ex, t_data *data)
{
	ex->data = data;
	ex->cmd = data->cmd;
	ex->prev_pipe = -1;
	ex->is_first = true;
	ex->is_last = (data->cmd->next == data->cmd);
}

static void	setup_pipes(t_exec *ex)
{
	if (ex->is_last)
		return ;
	if (pipe(ex->pipefd) == -1)
		free_all(ex->data, ERR_PIPE, EXT_PIPE);
}