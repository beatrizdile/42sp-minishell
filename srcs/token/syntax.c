#include "minishell.h"

static int	syntax_aux(int *lexer, int index);

int	syntax_analysis(int *lexer, int len)
{
	int	i;

	i = -1;
	if (++i < len && len > 1)
		if (syntax_aux(lexer, i) == 0)
			return (0);
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
	return (1);
}

static int	syntax_aux(int *lexer, int index)
{
	if (is_redirect(lexer[index]) == 1 && lexer[index + 1] != ARG)
	{
		if (lexer[index + 1] == PIPE)
			ft_putendl_fd("syntax error near unexpected token `newline'", 2);
		else if (lexer[index + 1] == INFILE)
			ft_putendl_fd("syntax error near unexpected token '<'", 2);
		else if (lexer[index + 1] == OUTFILE)
			ft_putendl_fd("syntax error near unexpected token `>'", 2);
		else if (lexer[index + 1] == HEREDOC)
			ft_putendl_fd("syntax error near unexpected token `<<'", 2);
		else if (lexer[index + 1] == APPEND)
			ft_putendl_fd("syntax error near unexpected token `>>'", 2);
		return (0);
	}
	return (1);
}

int	is_redirect(int value)
{
	if (value == INFILE || value == OUTFILE
		|| value == HEREDOC || value == APPEND)
		return (1);
	return (0);
}
