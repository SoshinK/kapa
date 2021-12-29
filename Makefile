#! Makefile
CC=g++
LD=ld
CCFLAGS=-g -Wall -Werror -O3 -std=c++17
TESTNAMES=entityTest
LDFLAGS=-lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

KAPA_DIR=./kapa
INCLUDES_DIR=$(KAPA_DIR)/headers
SRCS_DIR=$(KAPA_DIR)/src
BUILD_DIR=build
SRCS_TESTS_DIR=$(KAPA_DIR)/tests

TEST_ENTITY_TARGET=$(BUILD_DIR)/entityTest
OBJ_TEST_ENTITY=$(BUILD_DIR)/test_entity.o

TEST_GRAPHICS_TARGET=$(BUILD_DIR)/graphicsTest
OBJ_TEST_GRAPHICS=$(BUILD_DIR)/test_graphics.o

_OBJS=entities.o graphics.o
OBJS = $(patsubst %,$(BUILD_DIR)/%,$(_OBJS))



test: $(TEST_ENTITY_TARGET) $(TEST_GRAPHICS_TARGET)

# link entity test
$(TEST_ENTITY_TARGET): $(OBJS) $(OBJ_TEST_ENTITY)
	$(CC) $^ -o $(TEST_ENTITY_TARGET) $(LDFLAGS)

#link graphics test
$(TEST_GRAPHICS_TARGET): $(OBJS) $(OBJ_TEST_GRAPHICS)
	$(CC) $^ -o $(TEST_GRAPHICS_TARGET) $(LDFLAGS)

# build all object files from src
$(BUILD_DIR)/%.o: $(SRCS_DIR)/%.cpp
	$(CC) $(CCFLAGS) -c $< -I $(INCLUDES_DIR) -o $@

# build test object files from tests
$(BUILD_DIR)/%.o: $(SRCS_TESTS_DIR)/%.cpp
	$(CC) $(CCFLAGS) -c $< -I $(INCLUDES_DIR) -o $@

clean:
	rm $(BUILD_DIR)/*.o
