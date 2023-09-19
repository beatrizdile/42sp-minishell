#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_data	*data;

	(void)argv;
	if (argc == 1)
	{
		// signal(SIGINT, signal_handler);
		signal(SIGQUIT, SIG_IGN);
		data = ft_calloc(1, sizeof(t_data));
		data->path = save_path(envp);
		copy_env(&data->env, envp);
		init_readline(data);
		free_for_all(data);
	}
	return (0);
}

void	copy_env(t_list **list, char **env)
{
	int	i;

	i = -1;
	while (env[++i] != NULL)
		ft_lstadd_back(list, ft_lstnew(ft_strdup(env[i])));
}

void	init_readline(t_data *data)
{
	while (true)
	{
		data->token = NULL;
		data->lexer = NULL;
		data->prompt = readline("$> ");
		if (data->prompt == NULL)
		{
			ft_putendl_fd("exit", 1);
			break ;
		}
		if (ft_strlen(data->prompt) >= 1)
			add_history(data->prompt);
		tokenization(data);
		free_list(data->token);
		read_prompt(data);
		free(data->prompt);
	}
}

static void	teste(t_data *data)
{
	t_var	*temp;

	if (data->var == NULL)
	{
		printf("vazio\n");
	}
	else
	{
		temp = data->var;
		while (temp)
		{
			printf("str: %s\n", temp->str);
			printf("key: %s\n", temp->key);
			if (temp->value != NULL)
				printf("value: %s\n", temp->value);
			else
				printf("value: (null)\n");
			temp = temp->next;
		}
	}
}

void	read_prompt(t_data *data)
{
	if (ft_strcmp(data->prompt, "exit") == 0)
		exit_builtin(data);
	else if (ft_strcmp(data->prompt, "env") == 0)
		env_builtin(data);
	else if (ft_strcmp(data->prompt, "pwd") == 0)
		pwd_builtin();
	else if (ft_strncmp(data->prompt, "unset", 5) == 0)
		unset_builtin(data);
	else if (ft_strncmp(data->prompt, "export", 6) == 0)
		export_builtin(data);
	else if (ft_strcmp(data->prompt, "teste") == 0)
		teste(data);
	else if (ft_strchr(data->prompt, '=') != NULL)
		new_var(data);
}

// export sem argumento lista as variaveis em ordem
// alfabetica e lista tembem as que nao tem conteudo

// exec exige um ponteiro de ponteiro para receber env,
// ou seja, transformar em array a lista linkada
