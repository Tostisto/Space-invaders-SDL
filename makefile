NAME = space_invaders
CXX = gcc
OUT = obj

CFLAGS += `sdl2-config --cflags`
LDFLAGS += `sdl2-config --libs` -lSDL2_ttf -lSDL2_image 

vpath %.c %.h source
vpath %.h source

OBJS += main.o game.o use.o menu.o gameover.o

OBJ = $(patsubst %, $(OUT)/%, $(OBJS))

all: $(NAME)

$(OUT)/%.o: %.c %.h
	@mkdir -p $(OUT)
	$(CXX) $(CFLAGS) $(CFLAGS) -c -o $@ $<
	
$(NAME): $(OBJ)
	$(CXX) -o $@ $(OBJ) $(LDFLAGS)
