/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_spe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcaumont <bcaumont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 14:12:16 by broboeuf          #+#    #+#             */
/*   Updated: 2025/04/12 12:46:20 by bcaumont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

bool	is_space(char c)
{
	return (c == ' ' || c == '\n' || c == '\r' || c == '\f' || c == '\t'
		|| c == '\v');
}

bool	handle_special_case(t_token **begin, char *symbol, t_token_type type)
{
	char	*dup;

	dup = ft_strdup(symbol);
	if (!dup)
		return (false);
	return (append_token(begin, dup, type));
}

t_token_type	is_special(const char *str)
{
	int				i;
	char			*symbols[5];
	t_token_type	types[5];

	symbols[0] = "<<";
	symbols[1] = ">>";
	symbols[2] = "<";
	symbols[3] = ">";
	symbols[4] = "|";
	types[0] = HEREDOC;
	types[1] = APPEND;
	types[2] = INPUT;
	types[3] = OUTPUT;
	types[4] = PIPE;
	i = 0;
	while (i < 5)
	{
		if (!ft_strncmp(str, symbols[i], ft_strlen(symbols[i])))
			return (types[i]);
		i++;
	}
	return (WORD);
}

bool	add_special(t_token **begin, char **cmd)
{
	t_token_type	spe;
	int				i;

	spe = (t_token_type)is_special(*cmd);
	if (spe == 0)
		return (false);
	i = 0;
	if (!handle_special_loop(begin, spe, &i))
		return (false);
	if (spe == HEREDOC || spe == APPEND)
		*cmd += 2;
	else
		(*cmd)++;
	return (true);
}

bool	handle_special_loop(t_token **begin, t_token_type spe, int *i)
{
	char			*symbols[5];
	t_token_type	types[5];

	symbols[0] = "<<";
	symbols[1] = ">>";
	symbols[2] = "<";
	symbols[3] = ">";
	symbols[4] = "|";
	types[0] = HEREDOC;
	types[1] = APPEND;
	types[2] = INPUT;
	types[3] = OUTPUT;
	types[4] = PIPE;
	while (*i < 5)
	{
		if (spe == types[*i] && !handle_special_case(begin, symbols[*i],
				types[*i]))
			return (false);
		(*i)++;
	}
	return (true);
}
