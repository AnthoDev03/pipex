#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include <limits.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <stddef.h>
# include <stdint.h>
# include<sys/wait.h>
# include <fcntl.h>

void free_allocated_memory(char ***arr);
void	ft_putstr_fd(char *s, int fd);
size_t  ft_strlen(const char *s);
size_t  ft_strlcpy(char *dst, const char *src, size_t dstsize);
char    *ft_strjoin(char const *s1, char const *s2);
size_t  ft_strlcat(char *dst, const char *src, size_t size);
char    *ft_strnstr(const char *big, const char *little, size_t len);
char    **ft_split(char *s, char c);
char    *ft_substr(char const *s, unsigned int start, size_t len);
char    *ft_strnstr(const char *big, const char *little, size_t len);

#endif
