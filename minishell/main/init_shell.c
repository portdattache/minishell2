/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcaumont <bcaumont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 16:37:26 by bcaumont          #+#    #+#             */
/*   Updated: 2025/04/04 12:06:59 by bcaumont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	init_shell(t_shell *shell, char **envp)
{
	int	i;

	if (shell->env)
		return ;
	shell->env = NULL;
	shell->cmd = NULL;
	shell->pipex = NULL;
	shell->exit_status = 0;
	i = 0;
	while (envp[i])
	{
		add_env_to_shell(shell, envp[i]);
		i++;
	}
}

void	init_cmd(t_cmd *cmd, t_shell *shell, char **args)
{
	if (!cmd || !args)
		return ;
	cmd->cmds = NULL;
	cmd->args = args;
	cmd->path = NULL;
	cmd->pipefd[0] = -1;
	cmd->pipefd[1] = -1;
	cmd->env = shell->env;
	cmd->pid = 0;
	cmd->prev = NULL;
	cmd->next = NULL;
}

void	cleanup_shell(t_shell *shell)
{
	t_env	*tmp;
	t_env	*next;

	tmp = shell->env;
	while (tmp)
	{
		next = tmp->next;
		if (tmp->key != NULL)
			free(tmp->key);
		if (tmp->value != NULL)
			free(tmp->value);
		if (tmp->var != NULL)
			free(tmp->var);
		free(tmp);
		tmp = next;
	}
	shell->env = NULL;
}
