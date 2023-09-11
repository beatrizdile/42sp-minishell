#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_data	data;

	(void) argv;
	if (argc == 1)
	{
		data.env = envp;
		data.path = save_path(envp);
		init_readline(data);
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

void	init_readline(t_data data)
{
	char		*temp;

	while (true)
	{
		temp = readline("$>");
		if (ft_strncmp(temp, "exit", 4) == 0)
		{
			free(temp);
			exit_builtin(data);
		}
		free(temp);
	}
}
