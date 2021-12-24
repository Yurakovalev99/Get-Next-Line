# Get-Next-Line
21-school 1st level project

Function return the line that has just been read. If there is nothing
else to read or if an error has occurred it will return NULL.


Program must compile with the flag -D BUFFER_SIZE=xx which will be used as the buffer size for the read calls in your get_next_line. 

```
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 <files>.c.  
