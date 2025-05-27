/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_here_doc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: broboeuf <broboeuf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 19:49:33 by garside           #+#    #+#             */
/*   Updated: 2025/05/27 18:02:56 by broboeuf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	made_new_file(char **name)
{
	static int	nb_file = 0;
	char		*nb_str;

	nb_str = ft_itoa(nb_file);
	*name = ft_strjoin("/tmp/here_doc_", nb_str);
	free(nb_str);
	nb_file++;
}

void	fill_here_doc_file(char *delimitor, char *file)
{
	char	*str;
	int		fd;
	pid_t	pid;
	int		status;

	fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		return ;
	signal(SIGINT, SIG_IGN);
	pid = fork();
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		while (1)
		{
			str = readline("> ");
			if (g_status == 130)
			{
				close(fd);
				free(str);
				exit(130);
			}
			if (str == NULL)
			{
				ft_printf("minishell: warning: here-document delimited by end-of-file (wanted `%s')\n",
					delimitor);
				break ;
			}
			if (ft_strcmp(str, delimitor) == 0)
			{
				free(str);
				break ;
			}
			ft_putstr_fd(str, fd);
			ft_putchar_fd('\n', fd);
			free(str);
		}
		close(fd);
		exit(0);
	}
	else
	{
		waitpid(pid, &status, 0);
		if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
		{
			close(fd);
			unlink(file);
			g_status = 130;
			return ;
		}
	}
	close(fd);
	signal(SIGINT, handle_sigint);
}

char	*get_here_doc(char *str)
{
	char	*file_name;
	char	*delimitor;

	delimitor = ft_strdup(str);
	if (!delimitor)
		return (NULL);
	made_new_file(&file_name);
	fill_here_doc_file(delimitor, file_name);
	free(delimitor);
	if (g_status == 130 || access(file_name, F_OK) != 0)
	{
		if (file_name)
		{
			free(file_name);
			file_name = NULL;
		}
		return (NULL);
	}
	return (file_name);
}
