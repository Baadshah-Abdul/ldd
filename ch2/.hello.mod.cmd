cmd_/home/ldd_rpi/ldd/hello/hello.mod := printf '%s\n'   hello.o | awk '!x[$$0]++ { print("/home/ldd_rpi/ldd/hello/"$$0) }' > /home/ldd_rpi/ldd/hello/hello.mod
