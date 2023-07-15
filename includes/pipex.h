#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

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

void	puterror(char *str);
void	free_allocated_memory(char ***arr);
char	*find_path(char **envp, char *cmd);
void	out_process(int fds[2], char *outfile, char *cmd, char **envp);
void	in_process(int fds[2], char *infile, char *cmd, char **envp);

#endif
