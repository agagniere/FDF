NAME:=fdf.exe

# Folders
SOURCE_PATH := src
CACHE_PATH  := cache
HEADER_PATH := include
DOC_PATH    := doc

# Files
FILES   = $(shell find $(SOURCE_PATH) -name '*.c')
OBJECTS = $(subst $(SOURCE_PATH),$(CACHE_PATH),$(FILES:.c=.o))
DEPFILES= $(OBJECTS:.o=.d)

# ===== Compiler =====
CC       ?= gcc
CFLAGS   += -Wall -Wextra
CPPFLAGS += $(addprefix -I,$(HEADER_PATH))
LDLIBS   += "-lm"
# ====================

# ======= Conan =======
CONAN_BUILD_INFO = conanbuildinfo.mak
include $(CONAN_BUILD_INFO)
CFLAGS   += $(CONAN_CFLAGS)
CPPFLAGS += $(addprefix -I, $(CONAN_INCLUDE_DIRS))
CPPFLAGS += $(addprefix -D, $(CONAN_DEFINES))
LDFLAGS  += $(addprefix -L, $(CONAN_LIB_DIRS))
LDLIBS   += $(addprefix -l, $(CONAN_LIBS))
LDLIBS   += $(addprefix -l, $(CONAN_SYSTEM_LIBS))
LDLIBS   += $(addprefix -framework , $(CONAN_FRAMEWORKS))
# =====================


build: $(NAME)

include $(wildcard $(DEPFILES))

$(CONAN_BUILD_INFO):
	conan install .

$(NAME): $(OBJECTS)
	$(CC) $(CFLAGS) $^ $(LDFLAGS) $(LDLIBS) -o $@

$(CACHE_PATH)/%.o: $(SOURCE_PATH)/%.c | $(CACHE_PATH)
	$(CC) $(CPPFLAGS) $(CFLAGS) -MMD -c -o $@ $<

$(CACHE_PATH) $(DOC_PATH):
	mkdir $@

clean:
	$(RM) -r $(CACHE_PATH)

fclean: clean
	$(RM) $(NAME)

fbuild: fclean
	@$(MAKE) build --no-print-directory

man: $(DOC_PATH)/$(NAME:%.exe=%.1)

pdf: $(DOC_PATH)/$(NAME:%.exe=%.pdf)

$(DOC_PATH)/fdf.1: $(NAME) | $(DOC_PATH)
	-help2man --no-info --output $@ ./$<

%.pdf: %.1
	man -t $< | ps2pdf - $@

.PHONY: build clean fclean fbuild man pdf
