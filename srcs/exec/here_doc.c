/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcoqueir <gcoqueir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 09:27:34 by gcoqueir          #+#    #+#             */
/*   Updated: 2023/09/19 13:57:02 by gcoqueir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	here_doc_utils(int *fd, char *end_msg, t_pipex *pipex);
static char	*get_line(int fd);

void	here_doc(char *end_msg, t_pipex *pipex)
{
	pid_t	pid;
	int		fd[2];

	if (pipe(fd) == -1)
		error_check(4, pipex);
	pid = fork();
	if (pid == -1)
		error_check(4, pipex);
	if (pid == 0)
		here_doc_utils(fd, end_msg, pipex);
	else
	{
		dup2(fd[0], STDIN_FILENO);
		close(fd[1]);
		waitpid(pid, NULL, WNOHANG);
	}
}

static void	here_doc_utils(int *fd, char *end_msg, t_pipex *pipex)
{
	char	*temp;

	close(fd[0]);
	while (1)
	{
		temp = get_line(STDIN_FILENO);
		if (ft_strncmp(temp, end_msg, ft_strlen(end_msg)) == 0)
		{
			free(temp);
			close(pipex->outfile);
			exit(EXIT_SUCCESS);
		}
		ft_putstr_fd(temp, fd[1]);
		free(temp);
	}
}

static char	*get_line(int fd)
{
	char	*temp;
	char	*str;
	int		bytes_read;

	temp = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (temp == NULL)
		return (NULL);
	str = "\0";
	bytes_read = 1;
	while (ft_strchr(str, '\n') == NULL && bytes_read != 0)
	{
		bytes_read = read(fd, temp, BUFFER_SIZE);
		if (bytes_read < 0)
		{
			free (temp);
			return (NULL);
		}
		temp[bytes_read] = '\0';
		str = ft_strjoin(str, temp);
	}
	free(temp);
	return (str);
}
