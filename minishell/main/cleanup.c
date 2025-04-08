/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcaumont <bcaumont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 08:11:10 by bcaumont          #+#    #+#             */
/*   Updated: 2025/04/08 08:25:29 by bcaumont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	cleanup_shell_env(t_shell *shell)
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
		if (tmp->envp != NULL)
			ft_free_split(tmp->envp);
		free(tmp);
		tmp = next;
	}
	shell->env = NULL;
}

void	cleanup_shell_cmd(t_shell *shell)
{
	t_cmd	*tmp;
	t_cmd	*next;

	tmp = shell->cmd;
	while (tmp)
	{
		next = tmp->next;
		if (tmp->cmds != NULL)
			ft_free_split(tmp->cmds);
		free(tmp);
		tmp = next;
	}
	shell->cmd = NULL;
}
