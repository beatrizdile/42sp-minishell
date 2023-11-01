/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deal_with_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bedos-sa <bedos-sa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 10:20:13 by bedos-sa          #+#    #+#             */
/*   Updated: 2023/11/01 10:20:14 by bedos-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	redirect_files(int fd_in, int fd_out)
{
	if (fd_in != -2)
		dup2(fd_in, 0);
	if (fd_out != -2)
		dup2(fd_out, 1);
}

void	close_files(int fd_in, int fd_out)
{
	if (fd_in != -2)
		close(fd_in);
	if (fd_out != -2)
		close(fd_out);
}
