#include "minishell.h"

static void	search_unset(t_data *data, char *arr);
// static void	ft_freenode(t_list *tmp);
static void	ft_freenode(t_list *node, t_list *list);

void	unset_builtin(t_data *data)
{
	char	**arr;
	int		i;

	i = 0;
	arr = ft_split(data->prompt, ' ');
	while (arr[i] != NULL)
	{
		search_unset(data, arr[i]);
		free(arr[i]);
		i++;
	}
	free(arr);
}

void	search_unset(t_data *data, char *arr)
{
	t_list	*tmp;

	tmp = data->env;
	while (tmp)
	{
		if (ft_strncmp((char *)tmp->content, arr, ft_strlen(arr)) == 0)
		{
			ft_freenode(tmp, data->env);
			break ;
		}
		tmp = tmp->next;
	}
}

static void	ft_freenode(t_list *node, t_list *list)
{
	t_list	*temp;

	temp = list;
	while (temp->next != node)
		temp = temp->next;
	temp->next = temp->next->next;
	free(node);
}
