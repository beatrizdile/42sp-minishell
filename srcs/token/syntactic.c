#include "minishell.h"

static int	is_redirect(int value);

int	syntax_analysis(int *lexer, int len)
{
	int	i;

	if (lexer[0] == PIPE || lexer[len - 1] == PIPE)
	{
		ft_putendl_fd("syntax error near unexpected token `|'", 2);
		return (0);
	}
	if (is_redirect(lexer[len - 1]) == 1)
	{
		ft_putendl_fd("syntax error near unexpected token `newline'", 2);
		return (0);
	}
	i = -1;
	if (++i < len)
	{
		if (is_redirect(lexer[i]) == 1 || lexer[i + 1] != ARG)
			return (0);
	}
	return (1);
}

static int	is_redirect(int value)
{
	if (value == INFILE || value == OUTFILE
		|| value == HEREDOC || value == APPEND)
		return (1);
	return (0);
}
