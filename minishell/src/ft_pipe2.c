/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcaumont <bcaumont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 19:58:33 by garside           #+#    #+#             */
/*   Updated: 2025/06/01 21:04:50 by bcaumont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	safe_close(int fd)
{
	if (fd >= 0)
		close(fd);
}

int	redirect_management(t_cmd *cmd, int prev_fd)
{
	if (manag_infile(cmd, prev_fd) == 1)
	{
		safe_close(cmd->pipe_fd[PIPE_READ]);
		safe_close(cmd->pipe_fd[PIPE_WRITE]);
		return (1);
	}
	if (manag_outfile(cmd, cmd->pipe_fd) == 1)
	{
		safe_close(cmd->pipe_fd[PIPE_READ]);
		safe_close(cmd->pipe_fd[PIPE_WRITE]);
		return (1);
	}
	safe_close(cmd->pipe_fd[PIPE_READ]);
	safe_close(cmd->pipe_fd[PIPE_WRITE]);
	return (0);
}
