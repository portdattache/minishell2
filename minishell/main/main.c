/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcaumont <bcaumont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 17:09:48 by bcaumont          #+#    #+#             */
/*   Updated: 2025/04/09 17:24:47 by bcaumont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	main_cleaner(char **args, t_shell *shell)
{
	if (args != NULL)
		ft_free_split(args);
	if (shell->env)
		cleanup_shell_env(shell);
	if (shell->cmd)
		cleanup_shell_cmd(shell);
	if (shell->pipex)
		ft_free_pipeline(shell->pipex);
	rl_clear_history();
}

static void	exec_direction(char **args, t_shell *shell, char *line)
{
	if (shell->cmd->args && is_builtin(shell->cmd->args[0]))
		execute_builtin(shell->cmd->args, shell);
	else
		execute_pipex_from_minishell(shell);
	ft_free_split(args);
	free(line);
}

int	main(int argc, char **argv, char **envp)
{
	t_shell	shell;
	t_cmd	*cmd;
	char	*line;
	char	**args;

	args = NULL;
	(void)argc;
	(void)argv;
	ft_bzero(&shell, sizeof(t_shell));
	init_shell(&shell, envp);
	while (1)
	{
		line = readline(PROMPT);
		if (!line)
			break ;
		if (*line)
			add_history(line);
		args = args_split(line);
		if (!args)
			free(line);
		cmd = create_cmd_node(&shell, args);
		if (!cmd)
		{
			free(line);
			ft_args_split_free(args);
			continue ;
		}
		add_cmd_to_shell(&shell, cmd);
		exec_direction(args, &shell, line);
	}
	main_cleaner(args, &shell);
	return (0);
}
