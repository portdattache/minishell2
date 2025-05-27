/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_here_doc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcaumont <bcaumont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 19:49:33 by garside           #+#    #+#             */
/*   Updated: 2025/05/24 15:36:51 by bcaumont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	made_new_file(int *fd, char **name)
{
	static int	nb_file = 0;

	*name = ft_strjoin("/tmp/here_doc_", ft_itoa(nb_file));
	*fd = open(*name, O_RDWR | O_CREAT | O_TRUNC, 0644);
	nb_file++;
}

void	fill_here_doc_file(int fd, char *delimitor)
{
	char	*str;

	while (1)
	{
		str = readline("> ");
		if (str == NULL)
		{
			ft_printf("bash: warning: here-document delimited"\
						" by end-of-file (wanted `%s')\n", \
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
}

char	*get_here_doc(char *str)
{
	char	*file_name;
	char	*delimitor;
	int		here_doc_fd;

	delimitor = ft_strdup(str);
	file_name = NULL;
	made_new_file(&here_doc_fd, &file_name);
	if (here_doc_fd == -1)
		return (ft_printf("error to create a tmp file\n"), NULL);
	fill_here_doc_file(here_doc_fd, delimitor);
	close(here_doc_fd);
	return (file_name);
}
