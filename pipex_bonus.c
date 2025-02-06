#include "pipex_bonus.h"

void	write_to_limiter(int *fd, char *limiter)
{
	char	*line;

	close(fd[0]);
	ft_putstr_fd("pipe heredoc> ", 1);
	line = get_next_line(0);
	while (line)
	{
		if (ft_strcmp(limiter, line) == 0)
		{
			free(line);
			close(fd[1]);
			exit(EXIT_SUCCESS);
		}
		ft_putstr_fd("pipe in here_doc> ", 1);
		if (write(fd[1], line, ft_strlen(line)) == -1)
			perror("ERROR(write input in here_doc)");
		if (write(fd[1], "\n", 1) == -1)
			perror("ERROR(write new line in here_doc)");
		free(line);
		line = get_next_line(0);
	}
	free(line);
	close(fd[1]);
	ft_perror("ERROR - 13");
}

void	here_doc(int argc, char **argv)
{
	int		fd[2];
	int		pid;

	if (argc < 6)
		ft_error("Error: Wrong count of arguments -- argc < 6");
	if (pipe(fd) == -1)
		perror("ERROR(pipe in here_doc)");
	pid = fork();
	if (pid == -1)
		ft_perror("ERROR(fork in here_doc)");
	if (pid == 0)
		write_to_limiter(fd, argv[2]);
	else
	{
		close(fd[1]);
		if (dup2(fd[0], STDIN_FILENO) == -1)
			ft_perror("ERROR - 14");
		close(fd[0]);
		waitpid(pid, NULL, 0);
	}
}

void	pipex(int argc, char **argv, char **envp)
{
	int	num;
	int	fd_in;
	int	fd_out;

	if (ft_strcmp(argv[1], "here_doc") == 0)
	{
		num = 3;
		here_doc(argc, argv);
		fd_out = opener(argv[argc - 1], 'h');
	}
	else
	{
		num = 2;
		fd_in = opener(argv[1], 'I');
		fd_out = opener(argv[argc - 1], 'O');
		if (dup2(fd_in, STDIN_FILENO) == -1)
			ft_perror("ERROR - 1");
	}
	while (num < argc - 2)
		command_executing(argv[num++], envp);
	if (dup2(fd_out, STDOUT_FILENO) == -1)
		ft_perror("ERROR - 2");
	executer(argv[argc - 2], envp);
}
