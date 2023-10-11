#include "minishell.h"

void	execute_builtin(t_data *data, t_exec *exec, pid_t *pids)
{
	if (ft_strcmp(data->args->exec->cmd[0], "env") == 0)
		env_builtin(data, exec->cmd);
	else if (ft_strcmp(data->args->exec->cmd[0], "pwd") == 0)
		pwd_builtin(data);
	else if (ft_strcmp(data->args->exec->cmd[0], "export") == 0)
		export_builtin(data, exec->cmd);
	else if (ft_strcmp(data->args->exec->cmd[0], "unset") == 0)
		unset_builtin(data, exec->cmd);
	else if (ft_strcmp(data->args->exec->cmd[0], "exit") == 0)
		exit_builtin(data, pids, exec->cmd);
	else if (ft_strcmp(data->args->exec->cmd[0], "echo") == 0)
		echo_builtin(data, exec->cmd);
	else if (ft_strcmp(data->args->exec->cmd[0], "cd") == 0)
		cd_builtin(data, exec->cmd);
}
