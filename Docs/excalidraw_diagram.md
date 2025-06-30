```mermaid
graph TD
    %% Main Components
    A[User Input] --> B[CLI Interface]
    B --> C{Command Processor}
    
    %% Command Types
    C -->|Create| D[Textfile Creation]
    C -->|Read| E[Textfile Retrieval]
    C -->|Update| F[Textfile Update]
    C -->|Delete| G[Textfile Deletion]
    
    %% File Operations
    D --> H[File Operations]
    E --> H
    F --> H
    G --> H
    
    %% Storage Structure
    H --> I[Data Directory]
    I --> J[Recipes]
    I --> K[Notes]
    I --> L[Logs]
    I --> M[Versions]
    
    %% Logging System
    H --> N[Logging System]
    N --> O[history.txt]
    
    %% Version Control
    F --> P[Version Control]
    P --> M
    
    %% Error Handling
    H --> Q[Error Handler]
    Q --> N
    
    %% Input Validation
    B --> R[Input Validator]
    R --> C
    
```

# NoteCLI - Architecture Diagram

This diagram illustrates the complete architecture of our Notepad Command Line Base (NoteCLI). Here's what each component represents:

## Core Components
- **User Input**: Entry point for all user commands
- **CLI Interface**: Handles command-line interaction
- **Command Processor**: Routes commands to appropriate handlers

## Operations
- **Textfile Creation**: Handles new Textfile creation
- **Textfile Retrieval**: Manages Textfile reading
- **Textfile Update**: Processes Textfile modifications
- **Textfile Deletion**: Manages Textfile removal

## Storage
- **Data Directory**: Root storage location
  - Recipes: Storage for recipe Textfiles
  - Notes: Storage for note Textfiles
  - Logs: System operation logs
  - Versions: Textfile version history

## System Features
- **Logging System**: Tracks all system operations
- **Version Control**: Manages Textfile versions
- **Error Handler**: Processes and logs errors
- **Input Validator**: Ensures data integrity

## Color Legend
- Pink: User interaction points
- Light Blue: Interface components
- Light Green: Processing units
- Light Red: Core operations
- Blue: Storage components
- Yellow: System utilities 