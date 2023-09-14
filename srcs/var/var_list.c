#include "minishell.h"

char	*ft_copy_str(char *copy)
{
	char	*str;
	int		i;

	str = ft_calloc(1, ft_strlen(copy) + 1);
	i = 0;
	while (copy[i])
	{
		str[i] = copy[i];
		i++;
	}
	return (str);
}

t_var	*set_var(char *str)
{
	t_var	*var;
	char	**arr;

	var = ft_calloc(1, sizeof(t_var));
	arr = ft_split(str, '=');
	var->str = ft_copy_str(str);
	var->key = ft_copy_str(arr[0]);
	var->value = ft_copy_str(arr[1]);
	var->next = NULL;
	free_str_arrs(arr);
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

// void	new_var(t_data *data)
// {
// 	if (check_arg_in_var(data->prompt))
// 		change_value_in_var();
// 	else
		
// }
