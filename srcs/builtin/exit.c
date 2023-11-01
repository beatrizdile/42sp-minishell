/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bedos-sa <bedos-sa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 10:21:50 by bedos-sa          #+#    #+#             */
/*   Updated: 2023/11/01 10:21:51 by bedos-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exit_builtin(t_data *data, pid_t *pids, char **args)
{
	long	num;

	num = 0;
	if (data->exit_status != 0)
		num = data->exit_status;
	if (ft_arrsize(args) > 2)
	{
		ft_printf_fd(2, "exit: too many arguments\n");
		data->exit_status = 1;
		return ;
	}
	if (ft_arrsize(args) == 2)
	{
		if (ft_strdigit(args[1]) == 0)
		{
			ft_printf_fd(2, "exit: numeric argument required\n");
			data->exit_status = 2;
			return ;
		}
		if (args[1])
			num = ft_atol(args[1]);
	}
	free_builtin(data, pids);
	exit(num);
}
