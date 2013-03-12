SRC_DIR         = ./src
INCL_DIR	= ./include
COMP            = gcc
FLAGS           = -g -Wall
LIBS            = 
OBJ_LIST        = $(SRC_DIR)/main.o $(SRC_DIR)/expand.o $(SRC_DIR)/parse.o $(SRC_DIR)/file_output.o $(SRC_DIR)/logic_minimization.o
TARGET_NAME     = logic_min

all: $(TARGET_NAME)

$(TARGET_NAME): $(OBJ_LIST)
	$(COMP) $(FLAGS) -o $(TARGET_NAME) $(OBJ_LIST) $(LIBS)

%.o: %.c %.h
	$(COMP) $(FLAGS) -c $<

%.o: %.cc
	$(COMP) $(FLAGS) -c $<

clean:
	rm -f $(SRC_DIR)/*.o $(SRC_DIR)/*~ $(SRC_DIR)/*# $(TARGET_NAME)
