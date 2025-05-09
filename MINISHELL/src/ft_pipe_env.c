/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcaumont <bcaumont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 11:46:15 by bcaumont          #+#    #+#             */
/*   Updated: 2025/05/09 11:47:25 by bcaumont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	count_env_vars(t_env *env)
{
	int	count;

	count = 0;
	while (env)
	{
		count++;
		env = env->next;
	}
	return (count);
}

static char	**alloc_envp_array(int count)
{
	char	**envp;

	envp = malloc(sizeof(char *) * (count + 1));
	if (!envp)
	{
		g_status = 1;
		return (NULL);
	}
	return (envp);
}

static int	fill_envp_array(t_env *env, char **envp)
{
	int	i;

	i = 0;
	while (env)
	{
		envp[i] = join_env(env->name, env->content);
		if (!envp[i])
		{
			g_status = 1;
			return (-1);
		}
		i++;
		env = env->next;
	}
	envp[i] = NULL;
	return (0);
}

char	**env_to_envp(t_env *env)
{
	char	**envp;
	int		count;

	count = count_env_vars(env);
	envp = alloc_envp_array(count);
	if (!envp)
		return (NULL);
	if (fill_envp_array(env, envp) == -1)
		return (envp);
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
