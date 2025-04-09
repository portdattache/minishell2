/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcaumont <bcaumont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 19:00:07 by bcaumont          #+#    #+#             */
/*   Updated: 2025/04/09 10:14:27 by bcaumont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_env(t_shell *shell)
{
	t_env	*env;

	env = shell->env;
	if (env == NULL)
		return (1);
	while (env)
	{
		ft_printf("%s=%s\n", env->key, env->value);
		env = env->next;
	}
	return (0);
}

void	ft_print_env_path(char **envp)
{
	int		i;
	char	*prefix;

	prefix = "PATH=";
	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], prefix, 5) == 0)
		{
			ft_printf("%s\n", envp[i] + 5);
			return ;
		}
		i++;
	}
}

char	*get_env_value(char *name, char **envp)
{
	int		i;
	size_t	len;

	if (!name)
		return (NULL);
	len = ft_strlen(name);
	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], name, len) == 0 && envp[i][len] == '=')
			return (envp[i] + len + 1);
		i++;
	}
	return (NULL);
}
