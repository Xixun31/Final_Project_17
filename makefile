OUT := game
CC := gcc

CXXFLAGS := -Wall -std=c11 -O2
SOURCE := $(wildcard *.c */*.c */*/*.c)
SOURCE := $(filter-out mac_main.c, $(SOURCE))
OBJ := $(patsubst %.c, %.o, $(notdir $(SOURCE)))
RM_OBJ := 
RM_OUT := 

ALLEGRO_CFLAGS := -I/usr/local/include
ALLEGRO_LIBS := -L/usr/local/lib -lallegro -lallegro_main -lallegro_image -lallegro_font -lallegro_ttf -lallegro_dialog -lallegro_primitives -lallegro_audio -lallegro_acodec

ifeq ($(OS), Windows_NT) # Windows OS
	ALLEGRO_PATH := -L/usr/local/lib -lallegro
	export Path := ../MinGW/bin;$(Path)

	ALLEGRO_FLAGS_RELEASE := -I$(ALLEGRO_PATH)/include -L$(ALLEGRO_PATH)/lib/liballegro_monolith.dll.a
	ALLEGRO_DLL_PATH_RELEASE := $(ALLEGRO_PATH)/lib/liballegro_monolith.dll.a
	ALLEGRO_FLAGS_DEBUG := -I$(ALLEGRO_PATH)/include -L$(ALLEGRO_PATH)/lib/liballegro_monolith-debug.dll.a
	ALLEGRO_DLL_PATH_DEBUG := $(ALLEGRO_PATH)/lib/liballegro_monolith-debug.dll.a

	RM_OBJ := $(foreach name, $(OBJ), del $(name) & )
	RM_OUT += $(foreach name, $(*.gch */*.gch), del $(name) & )
	ifeq ($(suffix $(OUT)),)
		RM_OUT += del $(OUT).exe
	else
		RM_OUT += del $(OUT)
	endif

else # Mac OS / Linux
	UNAME_S := $(shell uname -s)

	ALLEGRO_FLAGS_RELEASE := $(ALLEGRO_CFLAGS)
	ALLEGRO_DLL_PATH_RELEASE := 
	ALLEGRO_FLAGS_DEBUG := $(ALLEGRO_FLAGS_RELEASE)
	ALLEGRO_DLL_PATH_DEBUG := 

	RM_OBJ := rm -f $(OBJ)
	RM_OUT := rm -f $(OUT)
endif

debug:
	$(CC) -c -g $(CXXFLAGS) $(ALLEGRO_FLAGS_DEBUG) $(SOURCE) -D DEBUG
	$(CC) $(CXXFLAGS) -o $(OUT) $(OBJ) $(ALLEGRO_FLAGS_DEBUG) $(ALLEGRO_LIBS) $(ALLEGRO_DLL_PATH_DEBUG)
	$(RM_OBJ)

release:
	$(CC) -c $(CXXFLAGS) $(ALLEGRO_FLAGS_RELEASE) $(SOURCE)
	$(CC) $(CXXFLAGS) -o $(OUT) $(OBJ) $(ALLEGRO_FLAGS_RELEASE) $(ALLEGRO_LIBS) $(ALLEGRO_DLL_PATH_RELEASE)
	$(RM_OBJ)

clean:
	$(RM_OUT)