/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bedos-sa <bedos-sa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 10:20:00 by bedos-sa          #+#    #+#             */
/*   Updated: 2023/11/01 10:20:01 by bedos-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*search_and_expand_var(char *str, t_data *data)
{
	int	quoted;
	int	i;

	quoted = 0;
	i = -1;
	while (str[++i] != '\0')
	{
		quoted = is_quoted(str[i], quoted);
		if (quoted == 0 && (str[i] == '$' && str[i + 1] != '\0'
				&& str[i + 1] != ' ' && str[i + 1] != '$'))
			str = expand_utils(data, str, i);
		else if (quoted == 2 && (str[i] == '$' && str[i + 1] != '\0'
				&& ft_strchr(VAR_BLOCK, str[i + 1]) == NULL))
			str = expand_utils(data, str, i);
		if (str[0] == '\0')
			break ;
	}
	return (str);
}
