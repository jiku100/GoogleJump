CC := /usr/local/arm-linux-4.1.1/bin/arm-linux-gcc

OUTPUT		= GoogleJump
SRCS		= ./src/main.c \
				./src/random.c\
				./src/queue.c\
				./src/clcd.c\
				./src/utils.c\
				./src/game.c\
				./src/dot.c\
				./src/led.c\
				./src/keypad.c\
				./src/player.c

CFLAGS		= -I./lib


$(OUTPUT) : $(SRCS)
	$(CC) $(CFLAGS) -o $@ $(SRCS)

test : $(SRCS)
	gcc $(CFLAGS) -o $@ $(SRCS)

xim : $(SRCS)
	@cd /usr/xim && $(MAKE) -s xim_OUTPUT="$(OUTPUT)" \
	xim_PATH="$(PWD)" xim_SRCS="$(SRCS)" xim_CFLAGS="$(CFLAGS)"

clean:
	@rm -f $(OUTPUT)
	@rm -f xim_$(OUTPUT)
