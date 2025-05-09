/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cleaner.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcaumont <bcaumont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 11:39:37 by bcaumont          #+#    #+#             */
/*   Updated: 2025/05/09 11:56:24 by bcaumont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	main_cleaner(t_data *data)
{
	if (data->cmd != NULL)
		free_cmd(data->cmd);
	if (data->env != NULL)
		free_env_list(data->env);
	if (data->export != NULL)
		free_env_list(data->export);
	if (data->token != NULL)
		free_token(data->token);
}

void	free_cmd(t_cmd *cmd)
{
	t_cmd	*tmp;
	t_cmd	*next;

	tmp = cmd;
	if (cmd != NULL)
	{
		tmp = cmd;
		while (tmp)
		{
			next = tmp->next;
			if (tmp->args != NULL)
				free_split(tmp->args);
			if (tmp->cmds != NULL)
				free_split(tmp->cmds);
			if (tmp->path != NULL)
				free(tmp->path);
			free(tmp);
			tmp = next;
		}
		cmd = NULL;
	}
	return ;
}
