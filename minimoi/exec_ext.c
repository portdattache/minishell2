/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_ext.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: broboeuf <broboeuf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 12:13:05 by broboeuf          #+#    #+#             */
/*   Updated: 2025/04/29 15:49:47 by broboeuf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_cmd_path(char **path, char *cmd_name, t_data *data)
{
	if (is_directory(*path))
	{
		print_error(cmd_name, ": Is a directory", NULL);
		data->exit_code = 126;
		return (FAILURE);
	}
	if (access(*path, X_OK) != 0)
	{
		print_error(*path);
		data->exit_code = 126;
		return (FAILURE);
	}
	return (SUCCESS);
}

static int	resolve_cmd_path(char **path, char *cmd, t_data *data)
{
	if (!ft_strchr(cmd, '/'))
		*path = find_command_in_path(data, cmd, data->env);
	else
		*path = handle_absolute_path(cmd, data);
	if (!*path)
	{
		if (data->exit_code == -1)
			free_all(data, NULL, data->exit_code);
		data->exit_code = 127;
		return (FAILURE);
	}
	return (verify_command_path(path, cmd, data));
}

void	exec_ext(t_data *data, t_cmd *cmd, int *pipefd)
{
	char	*path;
	char	**env;

	if (resolve_cmd_path(&path, cmd->cmd_param[0], data) != SUCCESS)
		return ;
	setup_redirections(cmd, pipefd, data);
	env = convert_env_list(data->env);
	if (!env)
	{
		free(path);
		free_all(data, ERR_MALLOC, EXT_MALLOC);
	}
	clean_before_exec(path, cmd->cmd_param, env, data);
}

void	clean_before_exec(char *path, char **args, char **env, t_data *data)
{
	rl_clear_history();
	setup_child_signals();
	execve(path, args, env);
	free(path);
	free_str_array(env);
	handle_exec_error(data);
}

void	handle_exec_error(t_data *data)
{
	perror("minishell");
	free_all(data, NULL, 126);
}