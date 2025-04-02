/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   first_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcaumont <bcaumont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 12:28:16 by bcaumont          #+#    #+#             */
/*   Updated: 2025/04/02 12:48:58 by bcaumont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	first_init(t_shell *shell)
{
	shell->env = NULL;
	shell->cmd = NULL;
	shell->pipex = NULL;
	shell->exit_status = 0;
	first_init_env(shell);
}

void	first_init_env(t_shell *shell)
{
	t_env	*first_env;

	first_env = malloc(sizeof(t_env));
	if (!first_env)
		exit(EXIT_FAILURE);
	first_env->var = NULL;
	first_env->key = NULL;
	first_env->value = NULL;
	first_env->envp = NULL;
	first_env->next = NULL;
	first_env->prev = NULL;
	shell->env = first_env;
}
