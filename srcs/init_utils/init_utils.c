#include "minishell.h"

void	copy_env(t_list **list, char **env)
{
	int	i;

	i = -1;
	while (env[++i] != NULL)
		ft_lstadd_back(list, ft_lstnew(ft_strdup(env[i])));
}

char	**env_copy(char **envp)
{
	char	**env;
	int		i;

	env = ft_calloc(sizeof(char *), ft_arrsize(envp) + 1);
	i = -1;
	while (envp[++i] != NULL)
		env[i] = ft_strdup(envp[i]);
	env[i] = NULL;
	return (env);
}

char	**save_path(char **envp)
{
	char	*start;
	char	**arr;

	arr = NULL;
	while (*envp)
	{
		start = ft_strnstr(*envp, "PATH=", 5);
		if (start != NULL)
		{
			start = ft_strtrim(start, "PATH=");
			arr = ft_split(start, ':');
			break ;
		}
		envp++;
	}
	free(start);
	return (arr);
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
		{
			add_history(data->prompt);
			if (tokenization(data) == 1)
			{
				// fix_input(data->token, data->var);
				read_prompt(data);
			}
			free_list(data->token);
			free(data->perline);
		}
		free(data->prompt);
	}
}

void	teste(t_data *data)
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
	// if (ft_strchr(data->prompt, '=') != NULL)
	// 	new_var(data);

	t_list	*temp;
	char	*str;
	char	*buff;

	temp = data->token;
	str = NULL;
	while (temp)
	{
		buff = ft_strdup(str);
		free(str);
		str = ft_strjoin(buff, temp->content);
		free(buff);
		if (temp->next != NULL)
		{
			buff = str;
			str = ft_strjoin(buff, " ");
			free(buff);
		}
		// printf("%s\n", (char *)temp->content);
		// printf("%s\n", (char *)str);
		temp = temp->next;
	}
	data->perline = str;

}
