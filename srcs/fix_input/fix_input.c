#include "minishell.h"

static char	*expand_var(char *str, int index, t_var *var, int quoted);
static char	*change_to_value(char *str, char *value);
static char	*complete_newstr(char *str, char *temp, size_t start, size_t end);

void	fix_input(t_list *token, t_var *var)
{
	t_list	*temp;
	char	*str;
	int		quoted;
	int		i;

	temp = token;
	while (temp != NULL)
	{
		str = ft_strdup((char *)temp->content);
		quoted = is_quoted(str[0], 0);
		i = -1;
		while (str[++i] != '\0')
		{
			if ((quoted == 0 && str[i] == '$' && str[i + 1] != '\0'
					&& str[i + 1] != ' ') || (quoted == 2 && str[i] == '$'
					&& str[i + 1] != D_QUOTES && str[i + 1] != ' '))
				str = expand_var(str, i, var, quoted);
		}
		free(temp->content);
		temp->content = ft_strdup(str);
		free(str);
		temp = temp->next;
	}
}

static char	*expand_var(char *str, int index, t_var *var, int quoted)
{
	char	*new;
	char	*temp;
	int		i;

	new = NULL;
	i = index + 1;
	if (quoted == 0)
		while (str[i] != ' ' && str[i] != '\0')
			i++;
	if (quoted == 2)
		while (str[i] != ' ' && str[i] != D_QUOTES)
			i++;
	temp = ft_calloc((i - (index + 1)) + 1, 1);
	ft_strlcpy(temp, &str[index + 1], (i - (index + 1)) + 1);
	while (var != NULL)
	{
		if (ft_strcmp(temp, var->key) == 0)
		{
			temp = change_to_value(temp, var->value);
			break ;
		}
		var = var->next;
	}
	new = complete_newstr(str, temp, index, i);
	free(temp);
	// printf("%s\n", new);
	return (new);
}

static char	*change_to_value(char *str, char *value)
{
	char	*temp;

	free(str);
	temp = ft_strdup(value);
	return (temp);
}

static char	*complete_newstr(char *str, char *temp, size_t start, size_t end)
{
	size_t	i;
	size_t	j;
	size_t	k;
	char	*new;

	// if ()
	new = ft_calloc((ft_strlen(str) - (end - (start + 1)))
			+ ft_strlen(temp), 1);
	i = -1;
	while (++i < start)
		new[i] = str[i];
	j = 0;
	while (i < ft_strlen(temp) + start)
		new[i++] = temp[j++];
	k = end + 1;
	while (str[k] != '\0')
		new[i++] = str[k++];
	new[i] = '\0';
	return (new);
}
