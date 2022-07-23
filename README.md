# Codify
A simple SDL2 application written in C that outputs a window with custom syntax highlighted code. 
Lexical analysis is performed on the raw input text to parse a subset of tokens that adhere to the C standard.
These tokens can be customized by changing the color attributes. 

## Quick start Linux

```
$ git clone https://github.com/Janko-dev/Codify.git
$ make
$ ./codify resources/helloworld.c
```
![Example hello world program](/resources/codify_example.png "Example hello world program")

The color palette can be adjusted in `graphics.c`


