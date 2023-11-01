/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bedos-sa <bedos-sa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 10:20:16 by bedos-sa          #+#    #+#             */
/*   Updated: 2023/11/01 10:20:17 by bedos-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	delete_heredoc_files(t_data *data)
{
	t_list	*temp;
	int		i;

	temp = data->token;
	i = -1;
	while (temp != NULL)
	{
		if (data->lexer[++i] == HEREDOC)
			unlink((char *)temp->next->content);
		temp = temp->next;
	}
}
