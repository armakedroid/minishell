# 🐚 Minishell
*As beautiful as a shell*

---

## 📘 Overview
The **Minishell** project is about creating a simple shell, similar to Bash.  
You will gain extensive knowledge about **processes, file descriptors, and command parsing**.

---

## 🎯 Objectives
- Implement a working shell in **C**.
- Handle built-in commands and environment variables.
- Implement **redirections** and **pipes**.
- Handle **signals** (ctrl-C, ctrl-D, ctrl-\) correctly.
- Apply proper **memory management** and Norm compliance.
- Understand how shells interpret commands and execute programs.

---

## ⚙️ Features

### Mandatory
- Display a prompt when waiting for commands.
- Maintain a **command history**.
- Search for executables using `$PATH`, relative or absolute paths.
- Handle signals using **one global variable** for signal numbers only.
- Support **quotes**:
  - `'` prevents interpretation of metacharacters.
  - `"` prevents interpretation except `$` (variables).
- Support **redirections**:
  - `<` input redirection
  - `>` output redirection
  - `>>` append mode
  - `<<` heredoc with delimiter
- Support **pipes** (`|`) to connect commands.
- Support **environment variables** (`$VAR`) and `$?` (last exit status).
- Implement built-in commands:
  - `echo [-n]`
  - `cd`
  - `pwd`
  - `export`
  - `unset`
  - `env`
  - `exit`

### Signal behavior (interactive mode)
| Signal | Behavior |
|--------|----------|
| Ctrl-C | Display new prompt on a new line |
| Ctrl-D | Exit the shell |
| Ctrl-\ | Does nothing |

---

### Bonus
- Logical operators `&&` and `||` with parentheses for priorities.
- Wildcards `*` expansion for the current working directory.

> **Note:** Bonus is evaluated only if the mandatory part is implemented perfectly.

---

## 📝 Program Usage

**Program Name:** `minishell`  
**Arguments:** None required  

**Example:**
```bash
$> ./minishell
minishell> echo "Hello world"
Hello world
minishell> ls | grep ".c"
main.c
utils.c
minishell> cd ..
minishell> pwd
/home/user/projects
minishell> exit
$
