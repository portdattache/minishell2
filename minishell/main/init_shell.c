/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcaumont <bcaumont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 16:37:26 by bcaumont          #+#    #+#             */
/*   Updated: 2025/04/08 11:47:34 by bcaumont         ###   ########.fr       */
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

t_cmd	*create_cmd_node(t_shell *shell, char **args)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->cmds = ft_args_split_dup(args);
	cmd->args = args;
	cmd->path = NULL;
	cmd->pipefd[0] = -1;
	cmd->pipefd[1] = -1;
	cmd->env = shell->env;
	cmd->pid = 0;
	cmd->prev = NULL;
	cmd->next = NULL;
	return (cmd);
}
