/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_ges.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: broboeuf <broboeuf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 14:12:16 by broboeuf          #+#    #+#             */
/*   Updated: 2025/04/04 16:42:52 by broboeuf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	copy_token(char *command, int length, char *str)
{
	int		i;
	int		j;
	char	quote;

	i = 0;
	j = 0;
	while (j < length)
	{
		if (command[j] == '"' || command[j] == '\'')
		{
			quote = command[j++];
			while (command[j] && command[j] != quote)
				str[i++] = command[j++];
			j++;
		}
		else
			str[i++] = command[j++];
	}
	str[i] = '\0';
}

bool	add_cmd(t_token **begin, char **command)
{
	int		length;
	int		quotes;
	char	*str;

	length = get_token_length(*command, &quotes);
	if (length < (2 * quotes))
		return (true);
	str = malloc(sizeof(char) * (length + 1 - (2 * quotes)));
	if (!str)
		return (false);
	copy_token(*command, length - (2 * quotes), str);
	if (!append_token(begin, str, WORD))
		return (false);
	*command += length;
	return (true);
}
