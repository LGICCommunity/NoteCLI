# Notepad Command Line Base (NoteCLI)

A command-line based notepad app written in C that allows users to create, read, update, and delete textfile organized in categories. The system includes automatic versioning and comprehensive operation logging.

## Features

- Create new text textfile in different categories
- Read existing textfile
- Update textfile content with automatic version backup
- Delete textfile
- Organized file structure with categories
- Version history for edited textfile
- Complete operation logging with timestamps
- Error handling and input validation
- Color-coded console output
- Clean all textfile with history preservation

## Directory Structure

```
NoteCLI/
├── bin/               # Compiled binary
├── src/               # Source code files
├── include/           # Header files
├── data/              # textfile storage
│   ├── recipes/       # Recipe textfile 
│   ├── notes/         # Note textfile 
│   ├── logs/          # Operation logs and history
│   │   └── history.txt    # Complete operation history
│   └── versions/      # Automatically saved old versions
└── obj/               # Object files
```

## Building

To build the project, run:

```bash
make
```

This will create the `NotesCLI` executable in the `bin` directory.

To clean the build files:

```bash
make clean
```

To clean all textfile while preserving history:

```bash
make clean-docs
```

This will:
1. Ask for confirmation before proceeding
2. Remove all textfile in notes, recipes, and versions directories
3. Preserve the operation history in data/logs/history.txt
4. Log the cleanup operation with timestamp

## Usage Guide

### Basic Commands

The NotesCLI supports the following commands:

```bash
# Create a new textfile
./bin/NotesCLI create <category> <filename>

# Read a textfile
./bin/NotesCLI read <category> <filename>

# Update a textfile
./bin/NotesCLI update <category> <filename>

# Delete a textfile
./bin/NotesCLI delete <category> <filename>
```

### Available Categories
The system organizes textfile into these categories:
- `recipes` - For storing cooking recipes
- `notes` - For general notes and todos
- `logs` - For logs and records

### How to Use

#### 1. Creating textfile
There are two ways to create textfile:

a. Interactive Mode:
```bash
./bin/NotesCLI create notes todo.txt
# Then type your content and press Ctrl+D when finished
```

b. Using Echo (for quick creation):
```bash
echo "My content here" | ./bin/NotesCLI create notes quick-note.txt
```

#### 2. Reading textfile
To read any textfile:
```bash
./bin/NotesCLI read notes todo.txt
```

#### 3. Updating textfile
When you update a textfile, the old version is automatically saved in the versions directory:

a. Interactive Mode:
```bash
./bin/NotesCLI update notes todo.txt
# Enter new content and press Ctrl+D when finished
```

b. Using Echo:
```bash
echo "Updated content" | ./bin/NotesCLI update notes todo.txt
```

The old version will be saved as: `data/versions/notes_YYYYMMDD_HHMMSS_todo.txt`

#### 4. Deleting textfile
To delete a textfile (will ask for confirmation):
```bash
./bin/NotesCLI delete notes todo.txt
```

### Operation History and Logging

The system maintains a complete history of all operations in `data/logs/history.txt`. Each operation is logged with:

1. Timestamp: `[YYYY-MM-DD HH:MM:SS]`
2. Operation Type: `CREATE`, `READ`, `UPDATE`, `DELETE`, or `CLEAN-DOCS`
3. File Path or Operation Details

Example log entries:
```
[2025-05-24 20:55:56] CREATE: notes/todo.txt
[2025-05-24 20:56:07] READ: notes/todo.txt
[2025-05-24 20:56:15] UPDATE: notes/todo.txt
[2025-05-24 20:56:19] DELETE: notes/todo.txt
[2025-05-24 21:00:00] CLEAN-DOCS: All textfiles cleared (notes, recipes, versions)
```

To view the operation history:
```bash
cat data/logs/history.txt
```

### Version Control

- All textfile updates are automatically versioned
- Old versions are stored in `data/versions/`
- Version files are named using the format: `category_YYYYMMDD_HHMMSS_filename`
- You can access old versions directly in the versions directory

### Practical Examples

1. Creating and managing a recipe:
```bash
# Create a new recipe
echo "Pasta Recipe:
1. Boil water
2. Add pasta
3. Cook for 10 minutes" | ./bin/NotesCLI create recipes pasta.txt

# Read the recipe
./bin/NotesCLI read recipes pasta.txt

# Update the recipe (old version will be saved automatically)
echo "Improved Pasta Recipe:
1. Boil water with salt
2. Add pasta
3. Cook for 8-10 minutes
4. Add olive oil" | ./bin/NotesCLI update recipes pasta.txt
```

2. Managing a todo list:
```bash
# Create todo list
echo "1. Buy groceries
2. Call mom
3. Study C programming" | ./bin/NotesCLI create notes todo.txt

# Update with completed items
echo "1. Buy groceries - DONE
2. Call mom
3. Study C programming
4. Go to gym" | ./bin/NotesCLI update notes todo.txt
```

### Input Guidelines

- Filenames can only contain:
  - Letters (a-z, A-Z)
  - Numbers (0-9)
  - Dots (.)
  - Hyphens (-)
  - Underscores (_)
- Directory traversal is not allowed in filenames
- Maximum input size for textfile content is 4KB

### Error Handling

The system provides clear error messages for:
- Invalid commands
- Invalid categories
- Invalid filenames
- File operation failures
- Memory allocation failures
- Version backup failures
- Logging failures

## Installation

### Prerequisites

#### Windows
- MinGW-w64 or MSYS2 with gcc
- Make utility
- Git (optional, for cloning)

#### Linux/macOS
- GCC
- Make
- Git (optional, for cloning)

### Building from Source

1. Clone the repository:
```bash
git clone https://github.com/LGICCommunity/NoteCLI.git
cd NoteCLI
```

2. Build the project:

For Windows (Using MinGW):
```bash
mingw32-make
```

For Windows (Using MSYS2):
```bash
make
```

For Linux/macOS:
```bash
make
```

The executable will be created in the `bin` directory:
- Windows: `bin/NoteCLI.exe`
- Linux/macOS: `bin/NoteCLI`

### Usage

#### Windows
```bash
# Create a new note
bin\NoteCLI.exe create notes todo.txt

# Read a note
bin\NoteCLI.exe read notes todo.txt

# Update a note
bin\NoteCLI.exe update notes todo.txt

# Delete a note
bin\NoteCLI.exe delete notes todo.txt
```

#### Linux/macOS
```bash
# Create a new note
./bin/NoteCLI create notes todo.txt

# Read a note
./bin/NoteCLI read notes todo.txt

# Update a note
./bin/NoteCLI update notes todo.txt

# Delete a note
./bin/NoteCLI delete notes todo.txt
```

## Platform-Specific Notes

### Windows
- File paths use backslashes (`\`) as separators
- Notes are stored in `data\` directory
- Logs are stored in `data\logs\history.txt`

### Linux/macOS
- File paths use forward slashes (`/`) as separators
- Notes are stored in `data/` directory
- Logs are stored in `data/logs/history.txt`

<!--

### Tips

1. Use meaningful filenames that describe the content
2. Check the versions directory for textfile history
3. Review the operation history in `data/logs/history.txt` to track all actions
4. Use the appropriate category for better organization
5. Make sure to press Ctrl+D after entering content in interactive mode
6. For multiline content, using echo with newlines (\n) is recommended
7. Check both version backups and operation logs for complete textfile history 

-->
