cmd_/home/ldd_rpi/ldd/youtube_examples/hello.mod := printf '%s\n'   hello.o | awk '!x[$$0]++ { print("/home/ldd_rpi/ldd/youtube_examples/"$$0) }' > /home/ldd_rpi/ldd/youtube_examples/hello.mod
