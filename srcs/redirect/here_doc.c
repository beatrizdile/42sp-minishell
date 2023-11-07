/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcoqueir <gcoqueir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 10:20:21 by bedos-sa          #+#    #+#             */
/*   Updated: 2023/11/01 13:47:49 by gcoqueir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	open_heredoc(t_data *data, int size);
static int	open_file(char *file);
static void	write_on_heredoc(int fd, char *end_msg, t_data *data);

int	check_heredoc(t_data *data)
{
	int		i;
	int		size;
	t_list	*temp;

	i = -1;
	size = 0;
	temp = data->token;
	while (temp != NULL)
	{
		if (data->lexer[++i] == HEREDOC)
			size++;
		temp = temp->next;
	}
	if (size > 0)
		if (open_heredoc(data, size) == 0)
			return (0);
	if (*get_heredoc_flag() == 1)
	{
		data->exit_status = 130;
		return (0);
	}
	return (1);
}

static int	open_heredoc(t_data *data, int size)
{
	t_list	*temp;
	int		i;
	int		index;
	int		backup;

	data->fd_heredoc = ft_calloc(sizeof(int), size);
	temp = data->token;
	i = -1;
	index = 0;
	while (temp != NULL)
	{
		backup = dup(0);
		if (data->lexer[++i] == HEREDOC)
		{
			data->fd_heredoc[index] = open_file((char *)temp->next->content);
			if (data->fd_heredoc[index] == -1)
				return (0);
			write_on_heredoc(data->fd_heredoc[index],
				(char *)temp->next->content, data);
			close(data->fd_heredoc[index++]);
		}
		dup2(backup, 0);
		temp = temp->next;
	}
	return (1);
}

static int	open_file(char *file)
{
	int		fd;
	char	*temp;

	temp = ft_strjoin("/tmp/", file);
	fd = open(temp, O_WRONLY | O_TRUNC | O_CREAT, 0644);
	free(temp);
	if (fd < 0)
		return (-1);
	return (fd);
}

static void	write_on_heredoc(int fd, char *end_msg, t_data *data)
{
	char	*temp;

	while (true)
	{
		signal(SIGINT, sigint_heredoc);
		signal(SIGQUIT, SIG_IGN);
		temp = readline("> ");
		if (temp == NULL)
		{
			ft_putchar_fd('\n', 1);
			break ;
		}
		if (ft_strcmp(temp, end_msg) == 0)
		{
			free(temp);
			break ;
		}
		temp = check_var_heredoc(temp, data);
		ft_putendl_fd(temp, fd);
		free(temp);
	}
}
