/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcaumont <bcaumont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 19:07:46 by bcaumont          #+#    #+#             */
/*   Updated: 2025/04/11 10:57:59 by bcaumont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	is_n_flag(char *str)
{
	int	i;

	if (!str || str[0] != '-')
		return (0);
	i = 1;
	if (!str[i])
		return (0);
	while (str[i] == 'n')
		i++;
	return (str[i] == '\0');
}

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
	while (cmd->args[i] && is_n_flag(cmd->args[i]))
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
