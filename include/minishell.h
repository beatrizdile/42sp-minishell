/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bedos-sa <bedos-sa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 14:55:22 by bedos-sa          #+#    #+#             */
/*   Updated: 2023/09/06 16:27:12 by bedos-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

typedef struct s_history
{
	char				*prompt;
	struct s_history	*next;
}	t_history;

void	init_readline(void);

// Linked List
void		history_add_front(t_history **history, t_history *node);
t_history	*history_new_node(char *content);

#endif