```mermaid
graph TD
    %% Main Components
    A[User Input] --> B[CLI Interface]
    B --> C{Command Processor}
    
    %% Command Types
    C -->|Create| D[Document Creation]
    C -->|Read| E[Document Retrieval]
    C -->|Update| F[Document Update]
    C -->|Delete| G[Document Deletion]
    
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
    
    style A fill:#f9f,stroke:#333,stroke-width:2px
    style B fill:#bbf,stroke:#333,stroke-width:2px
    style C fill:#dfd,stroke:#333,stroke-width:2px
    style H fill:#fdd,stroke:#333,stroke-width:2px
    style I fill:#ddf,stroke:#333,stroke-width:2px
    style N fill:#ffd,stroke:#333,stroke-width:2px

%% Additional Styling
classDef storage fill:#e1f5fe,stroke:#01579b,stroke-width:2px;
class J,K,L,M storage;

%% Relationships
classDef process fill:#e8f5e9,stroke:#2e7d32,stroke-width:2px;
class D,E,F,G process;

%% System Components
classDef system fill:#fff3e0,stroke:#ef6c00,stroke-width:2px;
class P,Q,R system;
```

# Document Management System - Architecture Diagram

This diagram illustrates the complete architecture of our Document Management System (DMS). Here's what each component represents:

## Core Components
- **User Input**: Entry point for all user commands
- **CLI Interface**: Handles command-line interaction
- **Command Processor**: Routes commands to appropriate handlers

## Operations
- **Document Creation**: Handles new document creation
- **Document Retrieval**: Manages document reading
- **Document Update**: Processes document modifications
- **Document Deletion**: Manages document removal

## Storage
- **Data Directory**: Root storage location
  - Recipes: Storage for recipe documents
  - Notes: Storage for note documents
  - Logs: System operation logs
  - Versions: Document version history

## System Features
- **Logging System**: Tracks all system operations
- **Version Control**: Manages document versions
- **Error Handler**: Processes and logs errors
- **Input Validator**: Ensures data integrity

## Color Legend
- Pink: User interaction points
- Light Blue: Interface components
- Light Green: Processing units
- Light Red: Core operations
- Blue: Storage components
- Yellow: System utilities 