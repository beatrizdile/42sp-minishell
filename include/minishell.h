/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bedos-sa <bedos-sa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 14:55:22 by bedos-sa          #+#    #+#             */
/*   Updated: 2023/09/11 17:27:52 by bedos-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <readline/history.h>
# include <readline/readline.h>
# include <stdio.h>

typedef struct s_data
{
	char	*temp;
	char	**env;
	char	**path;
}			t_data;

// Main
void	read_prompt(t_data *data);
char	**save_path(char **envp);
void	init_readline(t_data *data);

// Free
void	free_for_all(t_data *data);
void	free_str_arrs(char **arr);
void	free_list(t_list *list);

// Builtin
void	exit_builtin(t_data *data);
void	env_builtin(t_data *data);
void	pwd_builtin(void);

#endif