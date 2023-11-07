/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcoqueir <gcoqueir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 10:21:29 by bedos-sa          #+#    #+#             */
/*   Updated: 2023/11/01 14:37:24 by gcoqueir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_new_line(int n_check);
static int	verify_n(char *str);

void	echo_builtin(t_data *data, char **args)
{
	int	i;
	int	n_check;

	n_check = 0;
	i = 1;
	if (ft_arrsize(args) > 1)
	{
		while (args[i] != NULL && ft_strncmp(args[i], "-n", 2) == 0)
		{
			if (verify_n(args[i]) == 0)
				break ;
			i++;
			n_check = 1;
		}
		if (args[i] != NULL)
		{
			while (i < ft_arrsize(args) - 1)
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

static int	verify_n(char *str)
{
	int	i;

	i = 2;
	while (str[i] != '\0')
	{
		if (str[i++] != 'n')
			return (0);
	}
	return (1);
}
