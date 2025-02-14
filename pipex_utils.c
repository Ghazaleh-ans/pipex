/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gansari <gansari@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 14:47:56 by gansari           #+#    #+#             */
/*   Updated: 2025/02/14 14:47:58 by gansari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	**parse_path(char **envp)
{
	int		i;
	char	**paths;

	i = 0;
	if (!envp)
		return (NULL);
	while (envp[i])
	{
		if (!ft_strncmp(envp[i], "PATH=", 5))
		{
			paths = ft_split(envp[i] + 5, ':');
			if (!paths)
				return (NULL);
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

	if (!path || !cmd)
		return (NULL);
	if (cmd[0] == '/' || (cmd[0] == '.' && cmd[1] == '/'))
		return (ft_strdup(cmd));
	temp_path = ft_strjoin(path, "/");
	if (!temp_path)
		return (NULL);
	cmd_path = ft_strjoin(temp_path, cmd);
	free(temp_path);
	return (cmd_path);
}

void	free_array(char **arr_to_free)
{
	int	i;

	if (!arr_to_free)
		return ;
	i = 0;
	while (arr_to_free[i])
	{
		free(arr_to_free[i]);
		i++;
	}
	free(arr_to_free);
}
