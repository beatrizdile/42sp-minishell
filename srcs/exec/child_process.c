/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bedos-sa <bedos-sa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 10:20:43 by bedos-sa          #+#    #+#             */
/*   Updated: 2023/11/01 10:20:44 by bedos-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	child_process(t_data *data, t_list *token, int *lexer, pid_t *pids)
{
	int			fd[2];
	int			result;

	result = validate_files(token, lexer, &fd[0], &fd[1]);
	if (result == 1)
	{
		get_cmd_and_args(token, lexer, data);
		deal_with_pipes(data);
		if (fd[0] != -2 || fd[1] != -2)
			redirect_files(fd[0], fd[1]);
		if (data->has_builtin == 1 || data->has_cmd == 1)
			finally_execute(data, fd, pids);
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
