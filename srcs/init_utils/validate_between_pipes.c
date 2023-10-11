#include "minishell.h"

void	validate_between_pipes(t_list *token, t_data *data, int i, int len)
{
	t_exec		exec;
	int			invalid_file;
	int			buffer;
	t_list		*temp;
	struct stat	file_info;

	exec.cmd = NULL;
	data->exec = &exec;
	while (token != NULL)
	{
		temp = token;
		buffer = i;
		while (data->lexer[i] != PIPE && token != NULL)
		{
			token = token->next;
			i++;
		}
		validate_files(temp, i - buffer);
		i++;
		token = token->next;
	}
}
