#include "pipex_bonus.h"

int main(int argc, char **argv, char **envp)
{
	if (argc < 5)
	{
		ft_putstr_fd("Error: Invalid number of arguments\n", 2);
		ft_putstr_fd("Usage: ./pipex file1 cmd1 cmd2 file2\n", 2);
		ft_putstr_fd("   or: ./pipex here_doc LIMITER cmd1 cmd2 file\n", 2);
		return (1);
	}
	return (pipex_bonus(argc, argv, envp));
}
