/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcaumont <bcaumont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 19:06:08 by garside           #+#    #+#             */
/*   Updated: 2025/06/01 21:04:56 by bcaumont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	remove_from_list(t_env **list, char *name)
{
	t_env	*current;
	t_env	*prev;

	current = *list;
	prev = NULL;
	while (current)
	{
		if (ft_strcmp(current->name, name) == 0)
		{
			if (prev)
				prev->next = current->next;
			else
				*list = current->next;
			if (current->next)
				current->next->prev = prev;
			free(current->name);
			free(current->content);
			free(current);
			return ;
		}
		prev = current;
		current = current->next;
	}
}

int	ft_unset(t_data *data)
{
	int		i;
	t_cmd	*cmd;

	i = 0;
	cmd = data->cmd_list;
	if (!cmd->args[1])
		return (1);
	while (cmd->args[i])
	{
		remove_from_list(&data->env, cmd->args[i]);
		remove_from_list(&data->export, cmd->args[i]);
		i++;
	}
	return (0);
}
