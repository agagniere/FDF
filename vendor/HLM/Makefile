# Folders
SOURCE_PATH := src
CACHE_PATH  := cache
HEADER_PATH := include

# Files
NAME          := mlxwrap
TARGET_STATIC := lib$(NAME).a
TARGET_SHARED := lib$(NAME).so
FILES         := $(shell find $(SOURCE_PATH) -name '*.c')
OBJECTS       := $(FILES:$(SOURCE_PATH)%.c=$(CACHE_PATH)%.o)

# Compiler
CC       ?= gcc
CFLAGS   += -Wall -Wextra
CPPFLAGS += -I $(HEADER_PATH)

# ========== Conan ==========
CONAN_BUILD_INFO = conanbuildinfo.mak
include $(wildcard $(CONAN_BUILD_INFO))

CFLAGS   += $(CONAN_CFLAGS)
CPPFLAGS += $(addprefix -I, $(CONAN_INCLUDE_DIRS))
CPPFLAGS += $(addprefix -D, $(CONAN_DEFINES))
LDFLAGS  += $(addprefix -L, $(CONAN_LIB_DIRS))
LDLIBS   += $(addprefix -l, $(CONAN_LIBS))
# ===========================

static: $(TARGET_STATIC)

shared: $(TARGET_SHARED)

$(TARGET_STATIC): $(OBJECTS)
	$(AR) rcs $@ $^

$(TARGET_SHARED): $(OBJECTS)
	$(CC) -shared $(CFLAGS) -o $@ $^ $(LDFLAGS) $(LDLIBS)

$(CACHE_PATH)/%.o: $(SOURCE_PATH)/%.c | $(CACHE_PATH)
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

$(CACHE_PATH):
	mkdir -p $@

clean:
	$(RM) -r $(CACHE_PATH)

fclean: clean
	$(RM) $(TARGET_STATIC) $(TARGET_SHARED)

.PHONY: static shared clean fclean
