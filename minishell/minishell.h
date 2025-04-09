/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcaumont <bcaumont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 14:47:10 by bcaumont          #+#    #+#             */
/*   Updated: 2025/04/09 10:34:12 by bcaumont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "lib/libft.h"

# define PROMPT "\033[1;32mminishell$> \033[0m"

typedef enum e_token_type
{
	WORD,
	PIPE,
	INPUT,
	OUTPUT,
	HEREDOC,
	APPEND,
	ERROR,
}					t_token_type;

typedef struct s_token
{
	char			*value;
	t_token_type	type;
	struct s_token	*next;
	struct s_token	*prev;
}					t_token;

typedef struct s_env
{
	char			*key;
	char			*value;
	char			*var;
	char			**envp;
	struct s_env	*next;
	struct s_env	*prev;
}					t_env;

typedef struct s_cmd
{
	char			**cmds;
	char			**args;
	char			*path;
	int				pipefd[2];
	t_env			*env;
	pid_t			pid;
	struct s_cmd	*prev;
	struct s_cmd	*next;
}					t_cmd;

typedef struct s_pipex
{
	char			**envp;
	char			**args;
	int				fd_in;
	int				fd_out;
	int				input;
	int				output;
	char			*infile;
	char			*outfile;
	int				pipefd[2];
	bool			is_first;
	bool			is_middle;
	bool			is_last;
	bool			is_here_doc;
	pid_t			pid;
	t_cmd			*cmd;
	struct s_pipex	*prev;
	struct s_pipex	*next;
}					t_pipex;

typedef struct s_shell
{
	char			*input_terminal;
	t_env			*env;
	t_cmd			*cmd;
	t_pipex			*pipex;
	int				exit_status;
}					t_shell;

/* Redirection */
void				execute_pipex_from_minishell(t_shell *shell);

int					ft_echo(t_cmd *cmd, char **envp);
int					ft_cd(char **args, t_shell *shell);
int					ft_pwd(void);
int					ft_exit(char **args, t_shell *shell);
int					ft_env(t_shell *shell);
void				add_or_update_env(t_shell *shell, char *key, char *value);
void				remove_env(t_shell *shell, char *key);
int					execute_builtin(char **args, t_shell *shell);
int					ft_export(char **args, t_shell *shell);
int					ft_unset(char **args, t_shell *shell);
int					is_builtin(char *cmd);
void				cleanup_shell_env(t_shell *shell);
void				cleanup_shell_cmd(t_shell *shell);
void				init_shell(t_shell *shell, char **envp);
t_pipex				*append_pipe_node(t_pipex *pipex, t_pipex *current);
void				parse_env_var(t_env *env);
void				add_env_to_shell(t_shell *shell, char *env_line);
t_cmd				*create_cmd_node(t_shell *shell, char **args);
void				add_cmd_to_shell(t_shell *shell, t_cmd *new_cmd);
char				*get_env_value(char *name, char **envp);
void				ft_print_env_path(char **envp);

/* Topings ~ Tokens */
void				skip_spaces(char **cmd);
bool				free_and_return_false(t_token **begin);
int					handle_quotes(char *cmd, int *i, int *quotes);
int					get_token_length(char *cmd, int *quotes);
t_token				*token_new(t_token_type type, char *value);
int					token_add(t_token **token_list, char *value,
						t_token_type type);
int					append_token(t_token **list, char *str, t_token_type type);
void				token_print_l(t_token *head);
void				token_print_t(t_token_type type);
void				token_del(t_token **token);
void				tokens_free(t_token **token_list);
void				copy_token(char *command, int length, char *str);
bool				add_cmd(t_token **begin, char **command);
bool				create_list_token(t_token **begin, char *cmd);
size_t				token_list(t_token *first);
t_token				*token_last(t_token *head);
void				token_add_front(t_token **first, t_token *new_token);
bool				is_space(char c);
bool				handle_special_case(t_token **begin, char *symbol,
						t_token_type type);
t_token_type		is_special(const char *str);
bool				add_special(t_token **begin, char **cmd);

// /* Initialisation de la struct */
t_pipex				*init_minishell_pipeline(t_cmd *cmd_list, t_shell *shell);
t_pipex				*create_pipe_node(t_cmd *cmd, t_shell *shell);
void				set_first_or_last(t_pipex *head);

// /* Gestion des erreurs & free */
void				ft_free_pipeline(t_pipex *pipeline);
void				error_and_exit(t_pipex *node, char *msg);
void				cleanup(t_pipex *node);
void				cleanup_head(t_pipex *head);
// void				cleanup_here_doc(t_pipex *node);
void				ft_perror(char *msg);

// /* Verifs, secures & utils */
void				secure_close(int fd);
int					secure_open(char *filename, int flags);
void				secure_dup2(int old_fd, int new_fd);
void				secure_dup(t_pipex *current);
pid_t				secure_fork(void);
int					file_is_executable(char *file);

// /* Gestion des pipes & des forks */
void				do_pipe(t_pipex *node);
void				process_pipeline(t_pipex *pipex, t_shell *shell);
void				close_pipes(t_pipex *node);

// /* Executeur */
void				exec(t_pipex *pipex, t_shell *shell);
void				exec_redirection(t_pipex *node);
void				here_doc_redirection(t_pipex *node);
void				here_doc_outfile(t_pipex *node);
void				last_node_redirection(t_pipex *node);
void				exec_redirection_first(t_pipex *node);

// /* Here_doc*/
// void				here_doc(t_pipex *node);
// void				here_doc_put_in(t_pipex *node, int tmp_fd);

/* Gestion des PATHS */
char				*get_envp(char *name, t_pipex *node);
char				*get_path(t_pipex *node);
char				*search_in_path(t_pipex *node, char **all_path);
char				*check_current_directory(t_pipex *node);
char				*check_absolute_path(t_pipex *node);
char				**convert_env_to_array(t_env *env);
int					env_list_size(t_env *env);

#endif
