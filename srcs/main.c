/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anthrodr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 15:53:05 by anthrodr          #+#    #+#             */
/*   Updated: 2023/07/15 15:53:08 by anthrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	handle_pipe(int *fds, int redirect)
{
	if (redirect != 1)
		dup2(fds[0], STDIN_FILENO);
	if (redirect != 2)
		dup2(fds[1], STDOUT_FILENO);
	close(fds[0]);
	close(fds[1]);
}

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
	int		fds[2];
	t_exec	exec1;
	t_exec	exec2;

	if (ac != 5)
	{
		ft_putstr_fd("Usage: ./pipex filein cmd1 cmd2 fileout\n", 2);
		return (0);
	}
	if (pipe(fds) == -1)
		puterror("Pipe Error ");
	exec1.cmd = av[2];
	exec1.file = av[1];
	exec1.redirect = 1;
	exec1.envp = envp;
	exec2.cmd = av[3];
	exec2.file = av[4];
	exec2.redirect = 2;
	exec2.envp = envp;
	fork_processes(fds, &exec1, &exec2);
	return (0);
}
