INCDIR := ./inc/
SRCDIR := ./src/
OUTDIR := ./out/

vpath %.c $(SRCDIR)

CC := gcc
PATHFLAG := -I$(INCDIR)
CFLAGS := -std=c99 $(PATHFLAG) -Wall -Werror -Wpedantic

SRCS := $(wildcard $(SRCDIR)*.c)
OBGS := $(patsubst $(SRCDIR)%.c,$(OUTDIR)%.o,$(SRCS))

DEPS := $(patsubst %.o,%.d,$(OBGS))

.PHONY : clean debug release

debug : CFLAGS += -DDEBUG -g3
debug : app

release : clean app

app : $(OBGS) 
	$(CC) $(CFLAGS) $^ -o $@

$(OUTDIR)%.o : %.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

$(OUTDIR)%.d : %.c
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) $(PATHFLAG) -M $< | sed "s^$*.o^$(OUTDIR)$*.o^" > $@

include $(DEPS)

clean :
	rm -f app
	rm -fr $(OUTDIR)