#include "minishell.h"

void	pwd_builtin(t_data *data)
{
	char	*temp;

	temp = getcwd(NULL, 0);
	printf("%s\n", temp);
	free(temp);
	data->exit_status = 0;
}
