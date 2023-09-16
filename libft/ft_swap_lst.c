/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_swap_lst.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bedos-sa <bedos-sa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 13:52:40 by bedos-sa          #+#    #+#             */
/*   Updated: 2023/09/16 13:52:45 by bedos-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_swap_lst(t_list *lst)
{
	void	*tmp;

	tmp = lst->content;
	lst->content = lst->next->content;
	lst->next->content = tmp;
}
