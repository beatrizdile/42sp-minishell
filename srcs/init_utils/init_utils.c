#include "minishell.h"

static void	read_prompt(t_data *data);

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
		// signal(SIGINT, sigint_handler);
		signal(SIGQUIT, SIG_IGN);
		data->token = NULL;
		data->lexer = NULL;
		data->prompt = readline("\001\033[1;35m\002gibi>\001\033[0m\002 ");
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
				read_prompt(data);
			}
			if (data->lexer != NULL)
				free(data->lexer);
			if (data->token != NULL)
				free_list(data->token);
		}
		free(data->prompt);
	}
}

static void	read_prompt(t_data *data)
{
	int		i;
	t_list	*temp;

	// if (check_heredoc(data) == 1)
	// {
		i = -1;
		data->process_count = 1;
		data->builtin_check = 0;
		temp = data->token;
		while (temp != NULL)
		{
			if (data->lexer[++i] == PIPE)
				data->process_count++;
			if (data->process_count == 1 && data->lexer[i] == BUILTIN)
				data->builtin_check = 1;
			temp = temp->next;
		}
		execute(data);
	// }
}
