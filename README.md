# OSH

---

OSH is a simple implementation of a shell in C. It demonstrates the basics of how a shell works. That is: read, parse, fork, exec, and wait.

## For Now: 
- Commands must be on a single line.
- Arguments must be separated by whitespace.
- No quoting arguments or escaping whitespace.
- No piping or redirection.
- Only builtins are: cd, help, exit.

# Running
---- 

Use `gcc -o osh src/main.c` to compile, and then `./lsh` to run.
