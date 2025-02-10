#include "pipex_bonus.h"

void	setup_multiple_pipes(char **argv, int argc, int *num, int *fd_in, int *fd_out)
{
	*num = 2;
	*fd_in = file_opener(argv[1], 'I');
	*fd_out = file_opener(argv[argc - 1], 'O');
	if (dup2(*fd_in, STDIN_FILENO) == -1)
		ft_perror("ERROR(dup2 input multiple pipe)");
}
