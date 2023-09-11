#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_data	*data;

	(void) argv;
	if (argc == 1)
	{
		data = ft_calloc(1, sizeof(t_data));
		data->env = envp;
		data->path = save_path(envp);
		init_readline(data);
		free_for_all(data);
	}
	return (0);
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
		data->temp = readline("$>");
		if (data->temp == NULL)
			break ;
		read_prompt(data);
		free(data->temp);
	}
}

void	read_prompt(t_data *data)
{
	if (ft_strncmp(data->temp, "exit", 4) == 0)
		exit_builtin(data);
	else if (ft_strncmp(data->temp, "env", 3) == 0)
		env_builtin(data);
	else if (ft_strncmp(data->temp, "pwd", 3) == 0)
		pwd_builtin();
}
