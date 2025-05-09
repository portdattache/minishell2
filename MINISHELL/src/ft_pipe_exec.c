/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe_exec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcaumont <bcaumont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 11:23:56 by bcaumont          #+#    #+#             */
/*   Updated: 2025/05/09 12:07:40 by bcaumont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	exec_pipeline(t_cmd *cmd_list)
{
	t_cmd	*curr;

	curr = cmd_list;
	while (curr)
	{
		if (curr->next && pipe(curr->pipefd) == -1)
			return (perror("pipe"), 1);
		curr->pid = fork();
		if (curr->pid == -1)
			return (perror("fork"), 1);
		if (curr->pid == 0)
			exec_child(curr);
		close_parent_pipes(curr);
		curr = curr->next;
	}
	return (wait_all(cmd_list));
}

void	exec_child(t_cmd *cmd)
{
	char	**envp;

	envp = env_to_envp(cmd->env);
	if (cmd->prev && dup2(cmd->prev->pipefd[0], 0) == -1)
		exit(1);
	if (cmd->next && dup2(cmd->pipefd[1], 1) == -1)
		exit(1);
	if (cmd->prev)
		close(cmd->prev->pipefd[0]);
	if (cmd->next)
	{
		close(cmd->pipefd[0]);
		close(cmd->pipefd[1]);
	}
	else if (cmd->pipefd[0] != -1)
		close(cmd->pipefd[0]);
	if (execve(cmd->path, cmd->cmds, envp) == -1)
	{
		perror("execve");
		free_split(envp);
		free_cmd(cmd);
		exit(127);
	}
}

void	close_parent_pipes(t_cmd *cmd)
{
	if (cmd->prev && cmd->prev->pipefd[0] != -1)
		close(cmd->prev->pipefd[0]);
	if (cmd->pipefd[1] != -1)
		close(cmd->pipefd[1]);
}

int	wait_all(t_cmd *cmd)
{
	int		status;
	int		exit_code;
	t_cmd	*tmp;

	exit_code = 0;
	status = 0;
	tmp = cmd;
	while (tmp)
	{
		if (waitpid(tmp->pid, &status, 0) == -1)
		{
			perror("waitpid");
			g_status = 1;
			tmp = tmp->next;
			continue ;
		}
		if (WIFEXITED(status))
			exit_code = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			exit_code = 128 + WTERMSIG(status);
		tmp = tmp->next;
	}
	g_status = exit_code;
	return (exit_code);
}
