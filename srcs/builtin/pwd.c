#include "minishell.h"

void	pwd_builtin(void)
{
	char	temp[1024];

	printf("%s\n", getcwd(temp, sizeof(temp)));
}
