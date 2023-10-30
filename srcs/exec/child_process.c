#include "minishell.h"

static char	**turn_env_to_arr(t_list *env);
static char	**find_path(char **env);
static void	try_paths(t_exec *exec, char **path, char **env);

void	child_process(t_data *data, t_list *token, int *lexer, pid_t *pids)
{
	char		**path;
	char		**env;
	int			fd[2];
	int			backup_exit_status;
	int			result;

	result = validate_files(token, lexer, &fd[0], &fd[1]);
	if (result == 1)
	{
		get_cmd_and_args(token, lexer, data);
		if (data->process_count > 1)
		{
			if (data->args->index == data->process_count - 1)
				last_command(data->args);
			else if (data->args->index == 0)
				first_command(data->args);
			else
				middle_command(data->args);
		}
		close_pipes(data->args);
		if (fd[0] != -2 || fd[1] != -2)
			redirect_files(fd[0], fd[1]);
		if (data->has_builtin == 1 || data->has_cmd == 1)
		{
			if (data->exec->lex == CMD)
			{
				env = turn_env_to_arr(data->env);
				path = find_path(env);
				try_paths(data->exec, path, env);
				close_files(fd[0], fd[1]);
				free_cmd_not_found(path, env, data, pids);
				exit(127);
			}
			execute_builtin(data, data->exec, pids);
			close_files(fd[0], fd[1]);
			backup_exit_status = data->exit_status;
			free_builtin(data, pids);
			exit(backup_exit_status);
		}
	}
	else if (result == 2 || result == 4)
		data->exit_status = 1;
	else if (result == 3)
		data->exit_status = 126;
	close_files(fd[0], fd[1]);
	free(pids);
	free_for_all(data);
	exit(1);
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

static void	try_paths(t_exec *exec, char **path, char **env)
{
	int			i;
	int			strlen;
	char		*copy;

	if (access(exec->cmd[0], F_OK) == 0)
		execve(exec->cmd[0], exec->cmd, env);
	i = 0;
	if (path != NULL)
	{
		while (path[i])
		{
			strlen = ft_strlen(path[i]) + ft_strlen(exec->cmd[0]) + 1;
			copy = ft_calloc(strlen, sizeof(char));
			ft_strlcat(copy, path[i], strlen);
			ft_strlcat(copy, exec->cmd[0], strlen);
			if (access(copy, F_OK) == 0)
				execve(copy, exec->cmd, env);
			free(copy);
			i++;
		}
	}
}
