
#include "pipex_bonus.h"

void	setup_here_doc(int argc, char **argv, int *num, int *fd_out)
{
	int	status;

	*num = 3;
	status = here_doc(argc, argv);
	if (status != 0)
		exit(status);
	*fd_out = file_opener(argv[argc - 1], 'h');
}

void	process_commands(char **argv, char **envp, int num, int argc, int *last_status)
{
	while (num < argc - 2)
		exec_cmd(argv[num++], envp, last_status);
}

int	pipex_bonus(int argc, char **argv, char **envp)
{
	int	num;
	int	fd_in;
	int	fd_out;
	int	last_status;

	if (ft_strcmp(argv[1], "here_doc") == 0)
		setup_here_doc(argc, argv, &num, &fd_out);
	else
	{
		num = 2;
		fd_in = file_opener(argv[1], 'I');
		if (dup2(fd_in, STDIN_FILENO) == -1)
			ft_perror("ERROR(dup2 input multiple pipe)");
		close(fd_in);
		fd_out = file_opener(argv[argc - 1], 'O');
	}
	process_commands(argv, envp, num, argc, &last_status);
	if (dup2(fd_out, STDOUT_FILENO) == -1)
		ft_perror("ERROR(dup2 output)");
	close(fd_out);
	execute_final_command(argv, envp, argc, &last_status);
	return (last_status);
}
