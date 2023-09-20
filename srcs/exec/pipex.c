#include "minishell.h"

static int	open_file(char *file, int mode, t_pipex *pipex);
static void	take_paths(char **envp, t_pipex *pipex);

void	pipex(int argc, char **argv, char **envp)
{
	t_pipex	pipex;
	int		cmd;

	if (ft_strncmp("<<", argv[0], 2) == 0)
	{
		cmd = 3;
		pipex.outfile = open_file(argv[argc - 1], 3, &pipex);
		here_doc(argv[2], &pipex);
	}
	else
	{
		cmd = 2;
		pipex.infile = open_file(argv[1], 1, &pipex);
		pipex.outfile = open_file(argv[argc - 1], 2, &pipex);
		dup2(pipex.infile, STDIN_FILENO);
	}
	take_paths(envp, &pipex);
	while (cmd <= argc - 3)
		pipe_it(argv[cmd++], envp, &pipex);
	dup2(pipex.outfile, STDOUT_FILENO);
	make_cmd(envp, argv[cmd], &pipex);
}

static int	open_file(char *file, int mode, t_pipex *pipex)
{
	int	fd;

	if (mode == 1)
		fd = open(file, O_RDONLY);
	else if (mode == 2)
		fd = open(file, O_TRUNC | O_CREAT | O_WRONLY, 0777);
	else
		fd = open(file, O_APPEND | O_CREAT | O_WRONLY, 0777);
	if (fd == -1)
	{
		if (mode == 2)
			close(pipex->infile);
		perror("Error");
		exit(1);
	}
	return (fd);
}

static void	take_paths(char **envp, t_pipex *pipex)
{
	int		i;
	char	**temp;

	i = 0;
	while (envp[i] != NULL && ft_strncmp("PATH", envp[i], 4) != 0)
		i++;
	temp = ft_split(&envp[i][5], ':');
	i = 0;
	while (temp[i] != NULL)
		i++;
	pipex->all_paths = malloc(sizeof(char *) * (i + 1));
	if (pipex->all_paths == NULL)
	{
		free_tab(temp);
		exit(1);
	}
	i = -1;
	while (temp[++i] != NULL)
		pipex->all_paths[i] = ft_strjoin(temp[i], "/");
	pipex->all_paths[i] = NULL;
	free_tab(temp);
}
