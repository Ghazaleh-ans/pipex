#include "pipex.h"

void	ft_exec(char *cmd, char **envp)
{
	char	**commands;
	char	**paths;
	char	*the_way;
	int		i;

	commands = ft_split(cmd, ' ');
	paths = parse_path(envp);
	if (!commands || !paths)
		exit(1);
	i = 0;
	while (paths[i])
	{
		the_way = ft_makepath(paths[i], commands[0]);
		if (the_way && access(the_way, X_OK) == 0)
		{
			execve(the_way, commands, envp);
			free(the_way);
			break ;
		}
		free(the_way);
		i++;
	}
	free_array(commands);
	free_array(paths);
	exit(127);
}

void	first_cmd_exec(int *fd, char **argv, char **envp)
{
	int	fd_in;

	fd_in = open(argv[1], O_RDONLY);
	if (fd_in < 0)
		perror(argv[1]);
	if (dup2(fd_in, STDIN_FILENO) == -1)
		ft_putstr_fd("dup2 error\n", 2);
	if (dup2(fd[1], STDOUT_FILENO) == -1)
		ft_putstr_fd("dup2 error\n", 2);
	close(fd[0]);
	//if (fd_in != -1)
	close(fd_in);
	close(fd[1]);
	ft_exec(argv[2], envp);
	exit(0);
}

void	second_cmd_exec(int *fd, char **argv, char **envp)
{
	int	fd_out;
	
	fd_out = open(argv[4], O_CREAT | O_WRONLY | O_TRUNC, 0777);
	if (fd_out < 0)
	{
		close(fd[0]);
		close(fd[1]);
		exit(1);
	}
	if (dup2(fd_out, STDOUT_FILENO) == -1)
		ft_putstr_fd("dup2 error\n", 2);
	close(fd_out);
	if (dup2(fd[0], STDIN_FILENO) == -1)
	{
		ft_putstr_fd("dup2 error\n", 2);
		close(fd_out);
		close(fd[0]);
		close(fd[1]);
		exit(1);
	}
	close(fd[1]);
	close(fd[0]);
	ft_exec(argv[3], envp);
}

int	pipex(int argc, char **argv, char **envp)
{
	int	fd[2];
	int	pid1;
	int	pid2;
	int	status;

	if (argc != 5)
		ft_error("Error: Wrong count of arguments -- argc != 5");
	if (pipe(fd) == -1)
		return (1);
	pid1 = fork();
	if (pid1 < 0)
		return (1);
	if (pid1 == 0)
		first_cmd_exec(fd, argv, envp);
	pid2 = fork();
	if (pid2 < 0)
		return (1);
	if (pid2 == 0)
		second_cmd_exec(fd, argv, envp);
	close(fd[0]);
	close(fd[1]);
	waitpid(pid1, &status, 0);
	waitpid(pid2, &status, 0);
	return ((status & 0xFF00) >> 8);
}
