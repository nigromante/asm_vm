
#	Colors --------------------------------------------------------------------
RED    := $(shell tput -Txterm setaf 1)
GREEN  := $(shell tput -Txterm setaf 2)
YELLOW := $(shell tput -Txterm setaf 3)
BLUE   := $(shell tput -Txterm setaf 4)
RESET  := $(shell tput -Txterm sgr0)


#	Executable Name -----------------------------------------------------------
TARGETNAME:=asmvm
DATA1:=./test/prg1.asm

#	Source Folders ------------------------------------------------------------
SRCDIR:=./src

#	Work Folders --------------------------------------------------------------
WRKDIR:=./debug
OBJDIR:=$(WRKDIR)/obj
DEPDIR:=$(WRKDIR)/dep
BINDIR:=$(WRKDIR)/bin

#	Install Folders -----------------------------------------------------------
INSTALL:=../run/debug/bin

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



#	Actions -------------------------------------------------------------------

.PHONY: build
build: $(TARGET)


.PHONY: all
all: clean build run


$(TARGET): $(OBJS) 
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


.PHONY: clean
clean:
	rm -rf $(WRKDIR)  analisis


.PHONY: run
run:
	@$(TARGET) $(DATA1) 


.PHONY: run-demo
run-demo:
	@$(TARGET) $(DATA1) DEMO

.PHONY: run-debug
run-debug:
	@$(TARGET) $(DATA1) DEBUG



.PHONY: debug
debug:
	gdb $(TARGET) $(DATA1)


.PHONY: profile
profile:
	@bash ./scripts/profile.sh $(TARGET) $(DATA1) 


.PHONY: help
help:
	@cat ./readme.txt


.PHONY: install
install:
	cp $(TARGET) $(INSTALL)

.PHONY: zero
zero:
	mkdir -p $(OBJDIR) $(DEPDIR) $(BINDIR)

.PHONY: info
info:
	$(info Target       : $(YELLOW)$(TARGET)$(RESET))
	$(info )
	$(info Working Dir  : $(PWD))
	$(info )
	$(info Sources      : $(SRCS))
	$(info Dependencies : $(DEPS))
	$(info Objects      : $(OBJS))
	$(info )
	$(info Install Dir  : $(INSTALL))
	$(info )
	@echo
	@echo "$(LD)  $(OBJS)  $(LDFLAGS) $(LDLIBS) -o $(TARGET) "
	@echo "$(CC) $(CCFLAGS) $(DEPFLAGS) $(INCLUDE) %.c -o %.o "
	
