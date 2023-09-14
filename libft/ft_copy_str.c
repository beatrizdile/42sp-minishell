/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_copy_str.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bedos-sa <bedos-sa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 11:46:55 by bedos-sa          #+#    #+#             */
/*   Updated: 2023/09/14 11:47:18 by bedos-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_copy_str(char *copy)
{
	char	*str;
	int		i;

	str = ft_calloc(1, ft_strlen(copy) + 1);
	i = 0;
	while (copy[i])
	{
		str[i] = copy[i];
		i++;
	}
	return (str);
}
