#include "minishell.h"

void	free_tab(char **tab)
{
	int	i;

	i = -1;
	while (tab[++i] != NULL)
		free(tab[i]);
	free(tab);
}

void	error_check(int i, t_pipex *pipex)
{
	if (pipex != NULL)
	{
		if (pipex->all_paths != NULL)
			free_tab(pipex->all_paths);
		if (pipex->cmd != NULL)
			free_tab(pipex->cmd);
	}
	if (i == 1)
		ft_printf("Usage: ./pipex <infile> <cmd1> <cmd...> <outfile>\n");
	else if (i == 2)
		ft_printf("Usage: ./pipex here_doc LIMITER <cmd1> <...> <outfile>\n");
	else if (i == 3)
		ft_putendl_fd("Error: command not found", 2);
	else
		perror("Error");
	if (i == 3 || i == 4)
		close(pipex->infile);
	if (i >= 3)
		close(pipex->outfile);
	exit(EXIT_FAILURE);
}
