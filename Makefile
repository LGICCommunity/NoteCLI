CC = gcc
CFLAGS = -Wall -Wextra -I$(INC_DIR)
SRC_DIR = src
INC_DIR = include
OBJ_DIR = obj
BIN_DIR = bin
DATA_DIR = data
LOG_FILE = $(DATA_DIR)/logs/history.txt

# Platform-specific settings
ifeq ($(OS),Windows_NT)
    TARGET = $(BIN_DIR)/NotesCLI.exe
    RM = del /Q /F
    MKDIR = mkdir
    RMDIR = rmdir /Q /S
    PATHSEP = \\
else
    TARGET = $(BIN_DIR)/NotesCLI
    RM = rm -f
    MKDIR = mkdir -p
    RMDIR = rm -rf
    PATHSEP = /
endif

SRCS = $(wildcard $(SRC_DIR)/*.c)
OBJS = $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

.PHONY: all clean clean-docs banner

all: banner $(BIN_DIR) $(OBJ_DIR) $(TARGET)

banner:
	@echo "                                                            "   
	@echo " ███╗  ██╗ █████╗ ████████╗███████╗     █████╗ ██╗     ██╗  " 
	@echo " ████╗ ██║██╔══██╗╚══██╔══╝██╔════╝    ██╔══██╗██║     ██║  " 
	@echo " ██╔██╗██║██║  ██║   ██║   █████╗      ██║  ╚═╝██║     ██║  " 
	@echo " ██║╚████║██║  ██║   ██║   ██╔══╝      ██║  ██╗██║     ██║  " 
	@echo " ██║ ╚███║╚█████╔╝   ██║   ███████╗    ╚█████╔╝███████╗██║  " 
	@echo " ╚═╝  ╚══╝ ╚════╝    ╚═╝   ╚══════╝     ╚════╝ ╚══════╝╚═╝  " 
	@echo "                                                            "
	
                                                     
$(BIN_DIR):
	$(MKDIR) $(BIN_DIR)

$(OBJ_DIR):
	$(MKDIR) $(OBJ_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $(TARGET)

clean:
	$(RMDIR) $(OBJ_DIR)
	$(RMDIR) $(BIN_DIR)

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