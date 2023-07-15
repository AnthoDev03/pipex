#include "../includes/pipex.h"

void	child_process(int *fds, char *cmd, char *file, int redirect, char **envp)
{
	char	*path;
	int		fd;
	int		execstat;

	if (redirect == 1) // If this is the first command, redirect stdin to the file
	{
		fd = open(file, O_RDONLY);
		if (fd < 0)
			puterror("Error: Can't open infile");
		dup2(fd, STDIN_FILENO);
		close(fd);
	}
	else if (redirect == 2) // If this is the last command, redirect stdout to the file
	{
		fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0777);
		if (fd < 0)
			puterror("Error: Can't open outfile");
		dup2(fd, STDOUT_FILENO);
		close(fd);
	}

	// Redirect pipe appropriately
	if (redirect != 1)
		dup2(fds[0], STDIN_FILENO);
	if (redirect != 2)
		dup2(fds[1], STDOUT_FILENO);

	close(fds[0]);
	close(fds[1]);

	path = find_path(envp, cmd);
	if (!path)
		puterror("Command not found ");

	execstat = execve(path, ft_split(cmd, ' '), envp);
	if (execstat == -1)
		puterror("Execve Error: command failed/not found ");

	exit(0);
}

void	fork_processes(int *fds, char *infile, char *cmd1, char *cmd2, char *outfile, char **envp)
{
	int pid;

	pid = fork();
	if (pid == -1)
		puterror("Fork Error ");
	if (pid == 0)
		child_process(fds, cmd1, infile, 1, envp);

	pid = fork();
	if (pid == -1)
		puterror("Fork Error ");
	if (pid == 0)
		child_process(fds, cmd2, outfile, 2, envp);

	close(fds[0]);
	close(fds[1]);

	wait(NULL);
	wait(NULL);
}

