NAME:=fdf.exe

SOURCE_PATH:=src
CACHE_PATH:=cache
HEADER_PATH:=include

FILES=$(shell find $(SOURCE_PATH) -name '*.c')
OBJECTS=$(subst $(SOURCE_PATH),$(CACHE_PATH),$(FILES:.c=.o))

# ===== Libraries =====
LFT_PATH:=Libft
LFT_NAME:=ft
LFT=$(LFT_PATH)/lib$(LFT_NAME).a

MLX_PATH:=MinilibX
MLX_NAME:=mlx
MLX=$(MLX_PATH)/lib$(MLX_NAME).a

LIBS_NAME=$(LFT_NAME) $(MLX_NAME)
LIBS_PATH=$(LFT_PATH) $(MLX_PATH)
LIBS=$(LFT) $(MLX)
# =====================

# ===== Compiler =====
CC ?= gcc

CFLAGS=-Wall -Wextra
CFLAGS+=-g
#CFLAGS+=-O2
CFLAGS+=$(addprefix -I,$(HEADER_PATH) $(LFT_PATH)/include $(MLX_PATH))

LFLAGS=$(addprefix -L,$(LIBS_PATH))
LFLAGS+=$(addprefix -l,$(LIBS_NAME))
LFLAGS+=-lXext -lX11
# ====================

all: $(NAME)

$(NAME): $(OBJECTS) | $(LIBS)
	$(CC) $^ $(LFLAGS) -o $@

$(CACHE_PATH)/%.o: $(SOURCE_PATH)/%.c | $(CACHE_PATH)
	$(CC) -c $< $(CFLAGS) -o $@

%.a:
	@make -C $(@D)

$(CACHE_PATH):
	mkdir $@

test:
	@echo -e $(IFLAG)
	@echo objects $(OBJECTS)

clean:
	rm -rf $(CACHE_PATH)

fclean: clean
	rm -f $(NAME)

re: fclean
	@$(MAKE) all --no-print-directory

.PHONY: all clean fclean re
