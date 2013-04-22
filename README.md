
# How to compile

## get codes

```
$ git clone https://github.com/syuu1228/uARM.git
```

## compile

just run make.

```
$ make
```

You will get ./uARM as an executable binary.

## uncompress image

```
$ bzcat jaunty.rel.v2.bz2 > jaunty.rel.v2
```

## boot linux up.

```
$ ./uARM jaunty.rel.v2
```

You will get shell prompt after 10 second.

## enjoy in the sandbox.

You can terminate by using ```killall uARM``` on terminal.
I don't know how to shutdown safely.
