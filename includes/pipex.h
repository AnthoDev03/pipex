#ifndef PIPEX_H
# define PIPEX_H

# include <fcntl.h>
# include <limits.h>
# include <stdbool.h>
# include <stddef.h>
# include <stdint.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <unistd.h>
# include "../libft/libft.h"

typedef struct s_exec {
    char *cmd;
    char *file;
    int redirect;
    char **envp;
}              t_exec;

void	puterror(char *str);
void	free_allocated_memory(char ***arr);
char	*find_path(char **envp, char *cmd);
void	execute_cmd(char *cmd, char **envp); 
void	child_process(int *fds, t_exec *exec);
void	fork_and_execute(int *fds, t_exec *exec);
void	handle_pipe(int *fds, int redirect);
void	fork_processes(int *fds, t_exec *exec1, t_exec *exec2);

#endif

