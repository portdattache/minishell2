/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcaumont <bcaumont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 19:07:46 by bcaumont          #+#    #+#             */
/*   Updated: 2025/04/10 23:09:38 by bcaumont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// int	ft_echo(char **args)
// {
// 	int		i;
// 	int		newline;
// 	char	*value;

// 	i = 1;
// 	newline = 1;
// 	if (args[i] && ft_strcmp(args[i], "-n") == 0)
// 	{
// 		newline = 0;
// 		i++;
// 	}
// 	while (args[i])
// 	{
// 		write(1, args[i], ft_strlen(args[i]));
// 		if (args[i + 1])
// 			write(1, " ", 1);
// 		i++;
// 	}
// 	if (newline)
// 		write(1, "\n", 1);
// 	return (0);
// }

int	ft_echo(t_cmd *cmd, char **envp)
{
	int		i;
	int		newline;
	char	*expand;

	(void)envp;
	i = 1;
	newline = 1;
	if (!cmd || !cmd->args)
	{
		ft_printf("\n");
		return (1);
	}
	if (cmd->args[i] && ft_strcmp(cmd->args[i], "-n") == 0)
	{
		newline = 0;
		i++;
	}
	while (cmd->args[i])
	{
		expand = expand_vars(cmd->args[i], cmd->env);
		ft_printf("%s", expand);
		free(expand);
		if (cmd->args[i + 1])
			ft_printf(" ");
		i++;
	}
	if (newline)
		ft_printf("\n");
	return (0);
}
