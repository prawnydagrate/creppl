# Creppl
A very crappy read-eval-print loop for C

## Development status
Creppl is not functional yet.  

TODOS:
* use OS-provided temp files
* figure out how to compile and execute

## Why not to use Creppl
This is basically a fake REPL, but it's just enough to do what I want it to do.  
It looks at brackets to identify code blocks, so good luck using them in strings lol.
Maybe something like this:
```c
const char LPAREN = 0x28;
printf("Shouldn't have downloaded this thing :%c\n", LPAREN);
```
Multiline comments can also be somewhat problematic, as this:
```
>>> #include <stdio.h>
>>> puts("Goodbye, world!");
>>> /*
>>> #include "nuke.h"
>>> Uncommenting the above line could be fatal.
>>> */
```
is translated into this:
```c
#include <stdio.h>
#include "nuke.h"

int main() {
  puts("Goodbye, world!");
  /*
  Uncommenting the above line could be fatal.
  */
}
```
Also, the entire file, including previously executed statements, is compiled and executed every time a new statement is finished. For example:
```
>>> #include <stdio.h>
>>> char *message = "...---...";
>>> printf("Help, %s\n", message);
```
This prints `Help, ...---...` as expected. However, adding this line:
```
>>> puts("SOS");
```
reruns all of the code, outputting:
```
Help, ...---...
SOS
```
(notice the first call to `printf` was rerun)
