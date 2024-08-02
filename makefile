# Diretórios
SRC_DIR = src
INC_DIR = include

# Parâmetros de compilação
CFLAGS = -g -I$(INC_DIR) -I/usr/include/x86_64-linux-gnu -lallegro_main -lallegro_font -lallegro_ttf -lallegro_primitives -lallegro_image -lallegro -lm

# Arquivo de saída
TARGET = shadowCombat

# Arquivos de origem e objetos
SRCS = $(wildcard $(SRC_DIR)/*.c)
OBJS = $(SRCS:.c=.o)

# Regras
all: $(TARGET)

$(TARGET): $(OBJS)
	gcc -o $@ $^ $(CFLAGS)

$(SRC_DIR)/%.o: $(SRC_DIR)/%.c $(INC_DIR)/%.h
	gcc -c $< -o $@ $(CFLAGS)

clean:
	rm -f $(SRC_DIR)/*.o

purge: clean
	rm -f $(TARGET)

