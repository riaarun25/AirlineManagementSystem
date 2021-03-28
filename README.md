# Airline Management System
A simple C language program to show various data structures and search alogorithms.
#

## *Data Structures used:*
###### -> Linked Lists
###### -> Arrays
###### -> Queues
#

## *Modules*
#### *-> Database ( )* 
###### Return type: void 
###### Arguments: none
###### The first module that is called when the program begins execution. 

#### *-> Newdir ( )* 
###### Return type: void 
###### Arguments: none
###### This module is used mainly for creating files and directories. 

#### *-> Mainmenu ( )* 
###### Return type: void 
###### Arguments: char user [20], char pw [20]
###### This module provides options to the user to create a new booking, cancel a booking and to log out.
###### Signup ( ): This takes care of creating new files for the user inside the database directory. 
###### Login ( ): When this is called it asks for username and password from the user. 

#### *-> Booking ( )* 
###### Return type: void 
###### Arguments: char user [20], char pw [20]
###### This module offers the user to selects the basis on which they will be booking their trip. 
###### Display(): Displays the details of flight from the array of flights based on the index. 

#### *-> Cancelbooking ( )*
###### Return type: void 
###### Arguments: char user [20], char pw [20]
###### The function opens the file of the user and displays all the bookings that the user has done. The user can opt which one to cancel, then the user file is deleted and the new file is renamed after the username. 
###### Check_upcoming ( ): This function opens the file of the user and then checks all the bookings one by one and then displays them. 
