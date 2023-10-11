#include "minishell.h"

void	check_var(t_data *data)
{
	t_list	*temp;
	char	*str;

	temp = data->token;
	while (temp != NULL)
	{
		str = ft_strdup((char *)temp->content);
		str = search_and_expand_var(str, data);
		free(temp->content);
		temp->content = ft_strdup(str);
		free(str);
		temp = temp->next;
	}
	temp = data->token;
	check_tildes(temp, data->home);
	temp = data->token;
	while (temp != NULL)
	{
		str = ft_strdup((char *)temp->content);
		str = search_and_remove_quotes(str);
		free(temp->content);
		temp->content = ft_strdup(str);
		free(str);
		temp = temp->next;
	}
}
