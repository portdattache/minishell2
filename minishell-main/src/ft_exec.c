/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcaumont <bcaumont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 16:09:23 by garside           #+#    #+#             */
/*   Updated: 2025/05/02 13:11:27 by bcaumont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*get_cmd_path(t_data *data, char **cmd)
{
	if (data->token->value[0] == '/')
		return (ft_strdup(cmd[0]));
	return (find_cmd_path(cmd[0], data->envp));
}

void	exec_child_process(t_data *data)
{
	char	**cmd;
	char	*path;

	cmd = ft_get_cmd(data);
	path = get_cmd_path(data, cmd);
	if (!path)
	{
		ft_putstr_fd(data->token->value, 2);
		ft_putstr_fd(": command not found\n", 2);
		free_data(data);
		free_split(cmd);
		exit(127);
	}
	execve(path, cmd, data->envp);
	ft_putstr_fd("execve failed\n", 2);
	free_data(data);
	free_split(cmd);
	free(path);
	exit(127);
}

int	ft_shell(t_data *data)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == -1)
		return (ft_putstr_fd("fork failed\n", 2), 1);
	if (pid == 0)
		exec_child_process(data);
	waitpid(pid, &status, 0);
	return ((status >> 8) & 0xFF);
}

int	which_command(t_data *data)
{
	if (ft_strncmp(data->token->value, "export", 6) == 0
		&& !data->token->value[6])
		return (ft_export(data));
	if (ft_strncmp(data->token->value, "unset", 5) == 0
		&& !data->token->value[5])
		return (ft_unset(data));
	if (ft_strncmp(data->token->value, "exit", 4) == 0
		&& !data->token->value[4])
		return (ft_exit(data));
	if (ft_strncmp(data->token->value, "echo", 4) == 0
		&& !data->token->value[4])
		return (ft_echo(data));
	if (ft_strncmp(data->token->value, "pwd", 3) == 0 && !data->token->value[3])
		return (ft_pwd());
	if (ft_strncmp(data->token->value, "env", 3) == 0 && !data->token->value[3])
		return (ft_env(data));
	if (ft_strncmp(data->token->value, "cd", 2) == 0 && !data->token->value[2])
		return (ft_cd(data));
	if (ft_strncmp(data->token->value, "./", 2) == 0)
		return (ft_executables(data));
	return (ft_shell(data));
}

int	exec_line(t_data *data)
{
	t_cmd	*cmd_list;

	if (has_pipe(data->token))
	{
		cmd_list = build_cmd_list(data->token, data->env);
		if (!cmd_list)
			return (1);
		return (exec_pipeline(cmd_list));
	}
	else
		return (which_command(data));
}
