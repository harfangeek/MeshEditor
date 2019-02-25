OPT_nux		= -D_GLFW_X11
OPT_win		= -D_GLFW_WIN32
OPT			+= $(OPT_$(PLATFORM))

BIN 		:= $(BIN_DIR)/libglfw.a

INC_PATH	= -I./include
SRC_DIR 	= ./src

SOURCES_nux	= x11_init.c x11_monitor.c x11_window.c xkb_unicode.c linux_joystick.c \
			posix_time.c posix_tls.c glx_context.c egl_context.c

SOURCES_win = win32_init.c win32_joystick.c win32_monitor.c win32_time.c \
			 win32_tls.c win32_window.c wgl_context.c egl_context.c

SOURCES		= context.c init.c input.c monitor.c vulkan.c window.c
SOURCES 	+= $(SOURCES_$(PLATFORM))
OBJECTS 	:= $(patsubst %.c,$(BIN_DIR)/%.o,$(notdir $(SOURCES)))
DEPS		:= $(OBJECTS:.o=.d)

.PHONY: clean test

all: directories $(BIN)

directories:
	@$(MKDIR) $(BIN_DIR)

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





	
