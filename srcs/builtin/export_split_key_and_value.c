/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_split_key_and_value.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bedos-sa <bedos-sa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 10:21:40 by bedos-sa          #+#    #+#             */
/*   Updated: 2023/11/01 10:21:41 by bedos-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**ft_sep_words(char **strs, int size, char *s, char c);
static void	verify_equal_sign(int *count, int *temp, char *s, int c_word);
static char	*copy_str(char *s, int temp, int count);

char	**split_key_and_value(char *str, char c)
{
	char	**strs;
	int		pos;
	int		size;
	int		equal_check;

	if (str == NULL)
		return (NULL);
	pos = -1;
	size = 0;
	equal_check = 0;
	while (str[++pos] != '\0' && equal_check == 0)
	{
		if (str[pos] != c && (str[pos + 1] == c || str[pos + 1] == '\0'))
		{
			size++;
			if (str[pos + 1] == c && str[pos + 2] != '\0')
				size++;
			equal_check = 1;
		}
	}
	strs = malloc((size + 1) * sizeof(char *));
	if (strs == NULL)
		return (NULL);
	strs = ft_sep_words(strs, size, str, c);
	return (strs);
}

static char	**ft_sep_words(char **strs, int size, char *s, char c)
{
	int	count;
	int	c_word;
	int	temp;
	int	equal_check;

	count = 0;
	c_word = -1;
	equal_check = 0;
	while (++c_word < size)
	{
		temp = count;
		verify_equal_sign(&count, &temp, s, c_word);
		if (equal_check == 0)
			while (s[temp] != c && s[temp] != '\0')
				temp++;
		else if (equal_check == 1)
			while (s[temp] != '\0')
				temp++;
		if (s[temp] == c)
			equal_check = 1;
		strs[c_word] = copy_str(s, temp, count);
		count = temp;
	}
	strs[c_word] = NULL;
	return (strs);
}

static void	verify_equal_sign(int *count, int *temp, char *s, int c_word)
{
	if (s[*count] == '=')
	{
		if (c_word != 0)
			*count = *count + 1;
		*temp = *temp + 1;
	}
}

static char	*copy_str(char *s, int temp, int count)
{
	char	*str;

	str = malloc((temp - count + 1) * sizeof(char));
	ft_memcpy((void *)str, (const void *)&s[count], temp - count);
	str[temp - count] = '\0';
	return (str);
}
