#include "minishell.h"

static void	search_export(t_data *data, char *str);

void	export_builtin(t_data *data)
{
	char	**arr;
	int		i;

	i = 0;
	arr = ft_split(data->prompt, ' ');
	while (arr[i] != NULL)
	{
		search_export(data, arr[i]);
		free(arr[i]);
		i++;
	}
	free(arr);
}

static void	search_export(t_data *data, char *str)
{
	t_var	*temp;

	temp = data->var;
	while (temp)
	{
		if (ft_strcmp(temp->key, str) == 0)
		{
			ft_lstadd_back(&data->env, ft_lstnew(temp->str));
			break ;
		}
		temp = temp->next;
	}
}
