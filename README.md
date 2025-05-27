# NADRA Management System

The NADRA Management System is a C++ console application designed to simulate a citizen database management system, similar to Pakistan's National Database and Registration Authority (NADRA). It supports user authentication with cryptographic algorithms (Complex Hash, AES, DES, RSA), family tree management for citizen data, a token-based queue system, and console theming with customizable color schemes.

# Secure Cryptography Mechanisms 

# Complex Hash:

Description: A custom hashing algorithm used to securely store sensitive user data.
Usage: Applied to usernames, passwords, CNICs, and phone numbers to generate hashed values for secure storage and authentication.
Features: Incorporates salt and pepper to enhance security against brute-force attacks.


# AES (Advanced Encryption Standard):

Description: A symmetric encryption algorithm used for securing user data.
Usage: Encrypts sensitive fields like CNIC and phone numbers in user accounts to protect against unauthorized access.
Key: Uses a user-specific AESK key stored in the Node structure.


# DES (Data Encryption Standard):

Description: A legacy symmetric encryption algorithm for additional data protection.
Usage: Provides an alternative encryption method for user data, complementing AES.
Key: Uses a user-specific DESK key stored in the Node structure.


# RSA (Rivest-Shamir-Adleman):

Description: An asymmetric encryption algorithm for secure key exchange and authentication.
Usage: Secures cryptographic keys and validates user identity during sign-in, using public/private key pairs (p, q, n, e, d).
Implementation: Integrated into the authentication process to ensure secure communication.



# Data Structures and Their Purpose

# Linked List (User Accounts):

Structure: Node in Accounts.cpp with fields like Username, password, cnic, phone, mac, cryptographic keys (AESK, DESK, RSA keys), salt, pepper, and next pointer.
Purpose: Stores and manages user account information for secure authentication and account operations (e.g., signup, sign-in, updates).


# Linked List (Activity Log Stack):

Structure: node in Accounts.cpp with data (log message), h, m, s (timestamp), and next pointer.
Purpose: Maintains a stack-based log of user activities (e.g., sign-ins, account changes) for tracking and auditing purposes.


# Binary Tree (Family Tree):

Structure: person in Nadra.cpp with fields like Fname, Lname, gender, address, ID, D, M, Y (date of birth), age, dose (vaccine doses), left (mother), and right (father).
Purpose: Organizes citizen data in a family tree structure to manage relationships (parents and children) and support demographic queries.


# Queue (Circular Linked List):

Structure: Queue in Nadra.cpp with node containing value (token number), link (pointer), and queue pointers front, rear, and counter.
Purpose: Manages a token-based queuing system for counter access, ensuring orderly processing of citizens.


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
