#include "minishell.h"

static int	lexeme(char *token, t_data *data, int index);
static int	is_builtin(char *token);
static int	get_pos(int *lexer, int index);
// static int	is_cmd(char *token, char **path);

int	lex_analysis(t_data *data)
{
	t_list	*temp;
	int		i;

	data->lexer = ft_calloc(ft_lstsize(data->token), sizeof(int));
	temp = data->token;
	i = 0;
	while (temp != NULL)
	{
		data->lexer[i] = lexeme(temp->content, data, i);
		temp = temp->next;
		i++;
	}
	if (syntax_analysis(data->lexer, ft_lstsize(data->token)) == 0)
		return (0);
	return (1);
}

static int	lexeme(char *token, t_data *data, int index)
{
	if (ft_strlen(token) == 1)
	{
		if (token[0] == '<')
			return (INFILE);
		else if (token[0] == '>')
			return (OUTFILE);
		else if (token[0] == '|')
			return (PIPE);
	}
	if (ft_strlen(token) == 2)
	{
		if (token[0] == '<')
			return (HEREDOC);
		else if (token[0] == '>')
			return (APPEND);
	}
	if (get_pos(data->lexer, index) == 1 && is_builtin(token) == 1)
		return (BUILTIN);
	else if (get_pos(data->lexer, index) == 1 && ft_strchr(token, '=') == NULL)
		return (CMD);
	return (ARG);
}

static int	get_pos(int *lexer, int index)
{
	if (index == 0)
		return (1);
	if (lexer[index - 1] == PIPE)
		return (1);
	if (index - 2 >= 0)
	{
		if (lexer[index - 2] == HEREDOC)
			return (1);
		if (lexer[index - 2] == INFILE)
			return (1);
		if (lexer[index - 2] == OUTFILE)
			return (1);
		if (lexer[index - 2] == APPEND)
			return (1);
	}
	return (0);
}

static int	is_builtin(char *token)
{
	if ((ft_strcmp(token, "echo") == 0))
		return (1);
	if ((ft_strcmp(token, "cd") == 0))
		return (1);
	if ((ft_strcmp(token, "pwd") == 0))
		return (1);
	if ((ft_strcmp(token, "export") == 0))
		return (1);
	if ((ft_strcmp(token, "unset") == 0))
		return (1);
	if ((ft_strcmp(token, "env") == 0))
		return (1);
	if ((ft_strcmp(token, "exit") == 0))
		return (1);
	return (0);
}

// char	*make_tokens_str(t_list *token)
// {
// 	if ()
// }

// static int	is_cmd(char *token, char **path)
// {
// 	int		i;
// 	char	*temp;
// 	char	*buffer;

// 	if (access(token, X_OK) == 0)
// 		return (1);
// 	i = -1;
// 	while (path[++i] != NULL)
// 	{
// 		buffer = ft_strjoin("/", token);
// 		temp = ft_strjoin(path[i], buffer);

// 		printf("%s\n", temp);
// 		if (access(temp, X_OK) == 0)
// 		{
// 			free(temp);
// 			free(buffer);
// 			return (1);
// 		}
// 		free(temp);
// 		free(buffer);
// 	}
// 	return (0);
// }
