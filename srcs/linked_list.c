#include "minishell.h"

void	history_add_front(t_history **history, t_history *node)
{
	if (*history == NULL)
		*history = node;
	else
	{
		node->next = *history;
		*history = node;
	}
}

t_history	*history_new_node(char *content)
{
	t_history	*ptr;

	ptr = (t_history *)malloc(sizeof(t_history));
	if (!ptr)
		return (NULL);
	ptr->prompt = content;
	ptr->next = NULL;
	return (ptr);
}
