/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frees.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bedos-sa <bedos-sa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 10:20:52 by bedos-sa          #+#    #+#             */
/*   Updated: 2023/11/01 10:20:53 by bedos-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_cmd_not_found(char **path, char **env, t_data *data, pid_t *pids)
{
	ft_printf_fd(2, "%s: command not found\n", data->exec->cmd[0]);
	free(pids);
	ft_free_str_arr(&path);
	ft_free_str_arr(&env);
	free_exec(data->exec);
	free_for_all(data);
}

void	free_builtin(t_data *data, pid_t *pids)
{
	free(pids);
	free_exec(data->exec);
	free_for_all(data);
}

void	free_for_all(t_data	*data)
{
	rl_clear_history();
	if (data->env != NULL)
		free_list(data->env);
	if (data->prompt != NULL)
		free(data->prompt);
	if (data->fd_heredoc != NULL)
	{
		delete_heredoc_files(data);
		free(data->fd_heredoc);
	}
	if (data->token != NULL)
		free_list(data->token);
	if (data->lexer != NULL)
		free(data->lexer);
	if (data->home != NULL)
		free(data->home);
	if (data != NULL)
		free(data);
}

void	free_list(t_list *list)
{
	t_list	*temp;

	temp = list;
	while (temp != NULL)
	{
		list = list->next;
		if (temp->content)
			free(temp->content);
		free(temp);
		temp = list;
	}
}

void	free_exec(t_exec *exec)
{
	t_exec	*temp;

	temp = exec;
	if (temp->cmd)
		ft_free_str_arr(&temp->cmd);
	free(exec);
}
