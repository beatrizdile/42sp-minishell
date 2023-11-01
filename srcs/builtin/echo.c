/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bedos-sa <bedos-sa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 10:21:29 by bedos-sa          #+#    #+#             */
/*   Updated: 2023/11/01 10:21:30 by bedos-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_new_line(int n_check);

void	echo_builtin(t_data *data, char **args)
{
	int	len;
	int	i;
	int	n_check;

	n_check = 0;
	len = ft_arrsize(args);
	i = 1;
	if (len > 1)
	{
		while (ft_strcmp(args[i], "-n") == 0)
		{
			i++;
			n_check = 1;
		}
		if (args[i] != NULL)
		{
			while (i < len - 1)
				printf("%s ", args[i++]);
			printf("%s", args[i]);
		}
		print_new_line(n_check);
	}
	else
		printf("\n");
	data->exit_status = 0;
}

void	print_new_line(int n_check)
{
	if (n_check == 0)
		printf("\n");
}
