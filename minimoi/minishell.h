#ifndef MINISHELL_H
# define MINISHELL_H

# include <errno.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

# define SUCCESS 0
# define FAILURE 1

# define ERR_MALLOC "malloc failed"
# define EXT_MALLOC 12

# define ERR_PIPE "pipe failed"
# define EXT_PIPE 13

# define ERR_FORK "fork failed"
# define EXT_FORK 14

# define ERR_EXEC "execution failed"
# define EXT_EXEC 126

# define ERR_CMDNF "command not found"
# define EXT_CMDNF 127

# define PATH_MAX 4096

typedef enum e_token_type
{
	WORD,
	PIPE,
	REDIRECTION_IN,
	REDIRECTION_OUT,
	HEREDOC,
	APPEND,
}					TokenType;

typedef struct s_token
{
	char			*value;
	TokenType		type;
	struct s_token	*next;
}					t_token;

typedef struct s_cmd
{
	char			**cmd_param;
	int				infile;
	int				outfile;
	pid_t			pid;
	bool			skip_cmd;
	struct s_cmd	*next;
}					t_cmd;

typedef struct s_env
{
	char			*name;
	char			*content;
	struct s_env	*next;
	struct s_env	*prev;
}					t_env;

typedef struct s_data
{
	char			*input;
	t_env			*env;
	t_env			*export;
	char			**envp;
	t_token			*token;
	int				token_count;
	int				last_status;
	t_cmd			*cmd;
	int				exit_code;
}					t_data;

typedef struct s_exec
{
	t_data			*data;
	t_cmd			*cmd;
	int				pipefd[2];
	int				prev_pipe;
	bool			is_first;
	bool			is_last;
}					t_exec;

void				child_process(t_data *data, t_cmd *cmd, int *pipefd);
static bool			is_directory(const char *path);
static int			check_cmd_path(char **path, char *cmd_name, t_data *data);
static int			resolve_cmd_path(char **path, char *cmd, t_data *data);
void				execution(t_data *data);
static void			init_execution(t_exec *ex, t_data *data);
static void			setup_pipes(t_exec *ex);
void				setup_redirections(t_cmd *cmd, int *pipefd, t_data *data);
static bool			is_directory(const char *path);

#endif