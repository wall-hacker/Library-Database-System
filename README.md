````
  _   _           _     ____        _          _ 
 | | | | __ _ ___| |__ | __ )  __ _| |__   ___| |
 | |_| |/ _` / __| '_ \|  _ \ / _` | '_ \ / _ \ |
 |  _  | (_| \__ \ | | | |_) | (_| | |_) |  __/ |
 |_| |_|\__,_|___/_| |_|____/ \__,_|_.__/ \___|_|
                                                
````
- - -
### Description
- - -  

This project is a library backend system, 'The Library of HashBabel' that simulates the functionality of a library, allowing users to perform operations such as adding, borrowing, and returning books, as well as managing user accounts. It utilizes data structures like linked lists and hash tables to efficiently store and manage books and user information, while implementing various commands to handle library operations effectively.

- - -
### Structure && Implementation 
- - -
The main function of the program creates the two hashtables for the library and
users, reads commands as input and treats them in a repetitive cycle, while,
until the command 'EXIT' is given. For every command, the corresponding
procedure is called, where input is read, errors are dealt with and the
neccessary operations for the command are met. After 'EXIT' is given, the
books and users are sorted and printed, and the memory is freed.

Here is a list of all valid commands:

**1] 'ADD_BOOK'**

Command that adds a new book in the library hashtable. If the size of the
hashtable becomes greater than the capacity, an operation of resize will take
place, doubling the capacity. Also, if the book was already in the library, 
the book content will be erased (hashtable of content freed), and a new one
will replace it.

**2] 'GET_BOOK'**

This command will have as output the printing of the book's name, rating, and
purchases.

**3] 'RMV_BOOK'**

In order to remove a book from the library, first the hashtable of content is
freed, and then the entry of the book into the library is erased.

**4] 'ADD_DEF'**

This command adds a new definition in the content hashtable of a book. If the
key word was already in the book, its correspoding value is updated with the
new definition given. If the size of the hashtable of definitions is greater
then the capacity, the hashtable will be resized with double capacity.

**5] 'GET_DEF'**

This command prints the definition given to the specified word from a book.

**6] 'RMV_DEF'**

To remove a definition from a book, the function to remove an entry from a
hashtable is used.

**7] 'ADD_USER'**

This command adds a new user in the user system (or hashtable), and initializes
the information of the user. Initially, each user is given 100 points. Also,
when the size of the hashtable of users becomes larger than the capacity, the
hashtable is resized with doulbe capacity.

**8] 'BORRORW'**

The operation of borrowing makes the neccessary modifications to the parameters
of the book value and user values so that the book cannot be borrowed by another
user, and the user cannot borrow another book until he returns it.

**9] 'RETURN'**

This operation makes a book available for borrowing again, and a user valid to
borrow another book, if not banned. If the user returned the book earlier than
the deadline, the user's points increase by the number of days remained to the
deadline. If the user was late with the book, he loses double the amount of
days passed since the deadline in points. If his score becomes negative, the
user is banned.

**10] 'LOST'**

When a book is lost by a user, the user loses 50 points, and the book is erased
from the library. Again, if the points of the user got negative, the user is
banned from the library.

**11] 'EXIT'**

In order to end the program, the books are sorted based on their rating, then
by purchase, and last by name, if rating and purchases are equal. Users are
also sorted based on their points, or by name if points are equal. The books 
and users are then printed with their information, and at the end, memory of
library and user hashtables are freed.

- - -
### Feedback && Comments
- - -

This was a very interesting project, as it was the first time I had to implement
hashtables and linked lists from scrath in a project. I learned a lot about how to use these data structures efficiently and how to manage memory in a program.
