#include "minishell.h"

int	main(int argc, char **argv, char **env)
{

	(void) argv;
	(void) env;
	if (argc != 1)
		return (0);
	init_readline();
	return (0);
}

void	init_readline(void)
{
	t_history	*history;
	char		*temp;

	history = ft_calloc(1, sizeof(t_history));
	int i = 0;
	while (i++ < 4)
	{
		temp = readline("$>");
		history_add_front(&history, history_new_node(temp));
		//free(temp->prompt);
	}
	while (--i > 0)
	{
		ft_printf("%s\n", history->prompt);
		history = history->next;
	}
}

// valgrind --suppressions=./local.supp --leak-check=full ./minishell