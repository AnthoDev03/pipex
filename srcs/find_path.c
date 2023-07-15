/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anthrodr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 15:53:12 by anthrodr          #+#    #+#             */
/*   Updated: 2023/07/15 15:53:14 by anthrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

static char	*extract_path_from_env(char **envp)
{
	char	*sub;

	while (*envp && !ft_strnstr(*envp, "PATH=", 5))
		envp++;
	sub = ft_substr(*envp, 5, ft_strlen(*envp) - 5);
	return (sub);
}

static char	*search_executable_in_paths(char **paths, char *cmd)
{
	char	*cmd_path;
	char	*sub;

	cmd_path = NULL;
	sub = ft_strjoin("/", cmd);
	while (*paths)
	{
		cmd_path = ft_strjoin(*paths, sub);
		if (!cmd_path)
		{
			free(sub);
			return (NULL);
		}
		if (!access(cmd_path, F_OK))
			break ;
		free(cmd_path);
		paths++;
	}
	free(sub);
	return (cmd_path);
}

char	*find_path(char **envp, char *cmd)
{
	char	**temp;
	char	*sub;
	char	**paths;
	char	*cmd_path;

	temp = ft_split(cmd, ' ');
	cmd = *temp;
	sub = extract_path_from_env(envp);
	paths = ft_split(sub, ':');
	free(sub);
	cmd_path = search_executable_in_paths(paths, cmd);
	free_allocated_memory(&paths);
	free_allocated_memory(&temp);
	return (cmd_path);
}
