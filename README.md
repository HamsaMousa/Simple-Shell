# README Shell

Shell Project ROB4 - 2022-2022 - ALONSO Benito et MOUSA Hamsa

---

This README briefly presents the possible commands for our Shell as well as the instructions for launching it.

# 📂Compilation and Launching the Shell

To launch our shell, you need to enter the following commands in the terminal:

`$ make`

`$ ./shell`

To exit our shell, simply type the **exit** command:

`$ exit`

ou

`$ Exit`

# ⌨️Available Commands and Explanations

In our recreated terminal, we've aimed to replicate the Linux shell as accurately as possible. Consequently, the following prompt appears each time:

![Untitled](README%20Shell%2025d1468364cd478f90ee82540c5a97d1/Untitled.png)

The user can then enter the desired commands.

To execute functions, simply write the function name as in a normal shell and enter the desired arguments, with a maximum of 20 arguments per command line.

## 1. Basic Functions Without Arguments

These are the commands directly executed by the normal shell (excluding built-in commands).

In this first part of the project, the goal was to successfully execute these commands with or without arguments.

### 1.1 Execution of Programs Without Arguments in the Foreground

All classic functions are supported through the **execvp** call.

The following are among the most useful commands:

```c
$ ls
$ who
$ ps
```

Other commands like **mkdir** to create a new directory or **touch filename.txt** to create a new text file are also supported.

### 1.2 Basic Functions with Arguments

Basic functions can be supplemented with arguments such as '-a', '-l', '-o', '-x'.

Example: **ls** function with arguments:

`$ ls -l` 

`$ ls -l -a`

For each function, the argument '--help' will also display help on how to use a specific command.

### 1.3 Built-in Commands

These commands are directly interpreted by the shell itself, so creating a new process would be unnecessarily resource-intensive.

Here, they are handled with the **cd** and **pwd** functions.

The **cd** command allows changing directories by entering the target directory's path. 
For example, '$ cd /home/user/documents' allows you to navigate to the "documents" directory located within the "user" directory at the root of the file system.

`$ cd ..` permettra de revenir au répertoire précedent.

Error handling is also implemented, so if changing the directory is not possible, a message will be displayed.

The **pwd** command displays the current directory's path. This can be useful to know where you are in the file system.

## 2. Advanced Functions

Note: The following functions cannot be combined. For example:

'$ ls &' and '$ ls | wc' will work, but '$ ls | wc &' is not supported.

### 2.1 Background Commands

The **&** symbol allows you to run a command in the background. This means you can continue using your shell while the command is being executed.

We also considered whether or not the **&** is attached to other arguments:

`$ ls&`

`$ ls &`

And also when there are multiple arguments:

`$ ls -a -l&`

`$ ls -a -l &`

With background functions, just like in a real terminal, the user will regain control with the classic prompt before the command output appears.

![Untitled](README%20Shell%2025d1468364cd478f90ee82540c5a97d1/Untitled.png)

Then the command result will be added.

Example of behavior:

![Untitled](README%20Shell%2025d1468364cd478f90ee82540c5a97d1/Untitled%201.png)

Note: Multiple commands in the background are not supported, such as 'who & ls'.

### 2.2 Pipes

The pipe **|** allows redirecting the standard output of one command to the standard input of another command.

For example, the following command counts the number of words displayed by 'ls -l':

`$ ls -l | wc`   

Note: We will only handle the case with a single pipe in the form: command1 | command2.

### 2.3 Redirection of stdout

The redirection **>** allows redirecting the standard output of a command to a file. If the specified filename does not match an existing file, the file will be created; otherwise, it will be overwritten.

For instance, the command below outputs the list of files and their permissions to the file 'file1.txt':

`$ ls -l > fichier1.txt` 

If you start the command with the word **echo**, what is written before the redirection symbol **>** will be copied into the file.

For example, the following command copies the word "hello" into the file 'file1.txt':

`$ echo "bonjourr"> fichier1.txt` 

Running the command '$ cat file1.txt' then produces:

![Untitled](README%20Shell%2025d1468364cd478f90ee82540c5a97d1/Untitled%202.png)

The only difference from the real shell's behavior is that here the quotation marks “ “ are also sent to 'file1.txt'.

To simply send “hello”, you would write:

![Untitled](README%20Shell%2025d1468364cd478f90ee82540c5a97d1/Untitled%203.png)
