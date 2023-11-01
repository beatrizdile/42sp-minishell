/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_dups.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bedos-sa <bedos-sa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 10:20:35 by bedos-sa          #+#    #+#             */
/*   Updated: 2023/11/01 10:20:36 by bedos-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	first_command(t_args *args);
static void	middle_command(t_args *args);
static void	last_command(t_args *args);

void	deal_with_pipes(t_data *data)
{
	if (data->process_count > 1)
	{
		if (data->args->index == data->process_count - 1)
			last_command(data->args);
		else if (data->args->index == 0)
			first_command(data->args);
		else
			middle_command(data->args);
	}
	close_pipes(data->args);
}

static void	first_command(t_args *args)
{
	dup2(args->pipis[1], 1);
}

static void	middle_command(t_args *args)
{
	if (args->index % 2 == 0)
	{
		dup2(args->pipes[0], 0);
		dup2(args->pipis[1], 1);
	}
	else
	{
		dup2(args->pipis[0], 0);
		dup2(args->pipes[1], 1);
	}
}

static void	last_command(t_args *args)
{
	if (args->index % 2 == 0)
		dup2(args->pipes[0], 0);
	else
		dup2(args->pipis[0], 0);
}
