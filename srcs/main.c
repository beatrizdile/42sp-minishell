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
		data->env_copy = env_copy(envp);
		copy_env(&data->env, envp);
		init_readline(data);
		free_for_all(data);
	}
	return (0);
}

// export sem argumento lista as variaveis em ordem
// alfabetica e lista tembem as que nao tem conteudo

// exec exige um ponteiro de ponteiro para receber env,
// ou seja, transformar em array a lista linkada
