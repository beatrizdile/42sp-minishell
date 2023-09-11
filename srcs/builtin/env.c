#include "minishell.h"

void	env_builtin(t_data *data)
{
	int i;

	i = -1;
	while (data->env[++i] != NULL)
		printf("%s\n", data->env[i]);
}
