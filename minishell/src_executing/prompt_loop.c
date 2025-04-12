/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_loop.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcaumont <bcaumont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 11:07:12 by bcaumont          #+#    #+#             */
/*   Updated: 2025/04/12 11:16:18 by bcaumont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	prompt_loop(t_shell *shell)
{
	t_cmd	*cmd;
	char	*line;
	char	**args;

	while (1)
	{
		line = readline(PROMPT);
		if (!line)
			break ;
		if (*line)
			add_history(line);
		args = args_split(line);
		if (!args)
		{
			free(line);
			continue ;
		}
		cleanup_shell_cmd(shell);
		cmd = create_cmd_node(shell, args);
		ft_free_split(args);
		add_cmd_to_shell(shell, cmd);
		exec_direction(shell, line);
	}
}
