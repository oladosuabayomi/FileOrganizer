#include "file_organizer.h"
#include <iostream>
#include <string>

void show_help() {
    std::cout << "File Organizer v1.0.0" << std::endl;
    std::cout << "Automatic file organization by type with undo functionality" << std::endl;
    std::cout << std::endl;
    std::cout << "USAGE:" << std::endl;
    std::cout << "  file-organizer [COMMAND] [OPTIONS] <directory>" << std::endl;
    std::cout << std::endl;
    std::cout << "COMMANDS:" << std::endl;
    std::cout << "  --list <directory>              List files and their categories" << std::endl;
    std::cout << "  --organize <directory>          Organize files in directory" << std::endl;
    std::cout << "  --undo <directory>              Undo last organization" << std::endl;
    std::cout << "  --undo <directory> --session <id>  Undo specific session" << std::endl;
    std::cout << "  --history <directory>           Show organization history" << std::endl;
    std::cout << "  --interactive                   Start interactive mode" << std::endl;
    std::cout << "  --help                          Show this help message" << std::endl;
    std::cout << "  --version                       Show version information" << std::endl;
    std::cout << std::endl;
    std::cout << "EXAMPLES:" << std::endl;
    std::cout << "  file-organizer --list ~/Downloads" << std::endl;
    std::cout << "  file-organizer --organize ~/Downloads" << std::endl;
    std::cout << "  file-organizer --undo ~/Downloads" << std::endl;
    std::cout << "  file-organizer --interactive" << std::endl;
    std::cout << std::endl;
    std::cout << "SUPPORTED CATEGORIES:" << std::endl;
    std::cout << "  Documents: PDF, DOC, TXT, etc." << std::endl;
    std::cout << "  Images: JPG, PNG, GIF, etc." << std::endl;
    std::cout << "  Videos: MP4, AVI, MKV, etc." << std::endl;
    std::cout << "  Audio: MP3, WAV, FLAC, etc." << std::endl;
    std::cout << "  Others: All other file types" << std::endl;
}

void show_version() {
    std::cout << "File Organizer v1.0.0" << std::endl;
    std::cout << "Built with C++17" << std::endl;
    std::cout << "Copyright (c) 2025" << std::endl;
}

void interactive_mode() {
    FileOrganizer organizer;
    std::string choice, directory_path, session_id;
    
    std::cout << "File Organizer - Interactive Mode" << std::endl;
    std::cout << std::string(40, '=') << std::endl;
    std::cout << std::endl;
    
    while (true) {
        std::cout << "Available Commands:" << std::endl;
        std::cout << "  1. List files in directory" << std::endl;
        std::cout << "  2. Organize directory" << std::endl;
        std::cout << "  3. Undo organization" << std::endl;
        std::cout << "  4. Show organization history" << std::endl;
        std::cout << "  5. Exit" << std::endl;
        std::cout << std::endl;
        std::cout << "Enter your choice (1-5): ";
        std::getline(std::cin, choice);
        
        if (choice == "1") {
            std::cout << "Enter directory path: ";
            std::getline(std::cin, directory_path);
            
            if (!directory_path.empty()) {
                std::cout << std::endl;
                organizer.list_files(directory_path);
                std::cout << std::endl;
            }
        }
        else if (choice == "2") {
            std::cout << "Enter directory path to organize: ";
            std::getline(std::cin, directory_path);
            
            if (!directory_path.empty()) {
                std::cout << std::endl;
                organizer.organize_directory(directory_path);
                std::cout << std::endl;
            }
        }
        else if (choice == "3") {
            std::cout << "Enter directory path: ";
            std::getline(std::cin, directory_path);
            
            if (!directory_path.empty()) {
                std::cout << "Enter session ID (or press Enter for latest): ";
                std::getline(std::cin, session_id);
                std::cout << std::endl;
                organizer.undo_organization(directory_path, session_id);
                std::cout << std::endl;
            }
        }
        else if (choice == "4") {
            std::cout << "Enter directory path: ";
            std::getline(std::cin, directory_path);
            
            if (!directory_path.empty()) {
                std::cout << std::endl;
                organizer.show_history(directory_path);
                std::cout << std::endl;
            }
        }
        else if (choice == "5" || choice == "exit" || choice == "quit") {
            std::cout << "Goodbye!" << std::endl;
            break;
        }
        else {
            std::cout << "Invalid choice. Please try again." << std::endl << std::endl;
        }
    }
}

int main(int argc, char* argv[]) {
    FileOrganizer organizer;
    
    if (argc == 1) {
        show_help();
        return 0;
    }
    
    std::string command = argv[1];
    
    if (command == "--help" || command == "-h") {
        show_help();
    }
    else if (command == "--version" || command == "-v") {
        show_version();
    }
    else if (command == "--interactive" || command == "-i") {
        interactive_mode();
    }
    else if (command == "--list" && argc >= 3) {
        std::string directory_path = argv[2];
        if (!organizer.list_files(directory_path)) {
            return 1;
        }
    }
    else if (command == "--organize" && argc >= 3) {
        std::string directory_path = argv[2];
        if (!organizer.organize_directory(directory_path)) {
            return 1;
        }
    }
    else if (command == "--undo" && argc >= 3) {
        std::string directory_path = argv[2];
        std::string session_id = "";
        
        // Check for --session flag
        if (argc >= 5 && std::string(argv[3]) == "--session") {
            session_id = argv[4];
        }
        
        if (!organizer.undo_organization(directory_path, session_id)) {
            return 1;
        }
    }
    else if (command == "--history" && argc >= 3) {
        std::string directory_path = argv[2];
        if (!organizer.show_history(directory_path)) {
            return 1;
        }
    }
    else {
        std::cerr << "Error: Invalid arguments. Use --help for usage information." << std::endl;
        return 1;
    }
    
    return 0;
}
