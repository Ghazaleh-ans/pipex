/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gansari <gansari@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 15:21:06 by gansari           #+#    #+#             */
/*   Updated: 2025/02/07 15:21:09 by gansari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include <fcntl.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <sys/wait.h>
# include <string.h>
# include <errno.h>
# include "./Libft/libft.h"

//main functions
void	pipex_bonus(int argc, char **argv, char **envp);
void	exec_cmd(char *cmd, char **envp);
void	ft_exec(char *cmd, char **envp);
void	execute_final_command(char **argv, char **envp, int argc);
void	process_commands(char **argv, char **envp, int num, int argc);

//utils
int		file_opener(char *path, char flag);
char	**parse_path(char **envp);
char	*ft_makepath(char const *path, char const *cmd);
void	free_array(char **arr_to_free);

//heredoc
void	setup_here_doc(int argc, char **argv, int *num, int *fd_out);
void	clean_line(char *line);
void	write_line_to_fd(int fd, char *line);
void	here_doc(int argc, char **argv);
void	write_to_limiter(int *fd, char *limiter);

//multiple pipes
void	setup_multiple_pipes(char **argv, int argc, int *num, int *fd_in, int *fd_out);

#endif
