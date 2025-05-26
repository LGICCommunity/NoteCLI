# Document Management System (DMS)

A command-line based Document Management System written in C that allows users to create, read, update, and delete text documents organized in categories. The system includes automatic versioning and comprehensive operation logging.

## Features

- Create new text documents in different categories
- Read existing documents
- Update document content with automatic version backup
- Delete documents
- Organized file structure with categories
- Version history for edited documents
- Complete operation logging with timestamps
- Error handling and input validation
- Color-coded console output
- Clean all documents with history preservation

## Directory Structure

```
DocumentManager/
├── bin/               # Compiled binary
├── src/               # Source code files
├── include/           # Header files
├── data/              # Document storage
│   ├── recipes/       # Recipe documents
│   ├── notes/         # Note documents
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

This will create the `dms` executable in the `bin` directory.

To clean the build files:

```bash
make clean
```

To clean all documents while preserving history:

```bash
make clean-docs
```

This will:
1. Ask for confirmation before proceeding
2. Remove all documents in notes, recipes, and versions directories
3. Preserve the operation history in data/logs/history.txt
4. Log the cleanup operation with timestamp

## Usage Guide

### Basic Commands

The DMS supports the following commands:

```bash
# Create a new document
./bin/dms create <category> <filename>

# Read a document
./bin/dms read <category> <filename>

# Update a document
./bin/dms update <category> <filename>

# Delete a document
./bin/dms delete <category> <filename>
```

### Available Categories
The system organizes documents into these categories:
- `recipes` - For storing cooking recipes
- `notes` - For general notes and todos
- `logs` - For logs and records

### How to Use

#### 1. Creating Documents
There are two ways to create documents:

a. Interactive Mode:
```bash
./bin/dms create notes todo.txt
# Then type your content and press Ctrl+D when finished
```

b. Using Echo (for quick creation):
```bash
echo "My content here" | ./bin/dms create notes quick-note.txt
```

#### 2. Reading Documents
To read any document:
```bash
./bin/dms read notes todo.txt
```

#### 3. Updating Documents
When you update a document, the old version is automatically saved in the versions directory:

a. Interactive Mode:
```bash
./bin/dms update notes todo.txt
# Enter new content and press Ctrl+D when finished
```

b. Using Echo:
```bash
echo "Updated content" | ./bin/dms update notes todo.txt
```

The old version will be saved as: `data/versions/notes_YYYYMMDD_HHMMSS_todo.txt`

#### 4. Deleting Documents
To delete a document (will ask for confirmation):
```bash
./bin/dms delete notes todo.txt
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
[2025-05-24 21:00:00] CLEAN-DOCS: All documents cleared (notes, recipes, versions)
```

To view the operation history:
```bash
cat data/logs/history.txt
```

### Version Control

- All document updates are automatically versioned
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
3. Cook for 10 minutes" | ./bin/dms create recipes pasta.txt

# Read the recipe
./bin/dms read recipes pasta.txt

# Update the recipe (old version will be saved automatically)
echo "Improved Pasta Recipe:
1. Boil water with salt
2. Add pasta
3. Cook for 8-10 minutes
4. Add olive oil" | ./bin/dms update recipes pasta.txt
```

2. Managing a todo list:
```bash
# Create todo list
echo "1. Buy groceries
2. Call mom
3. Study C programming" | ./bin/dms create notes todo.txt

# Update with completed items
echo "1. Buy groceries - DONE
2. Call mom
3. Study C programming
4. Go to gym" | ./bin/dms update notes todo.txt
```

### Input Guidelines

- Filenames can only contain:
  - Letters (a-z, A-Z)
  - Numbers (0-9)
  - Dots (.)
  - Hyphens (-)
  - Underscores (_)
- Directory traversal is not allowed in filenames
- Maximum input size for document content is 4KB

### Error Handling

The system provides clear error messages for:
- Invalid commands
- Invalid categories
- Invalid filenames
- File operation failures
- Memory allocation failures
- Version backup failures
- Logging failures

### Tips

1. Use meaningful filenames that describe the content
2. Check the versions directory for document history
3. Review the operation history in `data/logs/history.txt` to track all actions
4. Use the appropriate category for better organization
5. Make sure to press Ctrl+D after entering content in interactive mode
6. For multiline content, using echo with newlines (\n) is recommended
7. Check both version backups and operation logs for complete document history 