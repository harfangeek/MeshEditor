CC 			= gcc
CXX			= g++

ARCH 		 = x64
OPT_ARCH_x86 	 = -m32
OPT_ARCH_x64 	 = -m64

MODE 			 = release
OPT_MODE_debug 	 = -g
OPT_MODE_release = -O2
OPT 		 := -Wall -MMD -MP $(OPT_ARCH_$(ARCH)) $(OPT_MODE_$(MODE))

SOLUTION_DIR	:= $(CURDIR)
BIN_DIR 		:= bin/$(ARCH)/$(MODE)
LIBS_DIR		:= $(SOLUTION_DIR)/Dependencies
GL3W_DIR		:= $(LIBS_DIR)/gl3w
GLFW_DIR		:= $(LIBS_DIR)/glfw
IMGUI_DIR		:= $(LIBS_DIR)/imgui
GLM_DIR			:= $(LIBS_DIR)/glm
MESH_DIR		:= MeshEditor

ifeq ($(OS),Windows_NT)
	PLATFORM := win
	ifneq (,$(findstring /usr/bin/sh.exe, $(SHELL)))
		TARGET_SHELL := bash
	else
		TARGET_SHELL := cmd
	endif
else
    PLATFORM := nux
	TARGET_SHELL := bash
endif

ifeq ($(TARGET_SHELL),cmd)
	SOLUTION_DIR	:= $(subst /,\,$(SOLUTION_DIR))
	BIN_DIR			:= $(subst /,\,$(BIN_DIR))
	LIBS_DIR		:= $(subst /,\,$(LIBS_DIR))
	GL3W_DIR		:= $(subst /,\,$(GL3W_DIR))
	GLFW_DIR		:= $(subst /,\,$(GLFW_DIR))
	IMGUI_DIR		:= $(subst /,\,$(IMGUI_DIR))
	GLM_DIR			:= $(subst /,\,$(GLM_DIR))

	MKDIR		:= -md
	RM			:= -del
	RMDIR		:= -rd /s /q
	COPY_FILE	:= -xcopy /y /c /i
	COPY_FOLDER	:= -xcopy /y /c /i
else
	MKDIR		:= mkdir -p
	RM			:= -rm
	RMDIR		:= -rm -R
	COPY_FILE	:= cp -f
	COPY_FOLDER	:= cp -RTf
endif

export

.PHONY: all gl3w glfw imgui nfd libs mesh mesh_clean clean test
all: libs mesh

libs: gl3w glfw imgui
	
gl3w:
	$(MAKE) -C $(GL3W_DIR)

glfw:
	$(MAKE) -C $(GLFW_DIR)

imgui:
	$(MAKE) -C $(IMGUI_DIR)
	
mesh : gl3w glfw imgui nfd
	$(MAKE) -C $(MESH_DIR)
	
clean-mesh:
	$(MAKE) clean -C $(MESH_DIR)

clean:
	$(MAKE) clean -C $(GL3W_DIR)
	$(MAKE) clean -C $(GLFW_DIR)
	$(MAKE) clean -C $(IMGUI_DIR)
	$(MAKE) clean -C $(MESH_DIR)
