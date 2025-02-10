/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gansari <gansari@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 15:21:20 by gansari           #+#    #+#             */
/*   Updated: 2025/02/07 15:21:21 by gansari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	file_opener(char *path, char flag)
{
	int	fd;

	fd = -1;
	if (flag == 'I')
		fd = open(path, O_RDONLY);
	else if (flag == 'O')
		fd = open(path, O_CREAT | O_WRONLY | O_TRUNC, 0777);
	else if (flag == 'h')
		fd = open(path, O_CREAT | O_WRONLY | O_APPEND, 0777);
	if (fd == -1)
		ft_perror("ERROR (input or output file)");
	return (fd);
}
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
void	clean_line(char *line)
{
	char	*trimmed_line;

	trimmed_line = line;
	while (*trimmed_line && *trimmed_line != '\n')
		trimmed_line++;
	*trimmed_line = '\0';
}

void	write_line_to_fd(int fd, char *line)
{
	if (write(fd, line, ft_strlen(line)) == -1)
		perror("ERROR(write the line to fd)");
	if (write(fd, "\n", 1) == -1)
		perror("ERROR(write new line to fd)");
}
