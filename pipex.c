#include "pipex.h"

void	ft_exec(char *cmd, char **envp)
{
	int		i;
	char	**commands;
	char	**paths;
	char	*the_way;

	commands = ft_split(cmd, ' ');
	paths = parse_path(envp);
	if (paths == NULL)
		ft_error("Error: no PATH");
	i = 0;
	while (paths[i])
	{
		the_way = ft_makepath(paths[i], commands[0]);
		if (access(the_way, F_OK) == 0)
		{
			if (execve(the_way, commands, NULL) == -1)
				ft_perror("ERROR(executing cmd)");
		}
		free(the_way);
		i++;
	}
	free_array(commands);
	free_array(paths);
	ft_perror("ERROR(no execution)");
}

void	first_cmd_exec(int *fd, char **argv, char **envp)
{
	int	fd_in;

	fd_in = open(argv[1], O_RDONLY);
	if (fd_in < 0)
		ft_perror("ERROR(opening input file)");
	if (dup2(fd[1], STDOUT_FILENO) == -1)
		ft_perror("ERROR(dup2 STDOUT)");
	if (dup2(fd_in, STDIN_FILENO) == -1)
		ft_perror("ERROR(dup2 STDIN)");
	close(fd[0]);
	close(fd_in);
	close(fd[1]);
	ft_exec(argv[2], envp);
}

void	second_cmd_exec(int *fd, char **argv, char **envp)
{
	int	fd_out;

	fd_out = open(argv[4], O_CREAT | O_WRONLY | O_TRUNC, 0777);
	if (fd_out < 0)
		ft_perror("ERROR(opening output file)");
	if (dup2(fd[0], STDIN_FILENO) == -1)
		ft_perror("ERROR(dup2 STDIN)");
	if (dup2(fd_out, STDOUT_FILENO) == -1)
		ft_perror("ERROR(dup2 STDOUT)");
	close(fd[1]);
	close(fd_out);
	close(fd[0]);
	ft_exec(argv[3], envp);
}

void	pipex(int argc, char **argv, char **envp)
{
	int	fd[2];
	int	pid1;
	int	pid2;

	if (argc != 5)
		ft_error("Error: Wrong count of arguments -- argc != 5");
	if (pipe(fd) == -1)
		ft_perror("Error(pipe)");
	pid1 = fork();
	if (pid1 < 0)
		ft_perror("Error(fork1)");
	if (pid1 == 0)
		first_cmd_exec(fd, argv,envp);
	pid2 = fork();
	if (pid2 < 0)
		ft_perror("Error(fork2)");
	if (pid2 == 0)
		second_cmd_exec(fd, argv,envp);
	close(fd[0]);
	close(fd[1]);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
}
