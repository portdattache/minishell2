/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: broboeuf <broboeuf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 16:20:24 by garside           #+#    #+#             */
/*   Updated: 2025/05/07 20:06:29 by broboeuf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "../octolib/includes/libft.h"
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <unistd.h>

# define PROMPT "\033[1;32mminishell$> \033[0m"

extern volatile sig_atomic_t	g_status;

typedef enum e_token_type
{
	WORD,
	PIPE,
	REDIRECTION_IN,
	REDIRECTION_OUT,
	HEREDOC,
	APPEND,
}								t_TokenType;

typedef struct s_token
{
	char						*value;
	t_TokenType					type;
	struct s_token				*next;
}								t_token;

typedef struct s_env
{
	char						*name;
	char						*content;
	struct s_env				*next;
	struct s_env				*prev;
}								t_env;

typedef struct s_cmd
{
	char						**cmds;
	char						**args;
	char						**cmd_param;
	char						*path;
	int							pipefd[2];
	t_env						*env;
	pid_t						pid;
	int							append_out;
	int							heredoc;
	int							infile;
	int							outfile;
	bool						skip_cmd;
	struct s_cmd				*prev;
	struct s_cmd				*next;
}								t_cmd;

typedef struct s_data
{
	char						*input;
	t_env						*env;
	t_env						*export;
	char						**envp;
	t_token						*token;
	t_cmd						*cmd;
	int							last_status;
}								t_data;

// parse
t_env							*env_new(char *name, char *value);
void							free_env_list(t_env *new_list);
t_token							*get_next_token(t_data *data, int *i);
t_token							*ft_lexer(t_data *data);
int								parse(t_data *data);

// lexer
char							*handle_quotes_part(t_data *data, int *i,
									char *value);
t_token							*handle_cmd_or_arg(t_data *data, int *i);
t_token							*handle_double_redir(char *input, int *i);
t_token							*handle_redirection(char *input, int *i);
void							skip_whitespace(const char *input, int *i);

// lexer1
void							free_one_token(t_token *token);
void							free_token(t_token *head);
t_token							*new_token(char *value, t_TokenType type);
char							*handle_error_code(t_data *data, char *value,
									int *i);
void							add_token_to_list(t_token **head,
									t_token **last, t_token *new_token);

// lexer2
int								is_skippable_char(char c);
int								is_token_char(char c);
char							*handle_env_value(t_data *data, int *i,
									char *value);
char							*handle_plain_text(t_data *data, int *i,
									char *value);
t_token							*handle_pipe(int *i);

// quote
char							*append_env_variable(t_data *data,
									char *extract, int *i, int *first);
char							*append_remaining_segment(t_data *data,
									char *extract, int first, int i);
char							*extract_word_double(t_data *data, int *i);
char							*extract_word_single(char *input, int *i);
char							*handle_quotes(t_data *data, int *i);

// quote1
int								check_quotes(char *input);
char							*ft_get_env(char *str, t_data *data);
char							*change_env(t_data *data, int *i);
char							*append_error_code(t_data *data, char *extract,
									int *i, int *first);

// exec
char							*get_cmd_path(t_data *data, char **cmd);
void							exec_child_process(t_data *data);
int								ft_shell(t_data *data);
int								which_command(t_data *data);
int								exec_line(t_data *data);

// exec1
void							free_data(t_data *data);
char							**ft_get_cmd(t_data *data);
void							ft_replace_in_env(t_data *data, char *name,
									char *value);

// export
int								ft_is_valid(char *str);
int								check_name(char *str, t_env *node,
									char *content);
void							free_name_content(char *name, char *content);
char							*get_content(char *str, int i);

// char	*find_cmd_path(char *cmd, t_data *data);
void							ft_lstadd_back_env(t_env **lst, t_env *new);
char							**translate_in_tab(t_data *data);
int								calcul_dynamique_len(t_env *tmp);
void							free_split(char **tmp);
t_env							*init_env_list(char **env);

//--------gestion des signaux---------
void							init_signal(void);

//-------------builtins---------------
int								ft_pwd(void);
int								ft_cd(t_data *data);
int								ft_env(t_data *data);
int								ft_echo(t_data *data);
int								ft_exit(t_data *data);
int								ft_isalldigit(char *str);

// ryew
int								ft_executables(t_data *data);
int								ft_export(t_data *data);
void							sort(char **tmp);
t_env							*init_export_list(char **env);
int								ft_unset(t_data *data);
char							*find_cmd_path(char *cmd, t_data *data);

/* ---------- Redirections ---------- */
int								opening(t_data *data, char *filename,
									t_TokenType type);
bool							redir_in(t_cmd *cmd, t_token *token,
									t_data *data);
bool							all_redir_in(t_cmd *cmd, t_token *start,
									t_data *data);
bool							redir_out(t_cmd *cmd, t_token *token,
									t_data *data);
bool							all_redir_out(t_cmd *cmd, t_token *start,
									t_data *data);
bool							add_argument(char ***cmd_args, int *index,
									char *value);
bool							replace_dollar(char **line, t_data *data);
bool							is_valid_argument(t_token *token);
void							cleanup_arguments(char **args, int count);
bool							process_token(t_data *data, t_token **current);
int								handle_heredoc(t_data *data, char *delimiter);
bool							process_token(t_data *data, t_token **token);
t_cmd							*init_new_cmd(t_data *data);
void							setup_pipe(t_cmd *cmd);
t_cmd							*get_last_cmd(t_cmd *cmd);
char							**parse_command_arguments(t_data *data,
									t_token *token);

#endif
