cmd_/home/ldd_rpi/ldd/example/example.mod := printf '%s\n'   example.o | awk '!x[$$0]++ { print("/home/ldd_rpi/ldd/example/"$$0) }' > /home/ldd_rpi/ldd/example/example.mod
