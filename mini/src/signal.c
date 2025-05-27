/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: broboeuf <broboeuf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 18:45:06 by garside           #+#    #+#             */
/*   Updated: 2025/05/27 17:59:54 by broboeuf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../octolib/includes/libft.h"
#include <readline/history.h>
#include <readline/readline.h>
#include <signal.h>

void	handle_sigint(int sig)
{
	(void)sig;
	if (rl_done == 0)
	{
		g_status = 1;
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	else
	{
		g_status = 130;
		write(1, "\n", 1);
	}
}

void	init_signal(void)
{
	signal(SIGINT, handle_sigint); // Ctrl+C annule la ligne en shell
	signal(SIGQUIT, SIG_IGN);      // Ctrl+\ ignoré en shell
}

void	reset_signals_child(void)
{
	signal(SIGINT, SIG_DFL);  // Ctrl+C interrompt la commande
	signal(SIGQUIT, SIG_DFL); // Ctrl+\ interrompt la commande
}
