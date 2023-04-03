# ----------------------------------------------------------------------
#  This file is part of jnutils, made public 2023, (c) Jeff Nye.
#  See LICENSE in the root directory.
# ----------------------------------------------------------------------
.PHONY: clean run

CPP = g++
# --------------------------------------------------------------
TARGET = bin/test
# --------------------------------------------------------------
ALL_SRC = $(wildcard src/*.cpp)
ALL_OBJ = $(subst src,obj,$(ALL_SRC:.cpp=.o))
ALL_DEP = $(ALL_OBJ:.o=.d))
# --------------------------------------------------------------
MSG_INC = -I../../../jnutils/msg/inc

DEP  = -MMD -MP
DEF  = -DVERSION='"0.1.2"'
INC  = -I./inc $(MSG_INC)
OPT  = -g
STD  = -std=c++2a
WARN = -Wall
LIBS = -lboost_program_options -lpthread

CFLAGS   = $(OPT) $(DEP) $(DEF) $(INC) $(WARN)
CPPFLAGS = $(CFLAGS) $(STD)
LDFLAGS  = 
# --------------------------------------------------------------
#default: run
only: $(TARGET)
# --------------------------------------------------------------
obj/%.o: src/%.cpp
	-mkdir -p obj
	$(CPP) -c $(CPPFLAGS) $< -o $@

$(TARGET):	$(ALL_OBJ)
	-mkdir -p bin
	$(CPP) $(LDFLAGS) $^ -o $@ $(LIBS)

#OPTS = \
#  --ini file.ini \
#  --multi multi_a \
#  --multi multi_b \
#  --bool_flag \
#  --plain 42 \
#  --hidden_one 1 \
#  --hidden_two 2 \
#  --query_options \

#  positional_option
INPUT = I04 INT03 MM03 MM05 S02 S04
TRACE   = ../traces/kaggle/input/I04.csv
SIMPLE  = simple.csv
RESULTS = results.txt

convert_set: $(TARGET)
	$(MAKE) convert BASE=I04
	$(MAKE) convert BASE=INT03
	$(MAKE) convert BASE=MM03
	$(MAKE) convert BASE=MM05
	$(MAKE) convert BASE=S02
	$(MAKE) convert BASE=S04

convert:	$(TARGET)
	$(TARGET) --convert_full_trace \
    --full_trace_fn   ../traces/kaggle/input/$(BASE).csv \
    --simple_trace_fn ./simple_$(BASE).csv
	
run:	$(TARGET)
	$(TARGET) --run_prediction --simple_trace_fn $(SIMPLE) \
            --results_fn $(RESULTS)

test:	$(TARGET)
	@echo " ---------------------------------------------"
	@-$(TARGET) --help
	@echo " ---------------------------------------------"
	@-$(TARGET) --version
	@echo " ---------------------------------------------"
	@$(TARGET) $(OPTS) pos_option
	@echo " ---------------------------------------------"
	@$(TARGET) $(OPTS) --positional_option explicit_pos_option
	@echo " ---------------------------------------------"

val: $(TARGET)
	valgrind --leak-check=full \
           --show-leak-kinds=all \
           --track-origins=yes \
           --verbose \
           --log-file=valgrind-out.txt \
           $(TARGET)

# Helpful to diplay values of variables, e.g. make help-DEP
help-%:
	@echo $* = $($*)

-include $(ALL_DEP)

clean:
	-rm -f obj/* bin/*
