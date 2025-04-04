/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_env_to_shell.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcaumont <bcaumont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 11:54:41 by bcaumont          #+#    #+#             */
/*   Updated: 2025/04/04 12:07:40 by bcaumont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	add_env_to_shell(t_shell *shell, char *env_line)
{
	t_env	*new_env;
	t_env	*last;

	new_env = malloc(sizeof(t_env));
	if (!new_env)
		exit(EXIT_FAILURE);
	new_env->var = ft_strdup(env_line);
	new_env->envp = NULL;
	new_env->key = NULL;
	new_env->value = NULL;
	new_env->next = NULL;
	new_env->prev = NULL;
	parse_env_var(new_env);
	if (!shell->env)
		shell->env = new_env;
	else
	{
		last = shell->env;
		while (last->next)
			last = last->next;
		last->next = new_env;
		new_env->prev = last;
	}
}

void	parse_env_var(t_env *env)
{
	int		i;
	char	*var;

	var = env->var;
	i = 0;
	while (var[i] && var[i] != '=')
		i++;
	env->key = ft_substr(var, 0, i);
	if (var[i] == '=')
		env->value = ft_strdup(&var[i + 1]);
	else
		env->value = NULL;
}
