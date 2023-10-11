#include "minishell.h"

static char	*remove_quote(char *str, int index);

int	check_for_quotes(t_data *data)
{
	t_list	*temp;
	char	*str;
	int		i;
	int		quoted;

	temp = ft_lstlast(data->token);
	str = ft_strdup((char *)data->token->content);
	i = -1;
	quoted = 0;
	while (str[++i] != '\0')
		quoted = is_quoted(str[i], quoted);
	free(str);
	if (quoted != 0)
	{
		ft_putendl_fd("prompt: non-closed quotes", 2);
		data->exit_status = 2;
		return (0);
	}
	return (1);
}

char	*search_and_remove_quotes(char *str)
{
	int	i;
	int	quoted;

	i = -1;
	quoted = 0;
	while (str[++i] != '\0')
	{
		quoted = is_quoted(str[i], quoted);
		if ((quoted == 2 || quoted == 0) && str[i] == D_QUOTES)
		{
			str = remove_quote(str, i);
			i--;
		}
		else if ((quoted == 1 || quoted == 0) && str[i] == S_QUOTE)
		{
			str = remove_quote(str, i);
			i--;
		}
	}
	return (str);
}

static char	*remove_quote(char *str, int index)
{
	char	*temp;
	int		i;
	int		j;

	temp = ft_calloc(1, ft_strlen(str));
	i = 0;
	j = 0;
	while (str[i] != '\0')
	{
		if (i == index)
			i++;
		temp[j] = str[i];
		if (str[i] == '\0')
			break ;
		j++;
		i++;
	}
	free(str);
	return (temp);
}
