/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: garside <garside@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 18:42:46 by garside           #+#    #+#             */
/*   Updated: 2025/05/25 18:48:12 by garside          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int is_n_flag(char *str)
{
    int i;

    if (!str || str[0] != '-' || str[1] != 'n')
        return (0);
    i = 2;
    while (str[i] == 'n')
        i++;
    return (str[i] == '\0');
}

int ft_echo(t_data *data, t_cmd *cmd)
{
    (void)data;
    int newline = 1;
    int i = 1;

    if (!cmd || !cmd->args)
    {
        write(STDOUT_FILENO, "\n", 1);
        return 0;
    }
    while (cmd->args[i] && is_n_flag(cmd->args[i]))
    {
        newline = 0;
        i++;
    }
    while (cmd->args[i])
    {
        write(STDOUT_FILENO, cmd->args[i], ft_strlen(cmd->args[i]));
        if (cmd->args[i + 1])
            write(STDOUT_FILENO, " ", 1);
        i++;
    }
    if (newline)
        write(STDOUT_FILENO, "\n", 1);
    return 0;
}


