#include "minishell.h"

void	close_pipes(t_args *args)
{
	close(args->pipis[0]);
	close(args->pipis[1]);
	close(args->pipes[0]);
	close(args->pipes[1]);
}

void	recycle_pipe(t_args *args)
{
	if (args->index % 2 == 0)
	{
		close(args->pipes[0]);
		close(args->pipes[1]);
		pipe(args->pipes);
	}
	else
	{
		close(args->pipis[0]);
		close(args->pipis[1]);
		pipe(args->pipis);
	}
}
