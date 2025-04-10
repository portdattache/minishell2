/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_sign.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcaumont <bcaumont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 22:39:54 by bcaumont          #+#    #+#             */
/*   Updated: 2025/04/10 23:10:43 by bcaumont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_env_value_from_list(t_env *env, char *name)
{
	if (!name)
		return (NULL);
	while (env)
	{
		if (ft_strcmp(env->key, name) == 0)
			return (env->value);
		env = env->next;
	}
	return (NULL);
}

char	*append_char(char *str, char c)
{
	char	tmp[2];
	char	*res;
	char	*joined;

	tmp[0] = c;
	tmp[1] = '\0';
	joined = ft_strdup(tmp);
	res = ft_strjoin(str, joined);
	free(joined);
	free(str);
	return (res);
}

char	*expand_vars(char *str, t_env *env)
{
	char	*result;
	int		i;

	result = ft_strdup("");
	i = 0;
	while (str && str[i])
	{
		if (str[i] == '$' && str[i + 1] != '\0')
			result = expand_dollar(str, env, result, &i);
		else
		{
			result = append_char(result, str[i]);
			i++;
		}
	}
	return (result);
}

char	*expand_dollar(char *str, t_env *env, char *res, int *i)
{
	char	*var_name;
	char	*value;
	int		start;
	char	*tmp;

	(*i)++;
	start = *i;
	while (str[*i] && (ft_isalnum(str[*i]) || str[*i] == '_'))
		(*i)++;
	var_name = ft_substr(str, start, *i - start);
	value = get_env_value_from_list(env, var_name);
	if (value)
	{
		tmp = ft_strjoin(res, value);
		free(res);
		res = tmp;
	}
	free(var_name);
	return (res);
}
