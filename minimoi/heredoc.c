/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: broboeuf <broboeuf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 12:07:11 by broboeuf          #+#    #+#             */
/*   Updated: 2025/04/29 13:00:55 by broboeuf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handle_eof_warning(char *delimiter)
{
	ft_putstr_fd("minishell: warning: here-document ", STDERR_FILENO);
	ft_putstr_fd("delimited by end-of-file (wanted '", STDERR_FILENO);
	ft_putstr_fd(delimiter, STDERR_FILENO);
	ft_putstr_fd("')\n", STDERR_FILENO);
}

static bool	process_heredoc_line(char **line, t_data *data, int fd)
{
	if (!replace_dollar(line, data))
	{
		free(*line);
		return (false);
	}
	ft_putstr_fd(*line, fd);
	ft_putchar_fd('\n', fd);
	free(*line);
	return (true);
}

static bool	read_heredoc_input(t_data *data, int fd, char *delimiter)
{
	char	*line;

	while (true)
	{
		line = readline("> ");
		if (!line)
		{
			handle_eof_warning(delimiter);
			break ;
		}
		if (ft_strcmp(delimiter, line) == 0)
		{
			free(line);
			break ;
		}
		if (!process_heredoc_line(&line, data, fd))
			return (false);
	}
	return (true);
}

static int	create_heredoc_file(void)
{
	int	fd;

	fd = open(".heredoc.tmp", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd < 0)
		perror("minishell: heredoc");
	return (fd);
}

int	handle_heredoc(t_data *data, char *delimiter)
{
	int fd;
	int ret;

	fd = create_heredoc_file();
	if (fd < 0)
		return (-1);
	ret = read_heredoc_input(data, fd, delimiter);
	close(fd);
	if (!ret)
	{
		unlink(".heredoc.tmp");
		return (-1);
	}
	fd = open(".heredoc.tmp", O_RDONLY);
	if (fd >= 0)
		unlink(".heredoc.tmp");
	return (fd);
}