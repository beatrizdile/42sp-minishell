/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bedos-sa <bedos-sa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 10:21:36 by bedos-sa          #+#    #+#             */
/*   Updated: 2023/11/01 10:21:37 by bedos-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	env_builtin(t_data *data, char **args)
{
	t_list	*temp;

	if (ft_arrsize(args) > 1)
	{
		ft_printf_fd(2, "env: %s: No such file or directory\n", args[1]);
		data->exit_status = 127;
		return ;
	}
	temp = data->env;
	while (temp != NULL)
	{
		if (temp->content && ft_strchr((char *)temp->content, '=') != NULL)
			printf("%s\n", (char *)temp->content);
		temp = temp->next;
	}
	data->exit_status = 0;
}
