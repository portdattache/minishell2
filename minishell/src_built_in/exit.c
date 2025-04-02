/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcaumont <bcaumont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 18:52:23 by bcaumont          #+#    #+#             */
/*   Updated: 2025/04/02 10:48:31 by bcaumont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_exit(char **args, t_shell *shell)
{
	int	exit_code;

	exit_code = 0;
	if (args[1])
		exit_code = ft_atoi(args[1]);
	ft_args_split_free(args);
	rl_clear_history();
	cleanup_shell(shell);
	exit(exit_code);
}
