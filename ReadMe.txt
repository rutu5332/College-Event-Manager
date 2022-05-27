************************** READ ME *******************************

This Program is made for the collegeFestival called "SYNAPSE".
In which their are lots of Event for which a user can Register.
there are 2 modules here
1. Admin
2. User

Admin is handled over server while users are handled over clients.
Multiple clients are allowed at a time.
But if server quits its all clients will be exited.

--> Admin:
Admin can 
  - create event
  - view the event information
  - view the list of registered users
  - Modify event Information
  - Chnage Password


-->User:
User can 
  - old user can Login
  - new user can Register
  - view the lost of events
  - register for any event
  - view information of all events

-------------------------------------------------------------------

Complie : make

run :
in 1st terminal -> ./server.out <port>
in 2nd terminal -> ./client.out <host> <port>