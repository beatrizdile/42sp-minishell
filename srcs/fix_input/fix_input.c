/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fix_input.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bedos-sa <bedos-sa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 10:19:51 by bedos-sa          #+#    #+#             */
/*   Updated: 2023/11/01 10:20:04 by bedos-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*replace_to_value(char *str, char *key, char *value);
static char	*search_var(t_list *env, char *temp, char *new);

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

char	*check_var_heredoc(char *str, t_data *data)
{
	int		i;
	int		buffer;
	char	*temp;
	char	*new;

	i = -1;
	new = ft_strdup(str);
	while (new[++i] != '\0')
	{
		if (new[i] == '$')
		{
			buffer = i + 1;
			while (str[buffer] != '\0' && ft_strchr(VAR_BLOCK, str[buffer])
				== NULL)
				buffer++;
			temp = get_key(str, i, buffer);
			new = search_var(data->env, temp, new);
			if (new[i] == '\0')
				break ;
		}
	}
	free(str);
	return (new);
}

static char	*search_var(t_list *env, char *temp, char *new)
{
	while (env != NULL)
	{
		if (ft_strncmp(temp, env->content, ft_strlen(temp)) == 0)
		{
			new = replace_to_value(new, temp,
					(char *)&env->content[ft_strlen(temp)]);
			break ;
		}
		if (env->next == NULL)
			new = replace_to_value(new, temp, "");
		env = env->next;
	}
	return (new);
}

static char	*replace_to_value(char *str, char *key, char *value)
{
	char	*new;
	int		i;
	int		j;
	int		k;

	new = ft_calloc(ft_strlen(str) - ft_strlen(key) + ft_strlen(value) + 1, 1);
	i = -1;
	while (str[++i] != '$' && str[i] != '\0')
		new[i] = str[i];
	k = i + ft_strlen(key);
	j = 0;
	while (value[j] != '\0')
		new[i++] = value[j++];
	while (str[k] != '\0')
		new[i++] = str[k++];
	new[i] = '\0';
	free(key);
	free(str);
	return (new);
}
