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

t_list	*copy_env_list(t_list *env, t_list *lst)
{
	while (env != NULL)
	{
		ft_lstadd_back(&lst, ft_lstnew(env->content));
		env = env->next;
	}
	return (lst);
}
