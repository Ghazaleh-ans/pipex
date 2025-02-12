#include "pipex_bonus.h"

int	here_doc(int argc, char **argv)
{
	int	fd[2];
	int	pid;
	int	status;

	if (argc < 6)
	{
		ft_putstr_fd("Error: heredoc usage error\n", 2);
		return (1);
	}
	if (pipe(fd) == -1)
		return (1);
	pid = fork();
	if (pid == -1)
		return (1);
	if (pid == 0)
		write_to_limiter(fd, argv[2]);
	close(fd[1]);
	if (dup2(fd[0], STDIN_FILENO) == -1)
	{
		close(fd[0]);
		return (1);
	}
	close(fd[0]);
	waitpid(pid, &status, 0);
	return ((status & 0xFF00) >> 8);
}

void	handle_heredoc_line(int fd, char *line, char *limiter, int *status)
{
	clean_line(line);
	if (ft_strcmp(limiter, line) == 0)
	{
		free(line);
		close(fd);
		*status = 0;
		exit(0);
	}
	ft_putstr_fd("pipe heredoc> ", 1);
	if (write_line_to_fd(fd, line) == -1)
		*status = 1;
	free(line);
}

void	write_to_limiter(int *fd, char *limiter)
{
	char	*line;
	int		status;

	status = 0;
	close(fd[0]);
	ft_putstr_fd("pipe heredoc> ", 1);
	line = get_next_line(0);
	while (line)
	{
		handle_heredoc_line(fd[1], line, limiter, &status);
		line = get_next_line(0);
	}
	free(line);
	close(fd[1]);
	exit(status);
}

int	write_line_to_fd(int fd, char *line)
{
	if (write(fd, line, ft_strlen(line)) == -1)
		return (-1);
	if (write(fd, "\n", 1) == -1)
		return (-1);
	return (0);
}

void	clean_line(char *line)
{
	char	*trimmed_line;

	trimmed_line = line;
	while (*trimmed_line && *trimmed_line != '\n')
		trimmed_line++;
	*trimmed_line = '\0';
}
