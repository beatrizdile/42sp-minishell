/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_tildes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bedos-sa <bedos-sa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 10:19:43 by bedos-sa          #+#    #+#             */
/*   Updated: 2023/11/01 10:19:44 by bedos-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*search_and_expand_tilde(char *str, char *env);

void	check_tildes(t_list *token, char *home)
{
	t_list	*temp;
	char	*str;

	temp = token;
	while (temp != NULL)
	{
		str = ft_strdup((char *)temp->content);
		str = search_and_expand_tilde(str, home);
		free(temp->content);
		temp->content = ft_strdup(str);
		free(str);
		temp = temp->next;
	}
}

static char	*search_and_expand_tilde(char *str, char *home)
{
	char	*temp;

	temp = NULL;
	if (ft_strlen(str) == 0 || str[0] != '~'
		|| (str[1] != '\0' && str[1] != '/'))
		return (str);
	else if (str[0] == '~' && str[1] == '\0')
	{
		temp = ft_calloc(1, ft_strlen(home) + 1);
		ft_strlcpy(temp, home, ft_strlen(home) + 1);
	}
	else if (str[0] == '~' && str[1] == '/')
	{
		temp = ft_calloc(1, (ft_strlen(str) - 1) + ft_strlen(home) + 1);
		ft_strlcpy(temp, home, ft_strlen(home) + 1);
		ft_strlcpy(&temp[ft_strlen(temp)], &str[1], ft_strlen(temp)
			+ (ft_strlen(str) - 1) + 1);
	}
	free(str);
	return (temp);
}
