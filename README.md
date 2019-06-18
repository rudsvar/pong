# Pong

A terminal pong clone written in C using sockets and ncurses.

## Building

After installing ncurses, do the following.

```bash
$ mkdir build
$ cd build
$ cmake ..
$ make
```

## Running the server

```bash
$ build/src/server <port>
```

## Running the client

```bash
$ build/src/client <ip> <port>
```

## Example

First, run the server.

```bash
$ build/src/server 12345
```

Then the client in two terminal windows.

```bash
$ build/src/client 127.0.0.1 12345
```

## TODO

* Place functions where they belong (more in bar, ball?)
* See if delay can be improved
* Protocol for communicating game state, and information about winners or quitters.
* Result screen
* Make server serve more people (person limit argument?)
