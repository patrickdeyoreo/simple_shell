# An implementation of sh in C programming language

## Overview
Simple Shell is a Holberton School pair project. The general goal of the project is to Write a simple UNIX command interpreter. 
### Content
* [General Requirements](#General-Requirements)
* [Expected output](#Expected-output)
* [List of allowed functions](#List-of-allowed-functions)
* [Compilation](#Compilation)
* [Testing](#Testing)
* [Tasks](#Tasks)
- [Mandatory](#Mandatory)
- [Advanced](#Advanced)

### General Requirements
* Allowed editors: vi, vim, emacs
* All your files will be compiled on Ubuntu 14.04 LTS
* Your C programs and functions will be compiled with gcc 4.8.4 using the flags -Wall -Werror -Wextra and -pedantic
* All your files should end with a new line
* A README.md file, at the root of the folder of the project is mandatory
* Your code should use the Betty style. It will be checked using betty-style.pl and betty-doc.pl
* No more than 5 functions per file
* All your header files should be include guarded
* Use system calls only when you need to
### Expected output
* Unless specified otherwise, your program must have the exact same output as sh (/bin/sh) as well as the exact same error output.
* The only difference is when you print an error, the name of the program must be equivalent to your argv[0]

- Example of error with sh:
```
$ echo "qwerty" | /bin/sh
/bin/sh: 1: qwerty: not found
$ echo "qwerty" | /bin/../bin/sh
/bin/../bin/sh: 1: qwerty: not found
$
```
- Same error with your program hsh:

```
$ echo "qwerty" | ./hsh
./hsh: 1: qwerty: not found
$ echo "qwerty" | ./././hsh
./././hsh: 1: qwerty: not found
$
```
### List of allowed functions
* access (man 2 access)
* chdir (man 2 chdir)
* close (man 2 close)
* closedir (man 3 closedir)
* execve (man 2 execve)
* exit (man 3 exit)
* _exit (man 2 _exit)
* fflush (man 3 fflush)
* fork (man 2 fork)
* free (man 3 free)
* getcwd (man 3 getcwd)
* getline (man 3 getline)
* isatty (man 3 isatty)
* kill (man 2 kill)
* malloc (man 3 malloc)
* open (man 2 open)
* opendir (man 3 opendir)
* perror (man 3 perror)
* read (man 2 read)
* readdir (man 3 readdir)
* signal (man 2 signal)
* stat (__xstat) (man 2 stat)
* lstat (__lxstat) (man 2 lstat)
* fstat (__fxstat) (man 2 fstat)
* strtok (man 3 strtok)
* wait (man 2 wait)
* waitpid (man 2 waitpid)
* wait3 (man 2 wait3)
* wait4 (man 2 wait4)
* write (man 2 write)

### Compilation
```
gcc -Wall -Werror -Wextra -pedantic *.c -o hsh 
```
### Testing
- Interactive mode:
```
$ ./hsh
($) /bin/ls
hsh main.c shell.c
($)
($) exit
$
```

- Non-interactive mode:
```
$ echo "/bin/ls" | ./hsh
hsh main.c shell.c test_ls_2
$
$ cat test_ls_2
/bin/ls
/bin/ls
$
$ cat test_ls_2 | ./hsh
hsh main.c shell.c test_ls_2
hsh main.c shell.c test_ls_2
$
```
### Tasks
- Mandatory:
0. README, man, AUTHORS
- Write a README
- Write a man for your shell.
- You should have an AUTHORS file at the root of your repository, listing all individuals having contributed content to the repository.
1. Betty would be proud
- Write a beautiful code that passes the Betty checks

2. Simple shell 0.1
- Write a UNIX command line interpreter.
- Your Shell should:
1. Display a prompt and wait for the user to type a command. A command line always ends with a new line.
2. The prompt is displayed again each time a command has been executed.
3. The command lines are simple, no semicolons, no pipes, no redirections or any other advanced features.
4. The command lines are made only of one word. No arguments will be passed to programs.
5. If an executable cannot be found, print an error message and display the prompt again.
6. Handle errors.
7. You have to handle the “end of file” condition (Ctrl+D)
- You don’t have to:
1. use the PATH
2. implement built-ins
3. handle special characters : ", ', `, \, *, &, #
be able to move the cursor
handle commands with arguments

3. Simple shell 0.2
- Handle command lines with arguments

4. Simple shell 0.3
- Handle the PATH

5. Simple shell 0.4
- Implement the exit built-in, that exits the shell
- Usage: exit
- You don’t have to handle any argument to the built-in exit

6. Simple shell 1.0
- Implement the env built-in, that prints the current environment

7. Write a blogpost "What happens when you type ls -l in the shell"

-Advanced
0. Test suite 
- Contribute to a test suite for your shell

1. Simple shell 0.1.1
- Write your own getline function

2. Simple shell 0.2.1
- Write your own strtok function

3. Simple shell 0.4.1
- handle arguments for the built-in exit

4. Simple shell 0.4.2
- Handle Ctrl+C: your shell should not quit when the user inputs ^C

5. setenv, unsetenv
- Implement the setenv and unsetenv builtin commands

6. cd
- Implement the builtin command cd

7. ;
- Handle the commands separator ;

8. && and ||
- Handle the && and || shell logical operators

9. alias 
- Implement the alias builtin command

10. Variables
- Handle variables replacement
- Handle the $? variable
- Handle the $$ variable

11. Comments
- Handle comments (#)

12. help 
- Implement the help built-in

13. history
- Implement the history built-in, without any argument

14. File as an input 
- Your shell should take a file as a command line argument

## Authors
* [Patrick Deyoreo](https://github.com/patrickdeyoreo)
* [Banu Sapakova](https://github.com/banuaksom)
