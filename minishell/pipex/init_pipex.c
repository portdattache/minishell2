/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_pipex.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcaumont <bcaumont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 20:01:50 by bcaumont          #+#    #+#             */
/*   Updated: 2025/04/08 11:50:52 by bcaumont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/* Va initialiser le nouveau noeud avec les valeurs par defaut */
void	init_pipe_node(t_pipex *node, t_cmd *cmd, t_shell *shell)
{
	node->cmd = NULL;
	node->args = cmd->args;
	node->envp = shell->env->envp;
	node->input = -1;
	node->output = -1;
	node->pipefd[0] = -1;
	node->pipefd[1] = -1;
	node->pid = -1;
	node->prev = NULL;
	node->next = NULL;
	node->is_last = false;
	node->is_middle = false;
	node->is_first = false;
	if (!cmd || !cmd->cmds)
		return ;
	node->cmd = cmd;
}

/* Creation du nouveau noeud dans la struct pipex */
t_pipex	*create_pipe_node(t_cmd *cmd, t_shell *shell)
{
	t_pipex	*node;

	if (!cmd || !cmd->cmds)
		return (NULL);
	node = malloc(sizeof(t_pipex));
	if (!node)
		return (NULL);
	ft_memset(node, 0, sizeof(t_pipex));
	init_pipe_node(node, cmd, shell);
	if (!node->cmd || !node->cmd->cmds)
	{
		free(node);
		return (NULL);
	}
	return (node);
}

int	env_list_size(t_env *env)
{
	int	size;

	size = 0;
	while (env)
	{
		size++;
		env = env->next;
	}
	return (size);
}

char	**convert_env_to_array(t_env *env)
{
	char	**env_array;
	int		size;
	int		i;

	size = env_list_size(env);
	env_array = malloc(sizeof(char *) * (size + 1));
	if (!env_array)
		return (NULL);
	i = 0;
	while (env)
	{
		env_array[i] = ft_strdup(env->value);
		if (!env_array[i])
		{
			ft_free_split(env_array);
			return (NULL);
		}
		env = env->next;
		i++;
	}
	env_array[i] = NULL;
	return (env_array);
}
