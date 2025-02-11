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

void	exec_cmd(char *cmd, char **envp)
{
	int	fd[2];
	int	pid;

	if (pipe(fd) == -1)
		ft_perror("ERROR(pipe in exec_cmd)");
	pid = fork();
	if (pid == -1)
		ft_perror("ERROR(fork in exec_cmd)");
	if (pid == 0)
	{
		close(fd[0]);
		if (dup2(fd[1], STDOUT_FILENO) == -1)
			ft_perror("ERROR(dup2 in exec_cmd)");
		close(fd[1]);
		ft_exec(cmd, envp);
	}
	close(fd[1]);
	if (dup2(fd[0], STDIN_FILENO) == -1)
		ft_perror("ERROR(dup2 in exec_cmd)");
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

void	execute_final_command(char **argv, char **envp, int argc)
{
	int	pid;

	pid = fork();
	if (pid == -1)
		ft_perror("ERROR(fork1)");
	if (pid == 0)
		ft_exec(argv[argc - 2], envp);
	waitpid(pid, NULL, 0);
}

void	process_commands(char **argv, char **envp, int num, int argc)
{
	while (num < argc - 2)
		exec_cmd(argv[num++], envp);
}

void	pipex_bonus(int argc, char **argv, char **envp)
{
	int	num;
	int	fd_in;
	int	fd_out;

	if (ft_strcmp(argv[1], "here_doc") == 0)
		setup_here_doc(argc, argv, &num, &fd_out);
	else
	{
		num = 2;
		fd_in = file_opener(argv[1], 'I');
		fd_out = file_opener(argv[argc - 1], 'O');
		if (dup2(fd_in, STDIN_FILENO) == -1)
			ft_perror("ERROR(dup2 input multiple pipe)");
	}
	process_commands(argv, envp, num, argc);
	if (dup2(fd_out, STDOUT_FILENO) == -1)
		ft_perror("ERROR(dup2 output)");
	execute_final_command(argv, envp, argc);
}
