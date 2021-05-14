INCDIR := ./inc/
SRCDIR := ./src/
OUTDIR := ./out/

vpath %.c $(SRCDIR)

CC := gcc
PATHFLAG := -I$(INCDIR)
CFLAGS := -std=c99 $(PATHFLAG) -Wall -Werror -O0 -fno-inline -masm=intel

SRCS := $(wildcard $(SRCDIR)*.c)
OBGS := $(patsubst $(SRCDIR)%.c,$(OUTDIR)%.o,$(SRCS))

DEPS := $(patsubst %.o,%.d,$(OBGS))

.PHONY : clean makeX87 makeNOX87 cleanOut

X87 : cleanOut appM80387
NOX87 : cleanOut appMNO80387

appM80387 : CFLAGS += -m80387 -DX87
appMNO80387 : CFLAGS += -mno-80387

appM80387 : $(OBGS) 
	$(CC) $(CFLAGS) $^ -o $@ -lm

appMNO80387 : $(OBGS) 
	$(CC) $(CFLAGS) $^ -o $@ -lm

$(OUTDIR)%.o : %.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

$(OUTDIR)%.d : %.c
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) $(PATHFLAG) -M $< | sed "s^$*.o^$(OUTDIR)$*.o^" > $@

include $(DEPS)

cleanOut :
	rm -fr $(OUTDIR)

clean : cleanOut
	rm -f app*