/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcaumont <bcaumont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 20:04:08 by bcaumont          #+#    #+#             */
/*   Updated: 2025/03/24 14:46:28 by bcaumont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/* Initialise la structure du pipeline */
t_pipex	*init_minishell_pipeline(t_cmd *cmd_list, t_shell *shell)
{
	t_pipex	*pipex;
	t_pipex	*current;
	t_cmd	*cmd;
	t_pipex	*last;

	pipex = NULL;
	current = NULL;
	cmd = cmd_list;
	while (cmd)
	{
		current = create_pipe_node(cmd, shell);
		if (!current)
			return (NULL);
		current->cmd = cmd;
		if (!pipex)
			pipex = current;
		else
		{
			last = pipex;
			while (last->next)
				last = last->next;
			last->next = current;
			current->prev = last;
		}
		cmd = cmd->next;
	}
	set_first_or_last(pipex);
	return (pipex);
}

/* Va ajouter le noeud a la dll pipex */
// t_pipex	*add_pipex_node(t_data *data)
// {
// 	t_pipex	*new_node;

// 	new_node = create_node(data);
// 	if (!new_node)
// 		return (NULL);
// 	if (data->prev)
// 	{
// 		data->prev->next = new_node;
// 		new_node->prev = data->prev;
// 	}
// 	return (new_node);
// }

/* Va determiner si le noeud est le premier, le dernier ou au milieu */
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
