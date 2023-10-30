#include "minishell.h"

void	echo_builtin(t_data *data, char **args)
{
	int	len;
	int	i;

	len = ft_arrsize(args);
	i = 1;
	if (len > 1)
	{
		if (ft_strcmp(args[i], "-n") == 0)
			i++;
		if (args[i] != NULL)
		{
			while (i < len - 1)
				printf("%s ", args[i++]);
			printf("%s", args[i]);
		}
		if (ft_strcmp(args[1], "-n") != 0)
			printf("\n");
	}
	else
		printf("\n");
	data->exit_status = 0;
}
