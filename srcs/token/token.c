/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bedos-sa <bedos-sa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 10:19:19 by bedos-sa          #+#    #+#             */
/*   Updated: 2023/11/01 10:19:20 by bedos-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	token_len(char *token);
static void	save_token(int len, t_data *data, int index);
static int	is_metachar(char c);

int	tokenization(t_data *data)
{
	int		i;
	int		len;

	i = 0;
	while (ft_strchr(BLANK, data->prompt[i]) != NULL && data->prompt[i] != '\0')
		i++;
	if (data->prompt[i] == '\0')
		return (0);
	i = -1;
	while (data->prompt[++i] != '\0')
	{
		while (ft_strchr(BLANK, data->prompt[i]) != NULL
			&& data->prompt[i] != '\0')
			i++;
		if (data->prompt[i] == '\0')
			break ;
		len = token_len(&data->prompt[i]);
		save_token(len, data, i);
		i += len - 1;
	}
	if (lex_analysis(data) == 0)
		return (0);
	return (1);
}

static int	token_len(char *token)
{
	int	i;
	int	quoted;
	int	metachar;

	metachar = is_metachar(token[0]);
	quoted = is_quoted(token[0], 0);
	i = 0;
	while (token[++i] != '\0')
	{
		if (metachar == 1)
		{
			if (token[i] == token[i - 1])
				return (2);
			return (1);
		}
		else if (quoted == 0)
		{
			if (token[i] == ' ' || is_metachar(token[i]) == 1)
				return (i);
			quoted = is_quoted(token[i], quoted);
		}
		else
			quoted = is_quoted(token[i], quoted);
	}
	return (i);
}

static void	save_token(int len, t_data *data, int index)
{
	char	*temp;

	temp = ft_calloc((len + 1), sizeof(char));
	ft_strlcpy(temp, &data->prompt[index], len + 1);
	ft_lstadd_back(&data->token, ft_lstnew(ft_strdup(temp)));
	free(temp);
}

int	is_quoted(char c, int identifier)
{
	if (identifier == 0)
	{
		if (c == S_QUOTE)
			return (1);
		else if (c == D_QUOTES)
			return (2);
	}
	else if (identifier == 1)
	{
		if (c != S_QUOTE)
			return (1);
	}
	else if (identifier == 2)
	{
		if (c != D_QUOTES)
			return (2);
	}
	return (0);
}

static int	is_metachar(char c)
{
	if (ft_strchr(METACHAR, c) == NULL)
		return (0);
	return (1);
}
