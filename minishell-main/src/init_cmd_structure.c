/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cmd_structure.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcaumont <bcaumont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 11:22:12 by bcaumont          #+#    #+#             */
/*   Updated: 2025/05/09 11:25:41 by bcaumont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_cmd	*build_cmd_list(t_token *token, t_env *env)
{
	t_cmd	*head;
	t_cmd	*curr;
	char	**args;

	head = NULL;
	curr = NULL;
	while (token)
	{
		args = collect_args_until_pipe(&token);
		if (!args)
			break ;
		curr = cmd_new(args, env);
		add_cmd_back(&head, curr);
		if (token && token->type == PIPE)
			token = token->next;
	}
	return (head);
}

t_cmd	*cmd_new(char **args, t_env *env)
{
	t_cmd	*cmd;
	char	**envp;

	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
	{
		g_status = 1;
		return (NULL);
	}
	init_cmd(cmd, args);
	envp = env_to_envp(env);
	cmd->path = find_cmd_path(args[0], envp);
	free_split(envp);
	if (!cmd->path)
	{
		g_status = 127;
		return (cmd);
	}
	cmd->env = env;
	return (cmd);
}

void	init_cmd(t_cmd *cmd, char **args)
{
	cmd->cmds = args;
	cmd->args = args;
	cmd->infile = NULL;
	cmd->outfile = NULL;
	cmd->pid = -1;
	cmd->next = NULL;
	cmd->prev = NULL;
	cmd->pipefd[0] = -1;
	cmd->pipefd[1] = -1;
}

void	add_cmd_back(t_cmd **head, t_cmd *new)
{
	t_cmd	*tmp;

	if (!*head)
	{
		*head = new;
		return ;
	}
	tmp = *head;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
	new->prev = tmp;
}
