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
void	free_list(t_list *list);
void	free_var_list(t_var *var);

/* Builtin */
void	exit_builtin(t_data *data);
void	env_builtin(t_data *data);
void	pwd_builtin(void);
void	unset_builtin(t_data *data);
void	export_builtin(t_data *data);

/* Builtin Utils*/
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

#endif