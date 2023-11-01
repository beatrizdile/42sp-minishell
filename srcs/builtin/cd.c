/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bedos-sa <bedos-sa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 10:20:57 by bedos-sa          #+#    #+#             */
/*   Updated: 2023/11/01 10:20:58 by bedos-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cd_builtin(t_data *data, char **args)
{
	int			len;
	struct stat	file_info;

	len = ft_arrsize(args);
	if (len > 2)
	{
		ft_putendl_fd("cd: too many arguments", 2);
		data->exit_status = 1;
		return ;
	}
	else if (len == 1)
		chdir(data->home);
	else if (len == 2)
	{
		if (stat(args[1], &file_info) != 0)
		{
			ft_printf_fd(2, "cd: %s: No such file or directory\n", args[1]);
			data->exit_status = 1;
			return ;
		}
		chdir(args[1]);
	}
	data->exit_status = 0;
}
