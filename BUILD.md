
= How to compile on OSX (10.6.8).

I'm sorry I don't know how to compile on OSX 10.7 or avobe. As I don't use them.

== get codes

```
$ git clone https://github.com/monaka/uARM.git
```

== compile

just run make.

```
$ make
```

You will get ./uARM as an executable binary.

NOTE: I tested on gcc-4.2 apple genuine.

== uncompress image

```
$ unzip2 jaunty.rel.v2.bz2
```

== boot linux up.

```
$ ./uARM jaunty.rel.v2
```

You will get shell prompt after 10 second.

== enjoy in the sandbox.

You can terminate by using ```killall uARM``` on OSX terminal.
I don't know how to shutdown safely.
