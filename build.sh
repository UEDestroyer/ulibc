#TODO: makefile

gcc -nostdlib -Wl,-no-dynamic-linker include/*/base.c helloWorld.c -o hello
