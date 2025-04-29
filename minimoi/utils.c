/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: broboeuf <broboeuf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 12:12:20 by broboeuf          #+#    #+#             */
/*   Updated: 2025/04/29 14:40:32 by broboeuf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	setup_redirections(t_cmd *cmd, int *pipefd, t_data *data)
{
	close(pipefd[0]);
	if (cmd->infile != STDIN_FILENO)
	{
		dup2(cmd->infile, STDIN_FILENO);
		close(cmd->infile);
	}
	if (cmd->outfile != STDOUT_FILENO)
	{
		dup2(cmd->outfile, STDOUT_FILENO);
		close(cmd->outfile);
	}
	else if (cmd->next != data->cmd)
		dup2(pipefd[1], STDOUT_FILENO);
	close(pipefd[1]);
}

static bool	is_directory(const char *path)
{
	struct stat	path_stat;

	if (stat(path, &path_stat) != 0)
		return (false);
	return (!S_ISREG(path_stat.st_mode));
}
