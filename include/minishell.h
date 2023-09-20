#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <readline/history.h>
# include <readline/readline.h>
# include <stdio.h>
# include <signal.h>
# include <errno.h>
# include <string.h>
# include <sys/wait.h>

/* Characteres */
# define METACHAR "<>| "
# define BLANK "\t\n\v\f\r "
# define S_QUOTE '\''
# define D_QUOTES '\"'

/* Error defines */
# define SUCCESS 0
# define FAILURE 1
# define ERRBUILTIN 2
# define ERRCMD_NOTEXEC 126
# define ERRCMD_NOTFOUNT 127
# define ERR_INVALIDARG 128
# define ERR_CTRLC 130

/* Lexer */
enum e_lexeme
{
	INFILE = 1,
	OUTFILE,
	HEREDOC,
	APPEND,
	PIPE,
	BUILTIN,
	CMD,
	ARG
};

typedef struct s_var
{
	char			*str;
	char			*key;
	char			*value;
	struct s_var	*next;
}	t_var;

typedef struct s_pipex
{
	int		infile;
	int		outfile;
	char	**cmd;
	char	**all_paths;
}			t_pipex;

typedef struct s_data
{
	char	*prompt;
	char	*perline;
	char	**path;
	char	**env_copy;
	t_list	*env;
	t_var	*var;
	t_list	*token;
	int		*lexer;
}			t_data;

/* Init */
void	copy_env(t_list **list, char **env);
char 	**env_copy(char **envp);
char	**save_path(char **envp);
void	init_readline(t_data *data);
void	read_prompt(t_data *data);

/* Free */
void	free_for_all(t_data *data);
void	free_list(t_list *list);
void	free_var_list(t_var *var);

/* Builtin */
void	exit_builtin(t_data *data);
void	env_builtin(t_data *data);
void	pwd_builtin(void);
void	unset_builtin(t_data *data);
void	export_builtin(t_data *data);

/* Builtin Utils */
t_list	*copy_env_list(t_list *env, t_list *lst);

/* Signal */
void	signal_handler(int signal);
void	signal_ignore(void);
void	signal_default(void);

/* Var */
t_var	*set_var(char *str);
void	new_var(t_data *data);
void	var_add_back(t_var **lst, t_var *new);
t_list	*find_env(t_data *data);
t_var	*find_var(t_data *data);
void	change_value_in_env(t_data *data, t_list *node);
void	change_value_in_var(t_data *data, t_var *node);

/* Token and syntax*/
int		tokenization(t_data *data);
int		lex_analysis(t_data *data);
int		syntax_analysis(int *lexer, int len);
int		is_quoted(char c, int identifier);

/* Fix input */
void	fix_input(t_list *token, t_var *var);

/* Exec */
void	pipex(int argc, char **argv, char **envp);
void	make_cmd(char **envp, char *command, t_pipex *pipex);
void	cmd_search(char **envp, t_pipex *pipex);
void	free_tab(char **tab);
void	error_check(int i, t_pipex *pipex);
void	pipe_it(char *cmd, char **envp, t_pipex *pipex);
void	here_doc(char *end_msg, t_pipex *pipex);

#endif