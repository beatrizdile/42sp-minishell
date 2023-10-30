#include "minishell.h"

void	first_command(t_args *args)
{
	dup2(args->pipis[1], 1);
}

void	middle_command(t_args *args)
{
	if (args->index % 2 == 0)
	{
		dup2(args->pipes[0], 0);
		dup2(args->pipis[1], 1);
	}
	else
	{
		dup2(args->pipis[0], 0);
		dup2(args->pipes[1], 1);
	}
}

void	last_command(t_args *args)
{
	if (args->index % 2 == 0)
		dup2(args->pipes[0], 0);
	else
		dup2(args->pipis[0], 0);
}
