/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bedos-sa <bedos-sa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 10:21:23 by bedos-sa          #+#    #+#             */
/*   Updated: 2023/11/01 10:21:24 by bedos-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	search_unset(t_data *data, char *arr);
static void	ft_freenode(t_list *node, t_list *list);

void	unset_builtin(t_data *data, char **args)
{
	int		i;

	i = 0;
	while (args[++i] != NULL)
		search_unset(data, args[i]);
	data->exit_status = 0;
}

void	search_unset(t_data *data, char *arr)
{
	t_list	*tmp;

	tmp = data->env;
	while (tmp)
	{
		if (ft_strncmp((char *)tmp->content, arr, ft_strlen(arr)) == 0)
		{
			ft_freenode(tmp, data->env);
			break ;
		}
		tmp = tmp->next;
	}
}

static void	ft_freenode(t_list *node, t_list *list)
{
	t_list	*temp;

	temp = list;
	while (temp->next != node)
		temp = temp->next;
	temp->next = temp->next->next;
	free(node->content);
	free(node);
}
