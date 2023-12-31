/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bedos-sa <bedos-sa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 10:19:13 by bedos-sa          #+#    #+#             */
/*   Updated: 2023/11/01 10:19:14 by bedos-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_data	*data;

	(void)argv;
	if (argc == 1)
	{
		data = ft_calloc(1, sizeof(t_data));
		copy_env(&data->env, envp, data);
		init_readline(data);
		free_for_all(data);
	}
	return (0);
}
