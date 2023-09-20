/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcoqueir <gcoqueir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 07:47:27 by gcoqueir          #+#    #+#             */
/*   Updated: 2023/09/19 13:57:02 by gcoqueir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	child(int *fd, char *cmd, char **envp, t_pipex *pipex);

void	pipe_it(char *cmd, char **envp, t_pipex *pipex)
{
	int		fd[2];
	pid_t	pid;

	if (pipe(fd) == -1)
		error_check(4, pipex);
	pid = fork();
	if (pid == -1)
		error_check(4, pipex);
	if (pid == 0)
		child(fd, cmd, envp, pipex);
	else
	{
		dup2(fd[0], STDIN_FILENO);
		close(fd[1]);
		waitpid(pid, NULL, WNOHANG);
	}
}

static void	child(int *fd, char *cmd, char **envp, t_pipex *pipex)
{
	dup2(fd[1], STDOUT_FILENO);
	close(fd[0]);
	make_cmd(envp, cmd, pipex);
}

void	make_cmd(char **envp, char *command, t_pipex *pipex)
{
	int		i;

	pipex->cmd = ft_split(command, ' ');
	i = -1;
	while (pipex->cmd[++i] != NULL)
		pipex->cmd[i] = ft_strtrim(pipex->cmd[i], "'");
	if (ft_strchr(pipex->cmd[0], '/') != NULL)
		if (execve(pipex->cmd[0], pipex->cmd, envp) == -1)
			error_check(4, pipex);
	cmd_search(envp, pipex);
}

void	cmd_search(char **envp, t_pipex *pipex)
{
	int		i;
	char	*temp;

	i = -1;
	while (pipex->all_paths[++i] != NULL)
	{
		temp = ft_strjoin(pipex->all_paths[i], pipex->cmd[0]);
		if (access(temp, F_OK) == 0)
		{
			if (execve(temp, pipex->cmd, envp) == -1)
			{
				free(temp);
				error_check(4, pipex);
			}
		}
		free(temp);
	}
	if (pipex->all_paths[i] == NULL)
		error_check(3, pipex);
}
