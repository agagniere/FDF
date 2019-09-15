NAME:=fdf

SOURCE_PATH:=src
CACHE_PATH:=cache
HEADER_PATH:=include

FILES=$(shell find $(SOURCE_PATH) -name '*.c')
OBJECTS=$(FILES:.c=.o)

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
COMPILER:=gcc
LINKER:=ld

IFLAGS=$(addprefix -L,$(LIBS_PATH))
IFLAGS+=$(addprefix -l,$(LIBS_NAME))

LFLAGS=$(IFLAGS)
# ====================

all: $(NAME)

$(NAME): $(OBJ) | $(LIBS)
	$(LINKER) $(LFLAGS) -o $@ $^

%.a:
	@make -C $(@D)

test:
	@echo -e $(IFLAG)

