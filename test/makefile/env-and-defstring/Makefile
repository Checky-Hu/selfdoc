#usage: export ENABLE_DEFINE=1;make
ifeq ($(ENABLE_DEFINE), 1)
DEFINE= -D DEFSTRING=\"HELLO\"
endif

all:
	gcc -Wall -g def_string.c $(DEFINE) -o out/def_string

clean:
	rm out/def_string
