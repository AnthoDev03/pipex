#include "../includes/pipex.h"

void	free_allocated_memory(char ***arr)
{
	char	**temp;

	temp = *arr;
	while (*temp)
	{
		free(*temp);
		temp++;
	}
	free(*arr);
	*arr = NULL;
}

void	puterror(char *str)
{
	ft_putstr_fd("\033[0;31m", 2);
	perror(str);
	ft_putstr_fd("\033[0m", 2);
	exit(-1);
}

int	main(int ac, char **av, char **envp)
{
	int	fds[2];

	if (ac != 5)
	{
		ft_putstr_fd("Usage: ./pipex filein cmd1 cmd2 fileout\n", 2);
		return (0);
	}
	if (pipe(fds) == -1)
		puterror("Pipe Error ");
	fork_processes(fds, av[1], av[2], av[3], av[4], envp);
	return (0);
}


