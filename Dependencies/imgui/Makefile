BIN 		:= $(BIN_DIR)/libimgui.a

OPT		+= -DGLFW_INCLUDE_GLCOREARB

INC_PATH	+= -I./include \
		   -I$(GL3W_DIR)/include \
		   -I$(GLFW_DIR)/include
		   
SRC_DIR 	= ./src

SOURCES 	:= $(wildcard $(SRC_DIR)/*.cpp)
OBJECTS 	:= $(patsubst %.cpp,$(BIN_DIR)/%.o,$(notdir $(SOURCES)))
DEPS		:= $(OBJECTS:.o=.d)

.PHONY: clean test

all: directories $(BIN)

directories:
	@$(MKDIR) $(BIN_DIR)

$(BIN): $(OBJECTS)
	ar rcs $@ $^

$(BIN_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(INC_PATH) $(OPT) -c -o $@ $<

clean:
	$(RMDIR) $(BIN_DIR)
	
test:
	@echo -------------------------------
	@echo $(SOURCES)
	@echo -------------------------------
	@echo $(OBJECTS)
	@echo -------------------------------
	@echo $(DEPS)
	@echo -------------------------------
	@echo $(INC_PATH)
	@echo -------------------------------
	
-include $(DEPS)


	
