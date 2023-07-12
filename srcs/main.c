#include "../includes/pipex.h"

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
	in_process(fds, av[1], av[2], envp);
	wait(NULL);
	out_process(fds, av[4], av[3], envp);
	close(fds[0]);
	close(fds[1]);
	return (0);
}
