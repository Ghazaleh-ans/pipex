/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gansari <gansari@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 15:20:04 by gansari           #+#    #+#             */
/*   Updated: 2025/02/07 15:20:12 by gansari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	**parse_path(char **envp)
{
	int		i;
	char	**paths;

	i = 0;
	while (envp[i])
	{
		if (!ft_strncmp(envp[i], "PATH=", 5))
		{
			paths = ft_split(envp[i] + 5, ':');
			return (paths);
		}
		i++;
	}
	return (NULL);
}

char	*ft_makepath(char const *path, char const *cmd)
{
	char	*cmd_path;
	char	*temp_path;

	temp_path = ft_strjoin(path, "/");
	cmd_path = ft_strjoin(temp_path, cmd);
	free(temp_path);
	return (cmd_path);
}

void	free_array(char **arr_to_free)
{
	int		i;

	i = 0;
	while (arr_to_free[i])
	{
		free(arr_to_free[i]);
		i++;
	}
	free(arr_to_free);
}
