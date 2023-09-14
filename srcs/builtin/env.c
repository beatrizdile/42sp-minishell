#include "minishell.h"

void	env_builtin(t_data *data)
{
	t_list	*temp;

	temp = data->env;
	while (temp != NULL)
	{
		printf("%s\n", (char *)temp->content);
		temp = temp->next;
	}
}
