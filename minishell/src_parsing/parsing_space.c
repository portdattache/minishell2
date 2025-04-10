/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_space.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: broboeuf <broboeuf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 16:12:22 by broboeuf          #+#    #+#             */
/*   Updated: 2025/04/04 16:44:14 by broboeuf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	skip_spaces(char **cmd)
{
	while (is_space(**cmd))
		(*cmd)++;
}

bool	free_and_return_false(t_token **begin)
{
	if (*begin)
		tokens_free(begin);
	return (false);
}
