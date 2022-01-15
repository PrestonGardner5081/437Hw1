TARGET1=hw1gardner1
TARGET2=hw1gardner2

SOURCES1=import_registers.c \
        enable_pwm_clock.c \
		hw1gardner1.c 

SOURCES2=import_registers.c \
        enable_pwm_clock.c \
		hw1gardner2.c 
 
OBJECTS1=$(patsubst %.c,%.o,$(SOURCES1))

OBJECTS2=$(patsubst %.c,%.o,$(SOURCES2))

all: hw1gardner1 hw1gardner2

hw1gardner1: $(OBJECTS1)
	gcc $(OBJECTS1) -o $(TARGET1)

hw1gardner2: $(OBJECTS2)
	gcc $(OBJECTS2) -o $(TARGET2)

clean:
	rm -f $(OBJECTS1) $(TARGET1)
	rm -f $(OBJECTS2) $(TARGET2)

%.o:%.c
	gcc -c $< -o $@
