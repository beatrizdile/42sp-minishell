#include "minishell.h"

void	free_for_all(t_data	*data)
{
	rl_clear_history();
	ft_free_str_arr(data->path);
	if (data->env != NULL)
		free_list(data->env);
	if (data->prompt != NULL)
		free(data->prompt);
	if (data->var != NULL)
		free_var_list(data->var);
	free(data);
}

void	free_list(t_list *list)
{
	t_list	*prompt;

	prompt = list;
	while (prompt != NULL)
	{
		list = list->next;
		free(prompt);
		prompt = list;
	}
}

void	free_var_list(t_var *var)
{
	t_var	*temp;

	temp = var;
	while (temp != NULL)
	{
		var = var->next;
		free(temp->str);
		free(temp->key);
		free(temp->value);
		free(temp);
		temp = var;
	}
}
