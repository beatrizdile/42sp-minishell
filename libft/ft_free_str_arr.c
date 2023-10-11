/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_str_arr.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcoqueir <gcoqueir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 11:57:16 by bedos-sa          #+#    #+#             */
/*   Updated: 2023/10/09 07:28:16 by gcoqueir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_free_str_arr(char ***arr)
{
	int	j;

	j = 0;
	while (*arr && (*arr)[j])
	{
		if ((*arr)[j])
		{
			free((*arr)[j]);
			(*arr)[j] = NULL;
		}
		j++;
	}
	if (*arr)
	{
		free(*arr);
		*arr = NULL;
	}
}
