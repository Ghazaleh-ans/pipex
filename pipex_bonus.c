/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gansari <gansari@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 15:36:57 by gansari           #+#    #+#             */
/*   Updated: 2025/02/07 15:37:00 by gansari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"
#include <stdio.h>

void	exec_cmd(char *cmd, char **envp)
{
	int	fd[2];
	int	pid;

	if (pipe(fd) == -1)
		ft_perror("ERROR - 3");
	pid = fork();
	if (pid == -1)
		ft_perror("ERROR - 4");
	if (pid == 0)
	{
		close(fd[0]);
		if (dup2(fd[1], STDOUT_FILENO) == -1)
			ft_perror("ERROR - 5");
		close(fd[1]);
		ft_exec(cmd, envp);
	}
	close(fd[1]);
	if (dup2(fd[0], STDIN_FILENO) == -1)
		ft_perror("ERROR - 6");
	close(fd[0]);
	waitpid(pid, NULL, 0);

}

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

void	pipex_bonus(int argc, char **argv, char **envp)
{
	int	pid;
	int	num;
	int	fd_in;
	int	fd_out;

	if (ft_strcmp(argv[1], "here_doc") == 0)
	{
		num = 3;
		here_doc(argc, argv);
		fd_out = file_opener(argv[argc - 1], 'h');
	}
	else
	{
		num = 2;
		fd_in = file_opener(argv[1], 'I');
		fd_out = file_opener(argv[argc - 1], 'O');
		if (dup2(fd_in, STDIN_FILENO) == -1)
			ft_perror("ERROR(dup2 input multiple pipe)");
	}
	while (num < argc - 2)
		exec_cmd(argv[num++], envp);
	if (dup2(fd_out, STDOUT_FILENO) == -1)
		ft_perror("ERROR(dup2 output)");
	pid = fork();
	if (pid == -1)
		ft_perror("ERROR(fork1)");
	if (pid == 0)
		ft_exec(argv[argc - 2], envp);
}
