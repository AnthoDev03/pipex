/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   out_in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anthrodr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 15:53:19 by anthrodr          #+#    #+#             */
/*   Updated: 2023/07/15 15:53:21 by anthrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

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

void	handle_redirect(int *fd, t_exec *exec)
{
	if (exec->redirect == 1)
	{
		*fd = open(exec->file, O_RDONLY);
		if (*fd < 0)
			puterror("Error: Can't open infile");
		dup2(*fd, STDIN_FILENO);
	}
	else
	{
		*fd = open(exec->file, O_WRONLY | O_CREAT | O_TRUNC, 0777);
		if (*fd < 0)
			puterror("Error: Can't open outfile");
		dup2(*fd, STDOUT_FILENO);
	}
	close(*fd);
}

void	child_process(int *fds, t_exec *exec)
{
	int		fd;

	handle_redirect(&fd, exec);
	handle_pipe(fds, exec->redirect);
	execute_cmd(exec->cmd, exec->envp);
}

void	fork_and_execute(int *fds, t_exec *exec)
{
	int		pid;

	pid = fork();
	if (pid == -1)
		puterror("Fork Error ");
	if (pid == 0)
		child_process(fds, exec);
}

void	fork_processes(int *fds, t_exec *exec1, t_exec *exec2)
{
	fork_and_execute(fds, exec1);
	fork_and_execute(fds, exec2);
	close(fds[0]);
	close(fds[1]);
	wait(NULL);
	wait(NULL);
}
