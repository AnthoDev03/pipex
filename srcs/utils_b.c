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

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	s_len;
	char	*empty_string;
	char	*new_string;

	if (s == NULL)
		return (NULL);
	s_len = ft_strlen(s);
	if (start >= s_len)
	{
		empty_string = (char *)malloc(1 * sizeof(char));
		if (empty_string == NULL)
			return (NULL);
		empty_string[0] = '\0';
		return (empty_string);
	}
	new_string = (char *)malloc((len + 1) * sizeof(char));
	if (new_string == NULL)
		return (NULL);
	ft_strlcpy(new_string, s + start, len + 1);
	return (new_string);
}

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;
	size_t	k;

	i = 0;
	j = 0;
	k = 0;
	if (little[i] == '\0')
		return ((char *)big);
	while (big[i] && k < len)
	{
		while (big[i] && big[i] == little[j] && (k + i) < len)
		{
			if (little[j + 1] == '\0')
				return ((char *)big + i - j);
			j++;
			i++;
		}
		i = 0;
		j = 0;
		big++;
		k++;
	}
	return (NULL);
}

void	puterror(char *str)
{
	ft_putstr_fd("\033[0;31m", 2);
	perror(str);
	ft_putstr_fd("\033[0m", 2);
	exit(-1);
}
