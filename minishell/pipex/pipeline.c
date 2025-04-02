/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcaumont <bcaumont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 20:04:08 by bcaumont          #+#    #+#             */
/*   Updated: 2025/04/02 17:29:00 by bcaumont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/* Initialise la structure du pipeline */
t_pipex	*init_minishell_pipeline(t_cmd *cmd_list, t_shell *shell)
{
	t_pipex	*pipex;
	t_pipex	*current;
	t_cmd	*cmd;

	pipex = NULL;
	current = NULL;
	cmd = cmd_list;
	while (cmd)
	{
		current = create_pipe_node(cmd, shell);
		if (!current)
			return (NULL);
		current->cmd = cmd;
		pipex = append_pipe_node(pipex, current);
		cmd = cmd->next;
	}
	set_first_or_last(pipex);
	return (pipex);
}

t_pipex	*append_pipe_node(t_pipex *pipex, t_pipex *current)
{
	t_pipex	*last;

	if (!pipex)
		return (current);
	last = pipex;
	while (last->next)
		last = last->next;
	last->next = current;
	current->prev = last;
	return (pipex);
}

void	set_first_or_last(t_pipex *head)
{
	if (head == NULL)
		return ;
	while (head)
	{
		if (head->next == NULL)
			head->is_last = true;
		if (head->prev == NULL)
			head->is_first = true;
		if (head->prev && head->next)
			head->is_middle = true;
		head = head->next;
	}
}
