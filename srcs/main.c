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
		copy_env(&data->env, envp, data);
		init_readline(data);
		free_for_all(data);
	}
	return (0);
}
