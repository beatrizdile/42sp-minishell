/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   finally_execute.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcoqueir <gcoqueir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 10:20:40 by bedos-sa          #+#    #+#             */
/*   Updated: 2023/11/01 14:04:08 by gcoqueir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**turn_env_to_arr(t_list *env);
static char	**find_path(char **env);
static int	try_paths(t_exec *exec, char **path, char **env);

void	finally_execute(t_data *data, int fd[], pid_t *pids)
{
	char	**env;
	char	**path;
	int		backup_exit_status;
	int		result;

	if (data->exec->lex == CMD)
	{
		env = turn_env_to_arr(data->env);
		path = find_path(env);
		result = try_paths(data->exec, path, env);
		close_files(fd[0], fd[1]);
		if (result == 127)
			ft_printf_fd(2, "%s: command not found\n", data->exec->cmd[0]);
		else
			ft_printf_fd(2, "%s: permission denied\n", data->exec->cmd[0]);
		free_cmd_not_found(path, env, data, pids);
		exit(result);
	}
	execute_builtin(data, data->exec, pids);
	close_files(fd[0], fd[1]);
	backup_exit_status = data->exit_status;
	free_builtin(data, pids);
	exit(backup_exit_status);
}

static char	**turn_env_to_arr(t_list *env)
{
	char	**arr;
	int		i;

	arr = ft_calloc(sizeof(char *), ft_lstsize(env) + 1);
	i = 0;
	while (env != NULL)
	{
		arr[i] = ft_calloc(sizeof(char), ft_strlen(env->content) + 1);
		ft_strlcpy(arr[i], env->content, ft_strlen(env->content) + 1);
		env = env->next;
		i++;
	}
	arr[i] = NULL;
	return (arr);
}

static char	**find_path(char **env)
{
	int		i;
	char	**temp;
	char	**paths;

	i = 0;
	while (env[i] != NULL && ft_strncmp("PATH=", env[i], 5) != 0)
		i++;
	if (env[i] == NULL)
		return (NULL);
	temp = ft_split(&env[i][5], ':');
	i = 0;
	while (temp[i] != NULL)
		i++;
	paths = ft_calloc(sizeof(char *), (i + 1));
	i = -1;
	while (temp[++i] != NULL)
		paths[i] = ft_strjoin(temp[i], "/");
	paths[i] = NULL;
	ft_free_str_arr(&temp);
	return (paths);
}

static int	try_paths(t_exec *exec, char **path, char **env)
{
	int		i;
	int		strlen;
	char	*copy;

	if (verify(access(exec->cmd[0], F_OK), exec->cmd[0], exec->cmd, env) == 0)
		return (126);
	i = -1;
	if (path != NULL)
	{
		while (path[++i])
		{
			strlen = ft_strlen(path[i]) + ft_strlen(exec->cmd[0]) + 1;
			copy = ft_calloc(strlen, sizeof(char));
			ft_strlcat(copy, path[i], strlen);
			ft_strlcat(copy, exec->cmd[0], strlen);
			if (access(copy, F_OK) == 0)
			{
				verify_permission(copy, exec->cmd, env);
				free(copy);
				return (126);
			}
			free(copy);
		}
	}
	return (127);
}

void	verify_permission(char *copy, char **cmd, char **env)
{
	if (access(copy, X_OK) == 0)
		execve(copy, cmd, env);
}
