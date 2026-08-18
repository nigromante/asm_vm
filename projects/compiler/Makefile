
#	Colors --------------------------------------------------------------------
RED    := $(shell tput -Txterm setaf 1)
GREEN  := $(shell tput -Txterm setaf 2)
YELLOW := $(shell tput -Txterm setaf 3)
BLUE   := $(shell tput -Txterm setaf 4)
RESET  := $(shell tput -Txterm sgr0)


#	Executable Name -----------------------------------------------------------
TARGETNAME:=asmvmc
ASM_TEST_FILE:=../../test/prg1.asm

#	Source Folders ------------------------------------------------------------
SRCDIR:=../../src

#	Work Folders --------------------------------------------------------------
WRKDIR:=./debug
OBJDIR:=$(WRKDIR)/obj
DEPDIR:=$(WRKDIR)/dep
BINDIR:=$(WRKDIR)/bin

#	Install Folders -----------------------------------------------------------
INSTALL:=../../run/debug/bin

#	Work Files ----------------------------------------------------------------
SRCS:=$(shell find $(SRCDIR) -name "*.c")
	
DEPSTMP:=$(SRCS:.c=.d)
DEPS:=$(subst $(SRCDIR),$(DEPDIR),$(DEPSTMP))

OBJSTMP:=$(patsubst %.c,%.o,$(SRCS))
OBJS:=$(subst $(SRCDIR),$(OBJDIR),$(OBJSTMP))

TARGET:=$(BINDIR)/$(TARGETNAME)


#	Libs (Dependencies) Folders -----------------------------------------------
LIBSDIR:=../run/debug/libs
INCDIR:=$(LIBSDIR)/include
LIBDIR:=$(LIBSDIR)/bin


# Compiler Flags --------------------------------------------------------------
CC:=gcc
CCFLAGS:=-c -g -Wall 
INCLUDE:=-I $(SRCDIR)/include -I $(INCDIR)
DEPFLAGS = -MMD -MP -MF $(DEPDIR)/$*.d 

# Linker Flags ----------------------------------------------------------------
LD:=gcc
LDFLAGS:=-L $(LIBDIR)
LDLIBS:=



# -------------------------------------------------------------------- Actions
.PHONY: build
build: $(TARGET)


.PHONY: all
all: clean zero build

.PHONY: zero
zero:
	mkdir -p $(OBJDIR) $(DEPDIR) $(BINDIR)

.PHONY: clean
clean:
	rm -rf $(WRKDIR) main.o analisis

.PHONY: install
install:
	cp $(TARGET) $(INSTALL)

# ------------------------------------------------------------------- Executes
.PHONY: run
run:
	@$(TARGET) -f $(ASM_TEST_FILE)  -o $(ASM_TEST_FILE).o 

.PHONY: run-demo
run-demo:
	@$(TARGET) -f $(ASM_TEST_FILE) -V -a

.PHONY: run-debug
run-debug:
	@$(TARGET) -f $(ASM_TEST_FILE) -D -a

.PHONY: debug
debug:
	@gdb $(TARGET) $(ASM_TEST_FILE)

.PHONY: profile
profile:
	@bash ./scripts/profile.sh $(TARGET) $(ASM_TEST_FILE) 


# ------------------------------------------------------------------- Compile
$(TARGET): $(OBJS) main.o
	$(info  )
	$(info Linking ... )
	@echo -n "\t${YELLOW}"  
	$(LD)  $^  $(LDFLAGS) $(LDLIBS) -o $@ 
	@echo -n "${RESET}"  
	$(info )


-include $(DEPS)

$(OBJDIR)/%.o: $(SRCDIR)/%.c 
	@echo -n "\t${YELLOW}"  
	$(CC) $(CCFLAGS) $(DEPFLAGS) $(INCLUDE) $< -o $@
	@echo -n "${RESET}"  

main.o: main.c
	@echo -n "\t${YELLOW}"  
	$(CC) $(CCFLAGS) $(DEPFLAGS) $(INCLUDE) $< -o $@
	@echo -n "${RESET}"  

# ---------------------------------------------------------------------- Helps

.PHONY: help
help:
	@glow ./README.md


.PHONY: info
info:
	$(info Target       : $(YELLOW)$(TARGET)$(RESET))
	$(info )
	$(info Working Dir  : $(PWD))
	$(info )
	$(info Sources      : $(SRCS))
	$(info )
	$(info Dependencies : $(DEPS))
	$(info )
	$(info Objects      : $(OBJS))
	$(info )
	$(info Install Dir  : $(INSTALL))
	$(info )
	$(info Test File    : $(ASM_TEST_FILE)) 
	@echo
	
