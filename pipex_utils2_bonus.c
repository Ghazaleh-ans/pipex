#include "pipex_bonus.h"

void	child_process(int *fd, char *cmd, char **envp)
{
	close(fd[0]);
	if (dup2(fd[1], STDOUT_FILENO) == -1)
	{
		close(fd[1]);
		exit(1);
	}
	close(fd[1]);
	ft_exec(cmd, envp);
}

void	parent_process(int *fd, int pid, int *last_status)
{
	int	status;

	close(fd[1]);
	if (dup2(fd[0], STDIN_FILENO) == -1)
	{
		close(fd[0]);
		exit(1);
	}
	close(fd[0]);
	waitpid(pid, &status, 0);
	*last_status = (status & 0xFF00) >> 8;
}

void	exec_cmd(char *cmd, char **envp, int *last_status)
{
	int	fd[2];
	int	pid;

	if (pipe(fd) == -1)
		exit(1);
	pid = fork();
	if (pid == -1)
		exit(1);
	if (pid == 0)
		child_process(fd, cmd, envp);
	parent_process(fd, pid, last_status);
}

void	execute_final_command(char **argv, char **envp, int argc, int *last_status)
{
	int	pid;
	int	status;

	pid = fork();
	if (pid == -1)
		ft_perror("ERROR(fork1)");
	if (pid == 0)
		ft_exec(argv[argc - 2], envp);
	waitpid(pid, &status, 0);
	*last_status = (status & 0xFF00) >> 8;
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
