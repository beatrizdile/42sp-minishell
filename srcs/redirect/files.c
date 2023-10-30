#include "minishell.h"

static int	verify_if_file_exists(char *file);
static int	verify_permissions(int lex, char *file);
static int	open_redirect(int lex, char *file, int *fd_in, int *fd_out);

int	validate_files(t_list *token, int *lexer, int *fd_in, int *fd_out)
{
	t_list	*temp;
	int		i;
	int		result;

	*fd_in = -2;
	*fd_out = -2;
	i = -1;
	temp = token;
	while (temp->next != NULL && lexer[++i] != PIPE)
	{
		if (is_redirect(lexer[i]) == 1)
		{
			result = open_redirect(lexer[i], (char *)temp->next->content, fd_in,
					fd_out);
			if (result == 2)
				return (2);
			if (result == 3)
				return (3);
			if (result == 4)
				return (4);
		}
		temp = temp->next;
	}
	return (1);
}

static int	open_redirect(int lex, char *file, int *fd_in, int *fd_out)
{
	struct stat	file_info;

	if (stat(file, &file_info) == 0)
	{
		if (S_ISDIR(file_info.st_mode))
		{
			ft_printf_fd(2, "%s: Is a directory\n", file);
			return (4);
		}
	}
	if (lex == INFILE)
		*fd_in = open(file, O_RDONLY);
	else if (lex == OUTFILE)
		*fd_out = open(file, O_RDWR | O_TRUNC | O_CREAT, 0644);
	else if (lex == APPEND)
		*fd_out = open(file, O_RDWR | O_APPEND | O_CREAT, 0644);
	if (verify_if_file_exists(file) == 0)
		return (2);
	if (verify_permissions(lex, file) == 0)
		return (3);
	return (1);
}

static int	verify_if_file_exists(char *file)
{
	struct stat	file_info;

	if (stat(file, &file_info) != 0)
	{
		ft_printf_fd(2, "%s: No such file or directory\n", file);
		return (0);
	}
	return (1);
}

static int	verify_permissions(int lex, char *file)
{
	if (lex == OUTFILE || lex == APPEND)
	{
		if (access(file, W_OK) != 0)
		{
			ft_printf_fd(2, "%s: Permission denied\n", file);
			return (0);
		}
	}
	else
	{
		if (access(file, R_OK) != 0)
		{
			ft_printf_fd(2, "%s: Permission denied\n", file);
			return (0);
		}
	}
	return (1);
}

void	redirect_files(int fd_in, int fd_out)
{
	if (fd_in != -2)
		dup2(fd_in, 0);
	if (fd_out != -2)
		dup2(fd_out, 1);
}

void	close_files(int fd_in, int fd_out)
{
	if (fd_in != -2)
		close(fd_in);
	if (fd_out != -2)
		close(fd_out);
}
