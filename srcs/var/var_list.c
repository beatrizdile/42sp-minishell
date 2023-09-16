#include "minishell.h"

void	new_var(t_data *data)
{
	if (find_var(data))
		change_value_in_var(data, find_var(data));
	else
		var_add_back(&data->var, set_var(data->prompt));
}

t_var	*find_var(t_data *data)
{
	t_var	*temp;
	char	**arr;

	if (data->var != NULL)
	{
		temp = data->var;
		while (temp != NULL)
		{
			arr = ft_split(data->prompt, '=');
			if (ft_strcmp(temp->key, arr[0]) == 0)
			{
				ft_free_str_arr(arr);
				return (temp);
			}
			ft_free_str_arr(arr);
			temp = temp->next;
		}
	}
	return (0);
}

void	change_value_in_var(t_data *data, t_var *node)
{
	char	**arr;

	arr = ft_split(data->prompt, '=');
	if (node->str)
		free(node->str);
	if (node->value)
		free(node->value);
	node->str = ft_copy_str(data->prompt);
	if (arr[1])
		node->value = ft_copy_str(arr[1]);
	else
		node->value = NULL;
	ft_free_str_arr(arr);
}

t_var	*set_var(char *str)
{
	t_var	*var;
	char	**arr;

	var = ft_calloc(1, sizeof(t_var));
	arr = ft_split(str, '=');
	var->str = ft_copy_str(str);
	var->key = ft_copy_str(arr[0]);
	if (arr[1])
		var->value = ft_copy_str(arr[1]);
	var->next = NULL;
	ft_free_str_arr(arr);
	return (var);
}

void	var_add_back(t_var **lst, t_var *new)
{
	t_var	*temp;

	if (!new)
		return ;
	if (!*lst)
		*lst = new;
	else
	{
		temp = *lst;
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = new;
	}
}
