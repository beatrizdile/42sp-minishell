#include "minishell.h"

static int	token_len(char *token);
static void	save_token(int len, t_data *data, int index);
static int	is_metachar(char c);

// void	print_lex_and_token(t_data *data)
// {
// 	t_list	*temp;
// 	int		i;

// 	i = 0;
// 	temp = data->token;
// 	while (temp != NULL)
// 	{
// 		printf("token: %s    ", (char *)temp->content);
// 		printf("lex value: %d    ", data->lexer[i]);
// 		if (data->lexer[i] == 1)
// 			printf("type: %s\n", "INFILE");
// 		else if (data->lexer[i] == 2)
// 			printf("type: %s\n", "OUTFILE");
// 		else if (data->lexer[i] == 3)
// 			printf("type: %s\n", "HEREDOC");
// 		else if (data->lexer[i] == 4)
// 			printf("type: %s\n", "APPEND");
// 		else if (data->lexer[i] == 5)
// 			printf("type: %s\n", "PIPE");
// 		else if (data->lexer[i] == 6)
// 			printf("type: %s\n", "BUILTIN");
// 		else if (data->lexer[i] == 7)
// 			printf("type: %s\n", "CMD");
// 		else if (data->lexer[i] == 8)
// 			printf("type: %s\n", "ARG");
// 		temp = temp->next;
// 		i++;
// 	}
// }

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
	// print_lex_and_token(data);
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
