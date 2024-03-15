/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_pipex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kahmada <kahmada@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 22:12:41 by kahmada           #+#    #+#             */
/*   Updated: 2024/03/15 01:56:06 by kahmada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	error(void)
{
	perror("\033[31mError");
	exit(EXIT_FAILURE);
}

void print_error(const char *message) {
    write(STDERR_FILENO, message, ft_strlen(message));
}

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
	{
		i++;
	}
	return (i);
}
/* Function that take the command and send it to find_path
 before executing it. */
// void	execute(char *argv, char **envp)
// {
// 	char	**cmd;
// 	int 	i;
// 	char	*path;
	
// 	i = -1;
// 	cmd = ft_split(argv, ' ');
// 	path = find_path(cmd[0], envp);
// 	if (!path)	
// 	{
// 		while (cmd[++i])
// 			free(cmd[i]);
// 		free(cmd);
// 		error();
// 	}
// 	if (execve(path, cmd, envp) == -1)
// 		error();
// }
