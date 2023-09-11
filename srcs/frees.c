#include "minishell.h"

void	free_for_all(t_data	data)
{
	free_str_arrs(data.path);
}

void	free_str_arrs(char **arr)
{
	int	j;

	j = 0;
	while (arr[j])
	{
		free(arr[j]);
		j++;
	}
	free(arr);
}

void	free_list(t_list *list)
{
	t_list	*temp;

	temp = list;
	while (temp != NULL)
	{
		list = list->next;
		free(temp);
		temp = list;
	}
}