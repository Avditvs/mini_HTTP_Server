# Mini HTTP server

This project is a small HTTP server that serves *static* files.
This sever is entirely written in pure C !

Of course, it is not as reliable as the Apache HTTP server but it works !!

## Installation

Just clone the project and run :  
`make clean && make`

## CLI

`./bin/server <config_file>`

The default configuration file is etc/serverHttp.conf  
Else, the program looks in /etc/serverHttp.conf
Else, the default hardcoded configuration is used.  

---------------

The config file supports commments, prepended by a `#`
