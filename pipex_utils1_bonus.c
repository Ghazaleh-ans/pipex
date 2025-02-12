
#include "pipex_bonus.h"

int file_opener(char *path, char flag)
{
	int fd;

	fd = -1;
	if (flag == 'I')
	{
		fd = open(path, O_RDONLY);
		if (fd == -1)
			ft_perror(path);
	}
	else if (flag == 'O')
	{
		fd = open(path, O_CREAT | O_WRONLY | O_TRUNC, 0777);
		if (fd == -1)
			ft_perror(path);
	}
	else if (flag == 'h')
	{
		fd = open(path, O_CREAT | O_WRONLY | O_APPEND, 0777);
		if (fd == -1)
			perror(path);
	}
	return (fd);
}

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

char	*find_executable(char **paths, char *cmd)
{
	int		i;
	char	*the_way;

	i = 0;
	while (paths[i])
	{
		the_way = ft_makepath(paths[i], cmd);
		if (the_way && access(the_way, X_OK) == 0)
			return (the_way);
		free(the_way);
		i++;
	}
	return (NULL);
}

void	ft_exec(char *cmd, char **envp)
{
	char	**commands;
	char	**paths;
	char	*the_way;

	commands = ft_split(cmd, ' ');
	paths = parse_path(envp);
	if (!commands || !paths)
		exit(1);
	the_way = find_executable(paths, commands[0]);
	if (the_way)
	{
		execve(the_way, commands, envp);
		free(the_way);
	}
	free_array(commands);
	free_array(paths);
	exit(1);
}
