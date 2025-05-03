/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcaumont <bcaumont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 13:14:43 by bcaumont          #+#    #+#             */
/*   Updated: 2025/05/03 15:40:24 by bcaumont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../octolib/includes/libft.h"

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
	execve(cmd->path, cmd->cmds, env_to_envp(cmd->env));
	perror("execve");
	exit(127);
}

void	close_parent_pipes(t_cmd *cmd)
{
	if (cmd->prev)
		close(cmd->prev->pipefd[0]);
	if (cmd->next)
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

t_cmd	*buil_cmd_list(t_token *token, t_env *env)
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

int	has_pipe(t_token *token)
{
	while (token)
	{
		if (token->type == PIPE)
			return (1);
		token = token->next;
	}
	return (0);
}

char	**collect_args_until_pipe(t_token **token)
{
	char	**args;
	int		count;
	t_token	*tmp;
	int		i;

	count = 0;
	tmp = *token;
	while (tmp && tmp->type != PIPE)
	{
		if (tmp->type == WORD)
			count++;
		tmp = tmp->next;
	}
	args = malloc(sizeof(char *) * (count + 1));
	if (!args)
	{
		g_status = 1;
		return (NULL);
	}
	i = 0;
	while (*token && (*token)->type != PIPE)
	{
		if ((*token)->type == WORD)
		{
			args[i] = ft_strdup((*token)->value);
			if (!args[i++])
			{
				g_status = 1;
				return (args);
			}
		}
		*token = (*token)->next;
	}
	args[i] = NULL;
	return (args);
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
	create_cmd(args);
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

t_cmd	*create_cmd(char **args)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->cmds = args[0];
	cmd->args = args;
	cmd->infile = -1;
	cmd->outfile = -1;
	cmd->pid = -1;
	cmd->next = NULL;
	cmd->prev = NULL;
	cmd->pipefd[0] = -1;
	cmd->pipefd[1] = -1;
	rteurn(cmd);
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

char	**env_to_envp(t_env *env)
{
	char	**envp;
	int		count;
	t_env	*tmp;
	int		i;

	count = 0;
	tmp = env;
	while (tmp)
	{
		count++;
		tmp = tmp->next;
	}
	envp = malloc(sizeof(char *) * (count + 1));
	if (!envp)
	{
		g_status = 1;
		return (NULL);
	}
	i = 0;
	while (env)
	{
		envp[i] = join_env(env->name, env->content);
		if (!envp[i++])
		{
			g_status = 1;
			return (envp);
		}
		env = env->next;
	}
	envp[i] = NULL;
	return (envp);
}

char	*join_env(char *key, char *value)
{
	char	*tmp;
	char	*res;

	tmp = ft_strjoin(key, "=");
	if (!tmp)
	{
		g_status = 1;
		return (NULL);
	}
	res = ft_strjoin(tmp, value);
	free(tmp);
	if (!res)
		g_status = 1;
	return (res);
}
