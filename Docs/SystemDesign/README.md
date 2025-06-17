# NoteCLI System Design Documentation

This document provides a comprehensive system design overview of the NoteCLI application, including its architecture, components, data flow, and file organization.

## Table of Contents
1. [System Architecture](#system-architecture)
2. [Component Diagram](#component-diagram)
3. [Data Flow](#data-flow)
4. [File System Organization](#file-system-organization)
5. [Command Processing Flow](#command-processing-flow)
6. [Version Control System](#version-control-system)

## System Architecture

The following diagram shows the high-level architecture of NoteCLI:

```mermaid
graph TB
    User[User/Terminal] --> CLI[CLI Interface]
    CLI --> CommandParser[Command Parser]
    CommandParser --> FileOps[File Operations]
    FileOps --> Storage[Storage Layer]
    
    Storage --> Notes[/Notes Directory/]
    Storage --> Recipes[/Recipes Directory/]
    Storage --> Versions[/Versions Directory/]
    Storage --> Logs[/Logs Directory/]
    
    FileOps --> Logger[Logger]
    Logger --> LogFile[/History Log File/]
    
    subgraph Core Components
        CLI
        CommandParser
        FileOps
        Logger
    end
    
    subgraph Storage System
        Storage
        Notes
        Recipes
        Versions
        Logs
        LogFile
    end
```

## Component Diagram

Detailed breakdown of system components and their relationships:

```mermaid
classDiagram
    class CLI {
        +parse_arguments()
        +print_usage()
        +confirm_action()
    }
    
    class FileOps {
        +create_document()
        +read_document()
        +update_document()
        +delete_document()
        -backup_document()
        -validate_path()
    }
    
    class Utils {
        +log_error()
        +log_info()
        +get_timestamp()
        +validate_filename()
    }
    
    class Storage {
        +write_file()
        +read_file()
        +delete_file()
        +create_backup()
    }
    
    class Logger {
        +log_operation()
        +get_history()
        -format_log_entry()
    }
    
    CLI --> FileOps
    FileOps --> Storage
    FileOps --> Utils
    FileOps --> Logger
    Storage --> Logger
```

## Data Flow

The following diagram illustrates the data flow for different operations:

```mermaid
sequenceDiagram
    participant User
    participant CLI
    participant FileOps
    participant Storage
    participant Logger
    
    Note over User,Logger: Create Document Flow
    User->>CLI: create command
    CLI->>FileOps: create_document()
    FileOps->>Storage: write_file()
    Storage->>Logger: log_operation()
    Logger-->>User: success/failure
    
    Note over User,Logger: Update Document Flow
    User->>CLI: update command
    CLI->>FileOps: update_document()
    FileOps->>Storage: create_backup()
    Storage->>Storage: write_file()
    Storage->>Logger: log_operation()
    Logger-->>User: success/failure
```

## File System Organization

Directory structure and file organization:

```mermaid
graph TD
    Root[NoteCLI Root] --> Src[src/]
    Root --> Include[include/]
    Root --> Data[data/]
    Root --> Bin[bin/]
    
    Src --> MainC[main.c]
    Src --> FileOpsC[file_ops.c]
    Src --> UtilsC[utils.c]
    Src --> CliC[cli.c]
    
    Include --> FileOpsH[file_ops.h]
    Include --> UtilsH[utils.h]
    Include --> CliH[cli.h]
    
    Data --> Notes[notes/]
    Data --> Recipes[recipes/]
    Data --> Versions[versions/]
    Data --> Logs[logs/]
    
    Logs --> History[history.txt]
```

## Command Processing Flow

The flow of command processing in the system:

```mermaid
stateDiagram-v2
    [*] --> ParseArgs
    ParseArgs --> ValidateInput
    ValidateInput --> ProcessCommand
    
    state ProcessCommand {
        [*] --> CommandType
        CommandType --> Create
        CommandType --> Read
        CommandType --> Update
        CommandType --> Delete
        
        Create --> ValidatePath
        Read --> ValidatePath
        Update --> ValidatePath
        Delete --> Confirm
        
        Confirm --> ValidatePath
        ValidatePath --> ExecuteOperation
        ExecuteOperation --> LogOperation
    }
    
    ProcessCommand --> ReturnResult
    ReturnResult --> [*]
```

## Version Control System

Version control and backup system flow:

```mermaid
flowchart TD
    A[Update Request] --> B{File Exists?}
    B -->|Yes| C[Create Backup]
    B -->|No| D[Error]
    
    C --> E[Generate Version Name]
    E --> F[Copy to Versions]
    F --> G[Update Original]
    G --> H[Log Operation]
    
    subgraph Version Naming
    E --> I[Category_YYYYMMDD_HHMMSS_filename]
    end
```

## Implementation Details

### Core Components

1. **CLI Interface (cli.c)**
   - Handles command-line argument parsing
   - Provides user interaction functions
   - Validates input parameters

2. **File Operations (file_ops.c)**
   - Manages document CRUD operations
   - Handles file system interactions
   - Implements version control logic

3. **Utilities (utils.c)**
   - Provides helper functions
   - Handles logging operations
   - Implements validation functions

4. **Storage System**
   - Organized directory structure
   - Version control implementation
   - Operation logging system

### Security Features

1. **Input Validation**
   - Filename sanitization
   - Path traversal prevention
   - Category validation

2. **Error Handling**
   - Comprehensive error messages
   - Operation logging
   - Failure recovery

### Logging System

1. **Operation Logging**
   - Timestamp-based entries
   - Operation type recording
   - File path tracking

2. **Version Control**
   - Automatic backup creation
   - Version naming convention
   - History preservation 