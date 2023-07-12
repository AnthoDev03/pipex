#include "../includes/pipex.h"

static void	child_process_common(int fds[2], char *cmd, char **envp)
{
	char	*path;
	int		execstat;

	close(fds[0]);
	close(fds[1]);
	path = find_path(envp, cmd);
	if (!path)
		puterror("Command not found ");
	execstat = execve(path, ft_split(cmd, ' '), envp);
	if (execstat == -1)
		puterror("Execve Error: command failed/not found ");
}

static void	child_process_out(int fds[2], char *outfile, char *cmd, char **envp)
{
	int	fd;

	close(fds[0]);
	fd = open(outfile, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (fd == -1)
		puterror("Outfile Error ");
	dup2(fds[1], STDOUT_FILENO);
	dup2(fd, STDOUT_FILENO);
	close(fds[1]);
	close(fd);
	child_process_common(fds, cmd, envp);
}

static void	child_process_in(int fds[2], char *infile, char *cmd, char **envp)
{
	int	fd;

	close(fds[1]);
	fd = open(infile, O_RDONLY);
	if (fd == -1)
		puterror("Infile Error ");
	dup2(fds[0], STDIN_FILENO);
	dup2(fd, STDIN_FILENO);
	close(fds[0]);
	close(fd);
	child_process_common(fds, cmd, envp);
}

void	out_process(int fds[2], char *outfile, char *cmd, char **envp)
{
	int	pid;

	pid = fork();
	if (pid == -1)
		puterror("Fork Error ");
	else if (pid == 0)
		child_process_out(fds, outfile, cmd, envp);
}

void	in_process(int fds[2], char *infile, char *cmd, char **envp)
{
	int	pid;

	pid = fork();
	if (pid == -1)
		puterror("Fork Error ");
	else if (pid == 0)
		child_process_in(fds, infile, cmd, envp);
}
