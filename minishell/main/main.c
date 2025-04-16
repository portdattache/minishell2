/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcaumont <bcaumont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 17:09:48 by bcaumont          #+#    #+#             */
/*   Updated: 2025/04/15 15:53:40 by bcaumont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

volatile sig_atomic_t	g_status = 0;

void	main_cleaner(t_shell *shell)
{
	if (shell->env != NULL)
		cleanup_shell_env(shell);
	if (shell->cmd != NULL)
		cleanup_shell_cmd(shell);
	if (shell->pipex != NULL)
		ft_free_pipeline(shell->pipex);
	rl_clear_history();
}

void	exec_direction(t_shell *shell, char *line)
{
	if (shell->cmd->args && is_builtin(shell->cmd->args[0]))
		execute_builtin(shell->cmd->args, shell);
	else
		execute_pipex_from_minishell(shell);
	free(line);
}

int	main(int argc, char **argv, char **envp)
{
	t_shell	shell;

	(void)argc;
	(void)argv;
	ft_bzero(&shell, sizeof(t_shell));
	init_shell(&shell, envp);
	setup_signals();
	prompt_loop(&shell);
	main_cleaner(&shell);
	return (0);
}
