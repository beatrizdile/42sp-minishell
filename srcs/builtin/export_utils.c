/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcoqueir <gcoqueir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 10:21:01 by bedos-sa          #+#    #+#             */
/*   Updated: 2023/11/01 14:35:35 by gcoqueir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_key(char *str)
{
	if (str == NULL)
		return (0);
	if (ft_isalpha(str[0]) != 1 && str[0] != '_')
	{
		printf("aaaa\n");
		return (0);
	}
	return (1);
}

void	print_export(t_list *export)
{
	char	**arr;

	while (export)
	{
		arr = split_key_and_value((char *)export->content, '=');
		if (arr[1])
			printf("declare -x %s=\"%s\"\n", arr[0], arr[1]);
		else
			printf("declare -x %s=\"\"\n", arr[0]);
		ft_free_str_arr(&arr);
		export = export->next;
	}
}
