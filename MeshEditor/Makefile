BIN_NAME	:= mesh-editor
BIN 		:= $(BIN_DIR)/$(BIN_NAME)

OPT			+= -std=c++17 -pedantic -DGLFW_INCLUDE_GLCOREARB -DGLM_ENABLE_EXPERIMENTAL -DGLM_FORCE_SILENT_WARNINGS

SRC_DIR 	:= modules
SRC_DIR_ABS := $(CURDIR)/$(SRC_DIR)
SHADERS_DIR	:= $(SRC_DIR)/Rendering/src/Shaders
SHADERS_DST := $(PROJECT_ROOT)/Shaders
INC_PATH	:=  -I$(GL3W_DIR)/include \
				-I$(GLFW_DIR)/include \
				-I$(IMGUI_DIR)/include \
				-I$(GLM_DIR)/include \

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
	SRC_DIR_ABS := $(subst /,\,$(SRC_DIR_ABS))
	SHADERS_DIR := $(subst /,\,$(SHADERS_DIR))
	SHADERS_DST := $(subst /,\,$(SHADERS_DST))

	MODULES := $(shell dir /b $(SRC_DIR))
	INC_PATH := $(INC_PATH)$(foreach MODULE,$(MODULES),-I$(SRC_DIR_ABS)\$(MODULE)\include)

	SOURCES := $(subst $(SRC_DIR_ABS), , $(foreach MODULE,$(MODULES),$(shell dir /b/s "$(SRC_DIR)\$(MODULE)\src\*.cpp")))
	FOLDERS := $(subst $(SRC_DIR_ABS), , $(foreach MODULE,$(MODULES),$(shell dir /b/s/a:d "$(SRC_DIR)\$(MODULE)\src")))
	FOLDERS := $(FOLDERS:%=$(BIN_DIR)\\%)
	OBJECTS := $(patsubst %.cpp,$(BIN_DIR)\\%.o,$(SOURCES))
else
	MODULES := $(shell find $(SRC_DIR) -mindepth 1 -maxdepth 1 -type d -printf "%P\n")
	INC_PATH := $(INC_PATH)$(foreach MODULE,$(MODULES),-I$(SRC_DIR_ABS)/$(MODULE)/include)

	SOURCES := $(foreach MODULE,$(MODULES),$(shell find $(SRC_DIR)/$(MODULE)/src/ -name *.cpp -type f -printf "$(MODULE)/src/%P\n"))
	FOLDERS := $(foreach MODULE,$(MODULES),$(shell find $(SRC_DIR)/$(MODULE)/src/ -type d -printf "$(BIN_DIR)/$(MODULE)/src/%P\n"))
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
$(foreach SRC, $(SOURCES), $(eval $(call myrule, $(patsubst %.cpp, $(BIN_DIR)\\%.o, $(SRC)), $(SRC_DIR)\$(SRC))))
else
$(foreach SRC, $(SOURCES), $(eval $(call myrule, $(patsubst %.cpp, $(BIN_DIR)/%.o, $(SRC)), $(SRC_DIR)/$(SRC))))
endif

clean:
	$(RM) $(BIN_DIR)
	
-include $(DEPS)
