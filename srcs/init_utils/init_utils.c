#include "minishell.h"

void	copy_env(t_list **list, char **env, t_data *data)
{
	int	i;

	i = -1;
	while (env[++i] != NULL)
	{
		ft_lstadd_back(list, ft_lstnew(ft_strdup(env[i])));
		if (ft_strncmp(env[i], "HOME=", 5) == 0)
		{
			data->home = ft_calloc(1, ft_strlen(&env[i][5]) + 1);
			ft_strlcpy(data->home, &env[i][5], ft_strlen(&env[i][5]) + 1);
		}
	}
}

void	init_readline(t_data *data)
{
	while (true)
	{
		data->token = NULL;
		data->lexer = NULL;
		data->prompt = readline("\033[1;35mgibi>\033[0m ");
		if (data->prompt == NULL)
		{
			ft_putendl_fd("exit", 1);
			break ;
		}
		if (ft_strlen(data->prompt) >= 1)
		{
			add_history(data->prompt);
			if (tokenization(data) == 1 && check_for_quotes(data) == 1)
			{
				check_var(data);
				read_prompt(data->token, data->lexer, data);
			}
			if (data->lexer != NULL)
				free(data->lexer);
			if (data->token != NULL)
				free_list(data->token);
		}
		free(data->prompt);
	}
}

void	read_prompt(t_list *token, int *lexer, t_data *data)
{
	int		i;
	int		list_len;
	t_exec	exec;

	list_len = ft_lstsize(token);
	i = 0;
	exec.cmd = NULL;
	data->exec = &exec;
	data->cmd_count = 0;
	data->process_count = 1;
	while (token != NULL)
	{
		if (lexer[i] == PIPE)
			data->process_count++;
		if (lexer[i] == CMD || lexer[i] == BUILTIN)
			get_cmd_and_args(data, list_len, i, token);
		token = token->next;
		i++;
	}
	// t_exec *test = data->exec;
	// while (test != NULL)
	// {
	// 	int j = -1;
	// 	while (test->cmd[++j] != NULL)
	// 		printf("%s\n", test->cmd[j]);
	// 	printf("lex: %d\n", test->lex);
	// 	test = test->next;
	// }
	if (data->cmd_count != 0)
		execute(data, data->exec);
	if (data->cmd_count > 0)
		free_exec(data->exec);
}
