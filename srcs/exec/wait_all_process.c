/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait_all_process.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bedos-sa <bedos-sa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 10:20:29 by bedos-sa          #+#    #+#             */
/*   Updated: 2023/11/01 10:20:30 by bedos-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	wait_all_processes(t_data *data, pid_t *pids, int flag)
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
