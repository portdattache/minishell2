/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcaumont <bcaumont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 19:07:46 by bcaumont          #+#    #+#             */
/*   Updated: 2025/04/17 13:40:09 by bcaumont         ###   ########.fr       */
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

static int	has_unquoted_semicolon(char *str)
{
	int		i;
	char	quote;

	i = 0;
	quote = 0;
	while (str[i])
	{
		if (!quote && (str[i] == '\'' || str[i] == '"'))
			quote = str[i];
		else if (quote && str[i] == quote)
			quote = 0;
		else if (!quote && str[i] == ';')
			return (1);
		i++;
	}
	return (0);
}

static void	handle_semicolon(char *str, t_env *env)
{
	char	**parts;
	char	*trimmed;
	char	*before;
	char	*after;

	parts = ft_split(str, ';');
	if (parts[0])
	{
		before = ft_strtrim(parts[0], " \t");
		trimmed = expand_vars(before, env);
		ft_printf("%s\n", trimmed);
		free(before);
		free(trimmed);
	}
	if (parts[1])
	{
		after = ft_strtrim(parts[1], " \t");
		if (after && *after)
		{
			ft_dprintf(2, "minishell: %s: command not found", after);
			g_status = 127;
		}
		free(after);
	}
	ft_free_split(parts);
}

static void	print_echo_args(t_cmd *cmd, int i)
{
	char	*expand;

	while (cmd->args[i])
	{
		if (has_unquoted_semicolon(cmd->args[i]))
		{
			handle_semicolon(cmd->args[i], cmd->env);
			return ;
		}
		expand = expand_vars(cmd->args[i], cmd->env);
		ft_printf("%s", expand);
		free(expand);
		if (cmd->args[i + 1])
			ft_printf(" ");
		i++;
	}
}

int	ft_echo(t_cmd *cmd, char **envp)
{
	int	i;
	int	newline;

	(void)envp;
	i = 1;
	newline = 1;
	while (cmd->args[i] && is_n_flag(cmd->args[i]))
	{
		newline = 0;
		i++;
	}
	print_echo_args(cmd, i);
	if (newline)
		ft_printf("\n");
	return (0);
}
