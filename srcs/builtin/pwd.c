#include "minishell.h"

void	pwd_builtin(void)
{
	char	*temp;

	temp = getcwd(NULL, 0);
	printf("%s\n", temp);
	free(temp);
}
