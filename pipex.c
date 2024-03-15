/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kahmada <kahmada@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 00:31:08 by kahmada           #+#    #+#             */
/*   Updated: 2024/03/15 00:31:08 by kahmada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void child_process(const char *cmd, int pipefd[]) {
    close(pipefd[0]); // Close read end of the pipe
    if (dup2(pipefd[1], STDOUT_FILENO) == -1) {
        print_error("Duplication of file descriptor failed\n");
        exit(EXIT_FAILURE);
    }
    close(pipefd[1]); // Close write end of the pipe
    const char *cmd_args[] = {cmd, NULL}; // Modified to const char *
    execve(cmd, (char *const *)cmd_args, NULL);
    // If execve fails
    print_error("Failed to execute ");
    print_error(cmd);
    print_error("\n");
    exit(EXIT_FAILURE);
}

void parent_process(const char *cmd, int pipefd[]) {
    close(pipefd[1]); // Close write end of the pipe
    if (dup2(pipefd[0], STDIN_FILENO) == -1) {
        print_error("Duplication of file descriptor failed\n");
        exit(EXIT_FAILURE);
    }
    close(pipefd[0]); // Close read end of the pipe
    const char *cmd_args[] = {cmd, NULL}; // Modified to const char *
    execve(cmd, (char *const *)cmd_args, NULL);
    // If execve fails
    print_error("Failed to execute ");
    print_error(cmd);
    print_error("\n");
    exit(EXIT_FAILURE);
}
int main(int argc, char *argv[])
{
    // Check arguments
    if (argc != 5)
    {
        print_error("Usage: ");
        print_error(argv[0]);
        print_error(" infile cmd1 cmd2 outfile\n");
        exit(EXIT_FAILURE);
    }
    // Extract arguments
    char *infile = argv[1];
    char *cmd1 = argv[2];
    char *cmd2 = argv[3];
    // Check if infile exists
    if (access(infile, F_OK) == -1) {
        print_error("Input file '");
        print_error(infile);
        print_error("' does not exist\n");
        exit(EXIT_FAILURE);
    }
    // Create a pipe
    int pipefd[2];
    if (pipe(pipefd) == -1) {
        print_error("Pipe creation failed\n");
        exit(EXIT_FAILURE);
    }
    // Execute the first command
    pid_t pid1 = fork();
    if (pid1 < 0) {
        print_error("Fork failed\n");
        exit(EXIT_FAILURE);
    } else if (pid1 == 0) {
        // Child process for cmd1
        child_process(cmd1, pipefd);
    }
    // Execute the second command
    pid_t pid2 = fork();
    if (pid2 < 0) {
        print_error("Fork failed\n");
        exit(EXIT_FAILURE);
    } else if (pid2 == 0) {
        // Child process for cmd2
        parent_process(cmd2, pipefd);
    }
    // Close pipe ends in the parent process
    close(pipefd[0]);
    close(pipefd[1]);
    // Wait for child processes to finish
    waitpid(pid1, NULL, 0);
    waitpid(pid2, NULL, 0);
    return 0;
}