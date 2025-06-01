/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_quote_utils_1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcaumont <bcaumont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 13:35:05 by garside           #+#    #+#             */
/*   Updated: 2025/06/01 21:04:52 by bcaumont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	check_quotes(char *input)
{
	int	i;

	i = 0;
	while (input[i])
	{
		if (input[i] == '\'')
		{
			i++;
			while (input[i] && (input[i] != '\''))
				i++;
			if (!input[i])
				return (ft_putstr_fd("quote error\n", 2), 1);
		}
		if (input[i] == '\"')
		{
			i++;
			while (input[i] && (input[i] != '\"'))
				i++;
			if (!input[i])
				return (ft_putstr_fd("quote error\n", 2), 1);
		}
		i++;
	}
	return (0);
}

char	*ft_get_env(char *str, t_data *data)
{
	t_env	*current;
	char	*value;
	int		len;

	current = data->env;
	len = ft_strlen(str);
	while (current)
	{
		if (ft_strcmp(str, current->name) == 0)
		{
			value = ft_strdup(current->content);
			return (value);
		}
		current = current->next;
	}
	return (NULL);
}

char	*change_env(t_data *data, int *i)
{
	int		first;
	int		last;
	char	*name;
	char	*value;

	(*i)++;
	first = (*i);
	while (ft_isalnum(data->input[*i]) || data->input[*i] == '_')
		(*i)++;
	last = (*i);
	name = ft_substr(data->input, first, last - first);
	if (!name[0])
		return (free(name), ft_strdup("$"));
	value = ft_get_env(name, data);
	free(name);
	return (value);
}

char	*append_error_code(t_data *data, char *extract, int *i, int *first)
{
	int		last;
	char	*tmp;
	char	*temp;

	last = *i;
	tmp = ft_substr(data->input, *first + 1, last - *first - 1);
	temp = ft_strjoin(extract, tmp);
	free(tmp);
	free(extract);
	extract = handle_error_code(data, temp, i);
	*first = *i - 1;
	return (extract);
}
