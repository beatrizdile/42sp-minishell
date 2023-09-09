#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_data	data;

	(void) argv;
	if (argc == 1)
	{
		data.env = envp;
		data.path = save_path(envp);
		init_readline();
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

void	init_readline(void)
{
	char		*temp;

	int i = 0;
	while (i++ < 4)
	{
		temp = readline("$>");
		free(temp);
	}
}

// valgrind --suppressions=./local.supp --leak-check=full ./minishell