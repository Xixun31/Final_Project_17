OUT := game
CC := gcc

CXXFLAGS := -Wall -std=c11 -O2
HEADERPAD := -Wl,-headerpad_max_install_names
SOURCE := $(wildcard *.c */*.c */*/*.c)
SOURCE := $(filter-out mac_main.c, $(SOURCE))
OBJ := $(patsubst %.c, %.o, $(notdir $(SOURCE)))
RM_OBJ := 
RM_OUT := 

# 使用 pkg-config 获取正确的 Allegro 路径
ALLEGRO_CFLAGS := $(shell pkg-config --cflags allegro-5 allegro_image-5 allegro_font-5 allegro_ttf-5 allegro_dialog-5 allegro_primitives-5 allegro_audio-5 allegro_acodec-5 2>/dev/null)
ALLEGRO_LIBS := $(shell pkg-config --libs allegro-5 allegro_image-5 allegro_font-5 allegro_ttf-5 allegro_dialog-5 allegro_primitives-5 allegro_audio-5 allegro_acodec-5 2>/dev/null)

# 如果 pkg-config 失败，使用备用路径
ifeq ($(ALLEGRO_CFLAGS),)
    ALLEGRO_CFLAGS := -I$(shell brew --prefix allegro)/include
    ALLEGRO_LIBS := -L$(shell brew --prefix allegro)/lib -lallegro -lallegro_main -lallegro_image -lallegro_font -lallegro_ttf -lallegro_dialog -lallegro_primitives -lallegro_audio -lallegro_acodec
endif

# 平台特定设置
UNAME_S := $(shell uname -s)

# 设置 RPATH 用于 macOS
ifeq ($(UNAME_S),Darwin)
    RPATH := -Wl,-rpath,$(shell brew --prefix allegro)/lib
else
    RPATH := 
endif

# 设置清理命令
RM_OBJ := rm -f $(OBJ)
RM_OUT := rm -f $(OUT)

debug:
	$(CC) -c -g $(CXXFLAGS) $(ALLEGRO_CFLAGS) $(SOURCE) -D DEBUG
	$(CC) $(CXXFLAGS) -o $(OUT) $(OBJ) $(ALLEGRO_LIBS) $(RPATH) $(HEADERPAD)
	$(RM_OBJ)

release:
	$(CC) -c $(CXXFLAGS) $(ALLEGRO_CFLAGS) $(SOURCE)
	$(CC) $(CXXFLAGS) -o $(OUT) $(OBJ) $(ALLEGRO_LIBS) $(RPATH) $(HEADERPAD)
	$(RM_OBJ)

clean:
	$(RM_OUT)