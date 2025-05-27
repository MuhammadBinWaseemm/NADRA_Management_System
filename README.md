
# NADRA Management System

# Overview
The NADRA Management System is a C++ console application designed to simulate a citizen database management system, similar to Pakistan's National Database and Registration Authority (NADRA). It supports user authentication with cryptographic algorithms (Complex Hash, AES, DES, RSA), family tree management for citizen data, a token-based queue system, and console theming with customizable color schemes.

# Data Structures
The system uses the following data structures to manage data efficiently:

# Linked List (User Accounts):

File: Accounts.cpp
Structure: Node
Fields: Username, password, cnic, phone, mac, Salt, Pepper, AESK, DESK, RSA keys (p, q, n, e, d), hashed values (hashedpassword, hashedcnic, etc.), and next pointer.
Purpose: Stores user account details for secure authentication.
Functions: insertNode, delnode, searchuser, updateuser, updatepass, printlist, printlistt.

# Linked List (Activity Log Stack):

File: Accounts.cpp
Structure: node
Fields: data (log message), h, m, s (timestamp), and next pointer.
Purpose: Logs user activities (e.g., sign-ins, account changes) in a stack.
Functions: push, display.

# Binary Tree (Family Tree):

File: Nadra.cpp
Structure: person
Fields: Fname, Lname, gender, address, ID, D, M, Y (date of birth), age, dose (vaccine doses), left (mother), right (father).
Purpose: Manages citizen data in a family tree structure, linking individuals to their parents.
Functions: addNewPerson, addMother, addFather, search, show, card, Ccertificate, printInOrder, saveData, addToFile, readFromFile.

# Queue (Token System):

File: Nadra.cpp
Structure: Queue with node
Fields: value (token number), link (circular linked list), front, rear, counter.
Purpose: Manages token-based access to counters.
Functions: enQueue, checkCounter, checkTokenNumber.

# Sound Files

The application uses sound effects for user feedback, played via PlaySound from <windows.h>. The sound files and their default paths are:
Bubble.wav: Played on successful actions (e.g., account creation, password change).
Path: C:/Users/PC/Downloads/Bubble.wav


User.wav: Played on invalid inputs (e.g., username taken, invalid CNIC).
Path: C:/Users/PC/Downloads/User.wav


Denied.wav: Played on authentication failures (e.g., wrong password, invalid MAC).
Path: C:/Users/PC/Downloads/Denied.wav


Access.wav: Played on successful sign-in.
Path: C:/Users/PC/Downloads/Access.wav



# Handling Sound File Paths
To use the sound files:

Verify File Locations:
Ensure the .wav files exist at the specified paths (C:/Users/PC/Downloads/).
If files are located elsewhere, update the paths in Accounts.cpp within the PlaySound calls.


Update Paths:
Example: Change PlaySound(TEXT("C:/Users/PC/Downloads/Bubble.wav"), NULL, SND_FILENAME | SND_SYNC) to PlaySound(TEXT("D:/Sounds/Bubble.wav"), NULL, SND_FILENAME | SND_SYNC) if the file is in D:/Sounds/.
Use forward slashes (/) or double backslashes (\\) for Windows paths.


Permissions: Ensure the program has read access to the sound files. Consider placing them in the project directory for simplicity.
Windows Dependency: The PlaySound function is Windows-specific. For non-Windows systems, replace with a cross-platform audio library (e.g., SFML) or comment out PlaySound calls to disable audio.
Missing Files: If sound files are unavailable, comment out PlaySound lines to run the program without audio feedback.

# Features

User Authentication: Supports signup, signin, and password recovery with Complex Hash, AES, DES, or RSA encryption.
Family Tree Management: Add citizens, view details, generate ID cards, and issue COVID-19 vaccination certificates.
Token System: Manages counter access using a queue-based token system.
Theming: Customizable console themes (Default, Zebra, Aqua, Buraikan, Blueberry, Jamun).
Data Persistence: Saves citizen data to Record.txt.

# How to Use
Main Files

Nadra.cpp is the main file that drives the program. Accounts.cpp is a supplementary file for managing user account creation. It does not function independently.

# Audio Files

.wav files are included for sound effects and are compatible with Dev-C++. Compatibility with other IDEs, such as Visual Studio, is not guaranteed.

Setup Instructions

Download Nadra.cpp, Accounts.cpp, and the .wav files to your system. Ensure the .wav files are placed in a directory of your choice and update the file paths in the code. For example: PlaySound(TEXT("C:/Users/PC/Downloads/User.wav"), NULL, SND_FILENAME | SND_SYNC); Replace the file path with the location of the .wav file on your system. Placing them in the Downloads folder will minimize changes.

# Configuring Sound in Dev-C++

To enable sound functionality in Dev-C++, follow these steps: Go to Tools > Compiler Options. Add -lwinmm to the linker commands.

# Support

If you encounter any issues or need assistance, feel free to contact me. I’ll be happy to help resolve any problems.
