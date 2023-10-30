#include "minishell.h"

static void	commands_fork(t_args *args, t_data *data);
static void	execute_builtin_parent_process(t_data *data);
static void	execute_child_process(t_data *data, t_args *args);
static void	wait_all_processes(t_data *data, pid_t *pids, int flag);

void	execute(t_data *data)
{
	t_args	args;

	data->args = &args;
	args.index = 0;
	pipe(args.pipis);
	pipe(args.pipes);
	commands_fork(&args, data);
	close_pipes(&args);
}

static void	commands_fork(t_args *args, t_data *data)
{
	data->has_cmd = 0;
	data->has_builtin = 0;
	if (data->process_count == 1 && data->builtin_check == 1)
		execute_builtin_parent_process(data);
	else
		execute_child_process(data, args);
}

static void	execute_builtin_parent_process(t_data *data)
{
	int		fd[2];
	int		result;

	result = validate_files(data->token, data->lexer, &fd[0], &fd[1]);
	if (result == 1)
	{
		get_cmd_and_args(data->token, data->lexer, data);
		if (fd[0] != -2 || fd[1] != -2)
			redirect_files(fd[0], fd[1]);
		execute_builtin(data, data->exec, NULL);
		free_exec(data->exec);
	}
	else if (result == 2 || result == 4)
		data->exit_status = 1;
	else if (result == 3)
		data->exit_status = 126;
	close_files(fd[0], fd[1]);
}

static void	execute_child_process(t_data *data, t_args *args)
{
	pid_t	*pids;
	int		i;
	t_list	*temp;

	i = 0;
	temp = data->token;
	pids = ft_calloc(sizeof(int), data->process_count);
	while (args->index < data->process_count)
	{
		if (data->lexer[i] == PIPE)
		{
			i++;
			temp = temp->next;
		}
		pids[args->index] = fork();
		if (pids[args->index] == 0)
			child_process(data, temp, &data->lexer[i], pids);
		if (data->process_count == 1)
			wait_all_processes(data, pids, data->process_count);
		recycle_pipe(args);
		while (temp != NULL && data->lexer[i] != PIPE)
		{
			temp = temp->next;
			i++;
		}
		args->index++;
	}
	wait_all_processes(data, pids, data->process_count);
	free(pids);
}

static void	wait_all_processes(t_data *data, pid_t *pids, int flag)
{
	int	i;

	i = -1;
	if (flag == 1)
	{
		waitpid(pids[++i], &data->exit_status, 0);
		if (WEXITSTATUS(data->exit_status))
			data->exit_status = WEXITSTATUS(data->exit_status);
	}
	else
	{
		while (++i < data->process_count)
			waitpid(pids[i], &data->exit_status, 0);
		if (WEXITSTATUS(data->exit_status))
			data->exit_status = WEXITSTATUS(data->exit_status);
	}
}
