BIN_NAME	:= mesh-editor
BIN 		:= $(BIN_DIR)/$(BIN_NAME)

OPT			+= -std=c++17 -pedantic -DGLFW_INCLUDE_GLCOREARB -DGLM_ENABLE_EXPERIMENTAL -DGLM_FORCE_SILENT_WARNINGS

SRC_DIR 	:= src
SHADERS_DIR	:= $(SRC_DIR)/Rendering/Shaders
SHADERS_DST := $(PROJECT_ROOT)/Shaders
INC_PATH	:=  -I$(GL3W_DIR)/include \
				-I$(GLFW_DIR)/include \
				-I$(IMGUI_DIR)/include \
				-I$(GLM_DIR)/include \
				-I$(SRC_DIR)

LIBS_PATH	:= -L$(GL3W_DIR)/$(BIN_DIR) \
			   -L$(GLFW_DIR)/$(BIN_DIR) \
			   -L$(IMGUI_DIR)/$(BIN_DIR) 

LIBS_nux		:= -lgl3w -lglfw -limgui -ldl -lX11 -lXrandr -lXinerama -lXcursor -lpthread -lstdc++fs
LIBS_win		:= -lgl3w -lglfw -limgui -lgdi32
LIBS			:= $(LIBS_$(PLATFORM))

ifeq ($(PLATFORM), win)
	OPT += -DBUILD_WIN
	BIN := $(BIN).exe
endif

ifeq ($(TARGET_SHELL),cmd)
	BIN := $(subst /,\,$(BIN))

	INC_PATH := $(subst /,\,$(INC_PATH))
	LIBS_PATH := $(subst /,\,$(LIBS_PATH))
	SRC_DIR_FULL := $(subst /,\,$(abspath $(SRC_DIR)))
	SHADERS_DIR := $(subst /,\,$(SHADERS_DIR))
	SHADERS_DST := $(subst /,\,$(SHADERS_DST))

	SOURCES := $(subst $(SRC_DIR_FULL), , $(shell dir /b/s $(SRC_DIR)\*.cpp))
	FOLDERS := $(subst $(SRC_DIR_FULL), , $(shell dir /b/s/a:d $(SRC_DIR)))
	FOLDERS := $(FOLDERS:%=$(BIN_DIR)\\%)
	OBJECTS := $(patsubst %.cpp,$(BIN_DIR)\\%.o,$(SOURCES))
else
	SOURCES := $(shell find $(SRC_DIR) -type f -name '*.cpp' -printf "%P\n")
	FOLDERS	:= $(shell find $(SRC_DIR) -mindepth 1 -type d -printf $(BIN_DIR)"/%P\n")
	OBJECTS := $(patsubst %.cpp,$(BIN_DIR)/%.o,$(SOURCES))
endif

DEPS := $(OBJECTS:.o=.d)

.PHONY: clean

all: directories $(BIN)
	$(COPY_FOLDER) $(SHADERS_DIR) $(SHADERS_DST)
	$(COPY_FILE) $(BIN) $(PROJECT_ROOT)

directories: $(FOLDERS)
	@echo Directories done
	
$(FOLDERS):
	@echo Creating directory: $@
	$(MKDIR) $@

$(BIN): $(OBJECTS)
	$(CXX) $(OPT) $(LIBS_PATH) -o $@ $^ $(LIBS)
	
define myrule
$(1) : $(2)
	@echo making $$@ from $$<
	$(CXX) $(INC_PATH) $(OPT) -c -o $$@ $$<
endef

ifeq ($(TARGET_SHELL),cmd)
$(foreach SRC, $(SOURCES), $(eval $(call myrule, $(patsubst %.cpp, $(BIN_DIR)\\%.o, $(SRC)), $(SRC_DIR)/$(SRC))))
else
$(foreach SRC, $(SOURCES), $(eval $(call myrule, $(patsubst %.cpp, $(BIN_DIR)/%.o, $(SRC)), $(SRC_DIR)/$(SRC))))
endif

clean:
	$(RM) $(BIN_DIR)
	
-include $(DEPS)
