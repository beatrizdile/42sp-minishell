#include "minishell.h"

char	*expand_exit_status(char *str, int index, int exit_status)
{
	char	*new;
	char	*temp;
	int		i;
	int		j;
	int		buffer;

	temp = ft_itoa(exit_status);
	new = ft_calloc(ft_strlen(temp) + (ft_strlen(str) - 2) + 1, 1);
	i = -1;
	while (++i < index)
		new[i] = str[i];
	buffer = i + 2;
	j = 0;
	while (temp[j] != '\0')
		new[i++] = temp[j++];
	while (str[buffer] != '\0')
		new[i++] = str[buffer++];
	new[i] = '\0';
	free(str);
	free(temp);
	return (new);
}
