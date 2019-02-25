BIN 		= $(BIN_DIR)/libgl3w.a

INC_PATH	= -I./include
SRC_DIR 	= ./src

SOURCES 	:= $(wildcard $(SRC_DIR)/*.c)
OBJECTS 	:= $(patsubst %.c,$(BIN_DIR)/%.o,$(notdir $(SOURCES)))
DEPS		:= $(OBJECTS:.o=.d)

.PHONY: clean test

all: directories $(BIN)

directories:
	$(MKDIR) $(BIN_DIR)

$(BIN): $(OBJECTS)
	ar rcs $@ $^

$(BIN_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(INC_PATH) $(OPT) -c -o $@ $<

clean:
	$(RM) $(BIN_DIR)

test:
	@echo $(SOURCES)
	@echo $(OBJECTS)
	@echo $(DEPS)
	
-include $(DEPS)

	
