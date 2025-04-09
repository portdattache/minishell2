/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcaumont <bcaumont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 19:07:46 by bcaumont          #+#    #+#             */
/*   Updated: 2025/04/09 15:26:36 by bcaumont         ###   ########.fr       */
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
	char	*var_name;
	char	*value;
	int		i;
	int		newline;

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
		if (cmd->args[i][0] == '$')
		{
			var_name = cmd->args[i] + 1;
			value = get_env_value(var_name, envp);
			if (value)
				ft_printf("%s\n", value);
		}
		else
			ft_printf("%s", cmd->args[i]);
		if (cmd->args[i + 1])
			ft_printf(" ");
		i++;
	}
	if (newline)
		ft_printf("\n");
	return (0);
}
