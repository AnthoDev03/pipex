#include "../includes/pipex.h"

void	handle_redirect(int *fd, char *file, int flag)
{
	if (flag == 1) // Redirect input
	{
		*fd = open(file, O_RDONLY);
		if (*fd < 0)
			puterror("Error: Can't open infile");
		dup2(*fd, STDIN_FILENO);
	}
	else // Redirect output
	{
		*fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0777);
		if (*fd < 0)
			puterror("Error: Can't open outfile");
		dup2(*fd, STDOUT_FILENO);
	}
	close(*fd);
}

void	handle_pipe(int *fds, int redirect)
{
	if (redirect != 1)
		dup2(fds[0], STDIN_FILENO);
	if (redirect != 2)
		dup2(fds[1], STDOUT_FILENO);

	close(fds[0]);
	close(fds[1]);
}

void	execute_cmd(char *cmd, char **envp)
{
	char	*path;
	int		execstat;

	path = find_path(envp, cmd);
	if (!path)
		puterror("Command not found ");

	execstat = execve(path, ft_split(cmd, ' '), envp);
	if (execstat == -1)
		puterror("Execve Error: command failed/not found ");

	exit(0);
}

void	child_process(int *fds, char *cmd, char *file, int redirect, char **envp)
{
	int		fd;

	handle_redirect(&fd, file, redirect);
	handle_pipe(fds, redirect);
	execute_cmd(cmd, envp);
}

void	fork_and_execute(int *fds, char *cmd, char *file, int redirect, char **envp)
{
	int pid;

	pid = fork();
	if (pid == -1)
		puterror("Fork Error ");
	if (pid == 0)
		child_process(fds, cmd, file, redirect, envp);
}

void	fork_processes(int *fds, char *infile, char *cmd1, char *cmd2, char *outfile, char **envp)
{
	fork_and_execute(fds, cmd1, infile, 1, envp);
	fork_and_execute(fds, cmd2, outfile, 2, envp);

	close(fds[0]);
	close(fds[1]);

	wait(NULL);
	wait(NULL);
}

