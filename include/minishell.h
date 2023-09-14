#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <readline/history.h>
# include <readline/readline.h>
# include <stdio.h>
# include <signal.h>

/* Error defines */
# define SUCCESS 0
# define FAILURE 1
# define ERRBUILTIN 2
# define ERRCMD_NOTEXEC 126
# define ERRCMD_NOTFOUNT 127
# define ERR_INVALIDARG 128
# define ERR_CTRLC 130

/* Token */
enum e_token_types {
	SPC = 1,
	PIPE,
	VAR,
	CMD,
	BUILTIN,
	WORD,
	HEREDOC,
	APPEND,
	INFILE,
	OUTFILE
};

typedef struct s_var
{
	char			*str;
	char			*key;
	char			*value;
	struct s_var	*next;
}	t_var;

typedef struct s_data
{
	char	*prompt;
	char	**path;
	t_list	*env;
	t_var	*var;
}			t_data;

/* Main */
void	read_prompt(t_data *data);
void	copy_env(t_list **list, char **env);
char	**save_path(char **envp);
void	init_readline(t_data *data);

/* Free */
void	free_for_all(t_data *data);
void	free_str_arrs(char **arr);
void	free_list(t_list *list);
void	free_var_list(t_var *var);

/* Builtin */
void	exit_builtin(t_data *data);
void	env_builtin(t_data *data);
void	pwd_builtin(void);
void	unset_builtin(t_data *data);
void	export_builtin(t_data *data);

/* Signal */
void	signal_handler(int signal);
void	signal_ignore(void);
void	signal_default(void);

t_var	*set_var(char *str);
// void	init_var_list(char **env, t_data *data);
void	var_add_back(t_var **lst, t_var *new);

#endif