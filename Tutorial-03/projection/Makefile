###############################################################################
#
# Makefile
#
###############################################################################

HEADERS  = glm.h 
SOURCES  = glm.c projection.c 
OBJECTS  = $(SOURCES:.c=.o)
PROGRAMS = projection 

###############################################################################


CC      = gcc
CFLAGS  = -Wall -Wno-format $(OPTFLAGS)
LDFLAGS = -lGL -lglut -lGLU -lm


###############################################################################

all: $(PROGRAMS)

$(PROGRAMS):
	$(CC) $(CFLAGS) $^ $(LDFLAGS) -o $@

define PROGRAM_template
$(1): $(addsuffix .o,$(1)) glm.o
endef
$(foreach t,$(PROGRAMS),$(eval $(call PROGRAM_template,$(t))))

clean:
	$(RM) $(OBJECTS) $(DEPENDS)
	$(RM) $(PROGRAMS)

.PHONY: all clean

###############################################################################

%.o: %.c
	$(CC) -c $(CFLAGS) $< -o $@

%.d: %.c
	$(CC) -MM $(CFLAGS) $< > $@

###############################################################################

ifneq ($(MAKECMDGOALS),clean)
-include $(DEPENDS)
endif

###############################################################################
