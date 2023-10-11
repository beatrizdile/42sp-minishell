#include "minishell.h"

static int		is_redirect(int lex);
static t_exec	*create_cmd_arr(int *lex, t_list *token, int len);
static char		*copy_str(t_list *token);
static void		exec_addback(t_exec **exec, t_exec *node);

void	get_cmd_and_args(t_data *data, int len, int i, t_list *token)
{
	int	temp;
	int	start;

	data->cmd_count++;
	start = i;
	temp = i;
	i++;
	while (i < len && data->lexer[i] != PIPE)
	{
		if (is_redirect(data->lexer[i]) == 1)
		{
			i++;
			temp += 2;
		}
		i++;
	}
	len = i - temp;
	exec_addback(&data->exec, create_cmd_arr(&data->lexer[start], token, len));
}

static int	is_redirect(int lex)
{
	if (lex == INFILE)
		return (1);
	else if (lex == OUTFILE)
		return (1);
	else if (lex == HEREDOC)
		return (1);
	else if (lex == APPEND)
		return (1);
	return (0);
}

static t_exec	*create_cmd_arr(int *lex, t_list *token, int len)
{
	t_exec	*exec;
	int		i;
	int		j;

	exec = ft_calloc(sizeof(t_exec), 1);
	exec->lex = lex[0];
	exec->cmd = ft_calloc(sizeof(char *), len + 1);
	i = 0;
	j = 0;
	while (j < len)
	{
		if (is_redirect(lex[i]) == 0)
			exec->cmd[j++] = copy_str(token);
		else
		{
			i++;
			token = token->next;
		}
		i++;
		token = token->next;
	}
	exec->cmd[j] = NULL;
	return (exec);
}

static char	*copy_str(t_list *token)
{
	char	*cmd;

	cmd = ft_calloc(sizeof(char), ft_strlen(token->content) + 1);
	ft_strlcpy(cmd, token->content, ft_strlen(token->content) + 1);
	return (cmd);
}

void	exec_addback(t_exec **exec, t_exec *node)
{
	t_exec	*temp;

	temp = *exec;
	if (temp->cmd == NULL)
		*exec = node;
	else
	{
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = node;
	}
}
