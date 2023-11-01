/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bedos-sa <bedos-sa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 10:20:46 by bedos-sa          #+#    #+#             */
/*   Updated: 2023/11/01 10:20:47 by bedos-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	close_pipes(t_args *args)
{
	close(args->pipis[0]);
	close(args->pipis[1]);
	close(args->pipes[0]);
	close(args->pipes[1]);
}

void	recycle_pipe(t_args *args)
{
	if (args->index % 2 == 0)
	{
		close(args->pipes[0]);
		close(args->pipes[1]);
		pipe(args->pipes);
	}
	else
	{
		close(args->pipis[0]);
		close(args->pipis[1]);
		pipe(args->pipis);
	}
}
