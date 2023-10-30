#include "minishell.h"

static char	*expand_var(char *str, int index, t_list *env);
static char	*get_key(char *str, int start, int end);
static char	*change_to_value(int index, char *str, char *value);
static char	*complete_newstr(char *str, char *temp, size_t start, size_t end);

char	*search_and_expand_var(char *str, t_data *data)
{
	int	quoted;
	int	i;

	quoted = 0;
	i = -1;
	while (str[++i] != '\0')
	{
		quoted = is_quoted(str[i], quoted);
		if (quoted == 0 && (str[i] == '$' && str[i + 1] != '\0'
				&& str[i + 1] != ' ' && str[i + 1] != '$'))
		{
			if (str[i + 1] == '?')
				str = expand_exit_status(str, i, data->exit_status);
			else
				str = expand_var(str, i, data->env);
		}
		else if (quoted == 2 && (str[i] == '$' && str[i + 1] != '\0'
				&& ft_strchr(VAR_STOPER, str[i + 1]) == NULL))
		{
			if (str[i + 1] == '?')
				str = expand_exit_status(str, i, data->exit_status);
			else
				str = expand_var(str, i, data->env);
		}
		if (str[0] == '\0')
			break ;
	}
	return (str);
}

static char	*expand_var(char *str, int index, t_list *env)
{
	char	*new;
	char	*temp;
	int		i;

	i = index + 1;
	while (ft_strchr(VAR_STOPER, str[i]) == NULL && str[i] != '\0')
		i++;
	temp = get_key(str, index, i);
	while (env != NULL)
	{
		if (ft_strncmp(temp, env->content, ft_strlen(temp)) == 0)
		{
			temp = change_to_value(ft_strlen(temp), temp, (char *)env->content);
			break ;
		}
		env = env->next;
	}
	if (env == NULL)
		new = complete_newstr(str, "", index, i);
	else
		new = complete_newstr(str, temp, index, i);
	free(str);
	free(temp);
	return (new);
}

static char	*get_key(char *str, int start, int end)
{
	char	*temp;

	temp = ft_calloc((end - (start + 1)) + 2, 1);
	ft_strlcpy(temp, &str[start + 1], (end - (start + 1)) + 1);
	temp[end - (start + 1)] = '=';
	temp[end - (start + 1) + 1] = '\0';
	return (temp);
}

static char	*change_to_value(int index, char *str, char *value)
{
	char	*temp;
	int		i;

	free(str);
	i = 0;
	temp = ft_calloc(1, ft_strlen(value) - index + 1);
	while (value[index] != '\0')
		temp[i++] = value[index++];
	temp[i] = '\0';
	return (temp);
}

static char	*complete_newstr(char *str, char *temp, size_t start, size_t end)
{
	size_t	i;
	size_t	j;
	size_t	k;
	size_t	len;
	char	*new;

	len = (ft_strlen(str) - (end - (start + 1))) + ft_strlen(temp);
	if (len == 1)
		return (ft_strdup(""));
	new = ft_calloc((ft_strlen(str) - (end - (start + 1)))
			+ ft_strlen(temp), 1);
	i = -1;
	while (++i < start)
		new[i] = str[i];
	j = 0;
	while (i < ft_strlen(temp) + start)
		new[i++] = temp[j++];
	k = end;
	while (str[k] != '\0')
		new[i++] = str[k++];
	new[i] = '\0';
	return (new);
}
