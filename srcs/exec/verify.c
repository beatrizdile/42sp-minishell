/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verify.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcoqueir <gcoqueir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 11:14:55 by gcoqueir          #+#    #+#             */
/*   Updated: 2023/11/01 11:14:56 by gcoqueir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	verify(int result, char *str, char **cmd, char **env)
{
	if (result == 0)
	{
		verify_permission(str, cmd, env);
		return (0);
	}
	return (-1);
}
