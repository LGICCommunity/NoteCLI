CC = gcc
CFLAGS = -Wall -Wextra -I./include
LDFLAGS =

SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin
DATA_DIR = data
LOG_FILE = $(DATA_DIR)/logs/history.txt

SRCS = $(wildcard $(SRC_DIR)/*.c)
OBJS = $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
TARGET = $(BIN_DIR)/NotesCLI

.PHONY: all clean clean-docs banner

all: banner $(TARGET)

banner:
	@echo "                                                            "   
	@echo " ███╗  ██╗ █████╗ ████████╗███████╗     █████╗ ██╗     ██╗  " 
	@echo " ████╗ ██║██╔══██╗╚══██╔══╝██╔════╝    ██╔══██╗██║     ██║  " 
	@echo " ██╔██╗██║██║  ██║   ██║   █████╗      ██║  ╚═╝██║     ██║  " 
	@echo " ██║╚████║██║  ██║   ██║   ██╔══╝      ██║  ██╗██║     ██║  " 
	@echo " ██║ ╚███║╚█████╔╝   ██║   ███████╗    ╚█████╔╝███████╗██║  " 
	@echo " ╚═╝  ╚══╝ ╚════╝    ╚═╝   ╚══════╝     ╚════╝ ╚══════╝╚═╝  " 
	@echo "                                                            "
	
$(TARGET): $(OBJS)
	@mkdir -p $(BIN_DIR)
	$(CC) $(OBJS) -o $(TARGET) $(LDFLAGS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)

clean-docs:
	@echo "WARNING: This will delete all documents (notes, recipes, and versions)."
	@echo -n "Are you sure you want to proceed? (y/N): "; \
	read answer; \
	if [ "$$answer" = "y" ] || [ "$$answer" = "Y" ]; then \
		echo "Cleaning all documents while preserving history..."; \
		echo "[`date '+%Y-%m-%d %H:%M:%S'`] CLEAN-DOCS: All documents cleared (notes, recipes, versions)" >> $(LOG_FILE); \
		rm -rf $(DATA_DIR)/notes/*; \
		rm -rf $(DATA_DIR)/recipes/*; \
		rm -rf $(DATA_DIR)/versions/*; \
		echo "Documents cleaned. History preserved in data/logs/history.txt"; \
		echo "Operation logged in history.txt"; \
	else \
		echo "Operation cancelled."; \
	fi 