<h1 align=center>
  42 Cursus
 </h1>
<h2 align=center>
  minishell
</h2>
<h2 align=center>

  ![minishell_logo](https://github.com/beatrizdile/beatrizdile-utils/blob/master/minishellm.png)
</h2>
  Minishell is a project designed to give you hands-on experience in building a basic Unix-like shell. In this project, it was developed a simplified shell that allows users to interact with the operating system through a command-line interface. The goal is to implement core features of a shell, including command execution, built-in commands, input/output redirection, and the use of pipes.
  Inside this repository, you can see all the code that has been created for the Minishell project, including the mandatory part and the bonus part. The project was done in collaboration with <a href="https://github.com/GiovannaCoqueiro">Giovanna Coqueiro</a>


<h3 align=left>
    Mandatory
</h3>

<p>
	Create a program that works like a shell, following the next conditions.
</p>

<ul>
	<li>Display a prompt when waiting for a new command</li>
	<li>Have a working history</li>
	<li>Search and launch the right executable(using relative path, absolute path or just the the name of the command)</li>
	<li>Handle '</li>
	<li>Handle "</li>
	<li>Implement redirections: '<', '>', '<<', '>>'</li>
	<li>Implemente pipes</li>
	<li>Handle environment variables</li>
	<li>Handle exit status with $?</li>
	<li>Handle signals: 'ctrl-C', 'ctrl-\', 'ctrl-D'</li>
	<li>Implement builtins: 'cd', 'pwd', 'echo', 'exit', 'unset', 'export, 'env'</li>
</ul>

you can run it with:
```sh
  $> ./minishell
```

---

<h3 align=left>
    Bonus
</h3>

| Bonus | Status |
| :---: | :--- |
| Manage '\|\|' and '&&' with parenthesis | not implemented |
| Manage wildcards | not implemented |
| Manage variables expansion inside ' and " | implemented |

---

<h2>
    Instructions to use
</h2>
Clone this repository in you local computer using a terminal:

```sh
$> git clone git@github.com:beatrizdile/42sp-minishell.git
```

After cloning the project in your local reposiory you can run some commands you can find in Makefile:
<ul>
	<li>$> <b>make all:</b> or just <b>make</b> compiles the project</li>
	<li>$> <b>make clean:</b> deletes the object files created during compilation</li>
	<li>$> <b>make fclean:</b> executes the <b>clean</b> command and also deletes the binary created</li>
	<li>$> <b>make re:</b> executes the <b>fclean</b> command followed by the <b>all</b> command</li>
	<li>$> <b>make bonus:</b> compiles the project</li>
	<li>$> <b>make rebonus:</b> executes the <b>fclean</b> command followed by the <b>rebonus</b> command</li>
	<li>$> <b>make run:</b> executes <b>all</b> and run the program</li>
	<li>$> <b>make val:</b> executes <b>all</b> and run the program with valgrind</li>
</ul>
