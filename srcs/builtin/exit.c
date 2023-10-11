#include "minishell.h"

void	exit_builtin(t_data *data, pid_t *pids, char **args)
{
	long	num;

	num = 0;
	if (data->exit_status != 0)
		num = data->exit_status;
	if (ft_arrsize(args) > 2)
	{
		printf("exit: too many arguments\n");
		data->exit_status = 1;
		return ;
	}
	if (ft_arrsize(args) == 2)
		if (args[1])
			num = ft_atol(args[1]);
	free_builtin(data, pids);
	exit(num);
}


// 	num = 0;
// 	if (data->exit_status != 0)
// 		num = data->exit_status;
// 	len = ft_arrsize(args);
// 	if (len > 1)
// 	{
// 		if (ft_strdigit(args[1]) == 0)
// 		{
// 			ft_printf_fd(2, "exit: %s: numeric argument required\n", args[1]);
// 			free_builtin(data, pids);
// 			exit (2);
// 		}
// 		if (len > 2)
// 		{
// 			ft_printf_fd(2, "exit: too many arguments\n");
// 			data->exit_status = 1;
// 			return ;
// 		}
// 	}