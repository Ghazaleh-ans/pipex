#include "pipex_bonus.h"

void setup_here_doc(int argc, char **argv, int *num, int *fd_out)
{
	*num = 3;
	here_doc(argc, argv);
	*fd_out = file_opener(argv[argc - 1], 'h');
}

void	here_doc(int argc, char **argv)
{
	int		fd[2];
	int		pid;

	if (argc < 6)
		ft_error("Error: wrong count of arguments");
	if (pipe(fd) == -1)
		perror("ERROR(here_doc pipe)");
	pid = fork();
	if (pid == -1)
		ft_perror("ERROR(here_doc fork)");
	if (pid == 0)
		write_to_limiter(fd, argv[2]);
	close(fd[1]);
	if (dup2(fd[0], STDIN_FILENO) == -1)
		ft_perror("ERROR(here_doc dup)");
	close(fd[0]);
	waitpid(pid, NULL, 0);
}

void	write_to_limiter(int *fd, char *limiter)
{
	char	*line;

	close(fd[0]);
	ft_putstr_fd("pipe heredoc> ", 1);
	line = get_next_line(0);
	while (line)
	{
		clean_line(line);
		if (ft_strcmp(limiter, line) == 0)
		{
			free(line);
			close(fd[1]);
			exit(EXIT_SUCCESS);
		}
		ft_putstr_fd("pipe heredoc> ", 1);
		write_line_to_fd(fd[1], line);
		free(line);
		line = get_next_line(0);
	}
	free(line);
	close(fd[1]);
	ft_perror("ERROR(write data fail in heredoc)");
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
