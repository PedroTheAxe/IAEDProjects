# IAEDProjects
Both of my Introduction to Algorithms and Data Structures course projects

## Project 1

Room reservation system where rooms and reunions can be booked. Interaction with the program occurs by sentences composed of a letter (command) and a variable number of arguments.

| Command | Action |
|:---:|:---|
| __a__ | Adds a new event |
| __l__ | Lists all events by chronological order |
| __s__ | Lists all events in a given room by chronological order |
| __r__ | Removes an event |
| __i__ | Changes the start time of an event |
| __t__ | Changes the duration of an event |
| __m__ | Changes the room of an event |
| __A__ | Adds an attendee to an event |
| __R__ | Removes an attendee from an event |
| __x__ | Closes the program |

### Examples

Adding an event: `a description:date:start:duration:room:organizer:attendees`

Changing an event's room: `m description:new_room`

List all events in a given room by chronological order: `s room`

### Compiling and executing the program

`$ gcc -Wall -Wextra -ansi -pendatic -o proj1 *.c`

You can now either interact directly with the program through the command line or run specific test files.

`$ ./proj1 < test.in > test.myout`

## Project 2

Contact management system that allows to link an e-mail and a phone number to a name. Interaction with the program occurs by sentences composed of a letter (command) and a variable number of arguments. An hashtable was implemented
in this project to *significantly* improve performance

| Comando | Acção |
|:---:|:---|
| __a__ | Adds a new contact |
| __l__ | Lists all contacts by the order they were introduced in |
| __p__ | Searches for a contact |
| __r__ | Removes a contact |
| __e__ | Changes the e-mail address of a contact |
| __c__ | Counts the number of occurences of a specific e-mail domain |
| __x__ | Closes the program |

### Examples

Adding a contact: `a name e-mail phone_number`

Changing the e-mail of a contact: `e name new_e-mail`

List all contacts: `l`

### Compiling and executing the program

`$ gcc -Wall -Wextra -ansi -pedantic -o proj2 *.c`

You can now either interact directly with the program through the command line or run specific test files.

`$ ./proj2 < test.in > test.myout`

