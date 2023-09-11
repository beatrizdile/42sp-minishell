#include "minishell.h"

void	exit_builtin(t_data *data)
{
	free_for_all(data);
	exit(0);
}

