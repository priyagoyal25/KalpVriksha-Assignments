# KalpVriksha-Assignments
## CRUD Operations in File Using C
This project implements a User Management System in C that performs CRUD operations (Create, Read, Update, Delete) on user records stored in a text file. Each user record contains three fields: Unique ID, Name, and Age.

## Problem Statement
+ Create a file to store data if not exist
+ Ensuring data is stored in a structured format.
+ Preventing duplicate entries.
+ Performing operations (like updates or deletions) without corrupting the file content.

## Features
+ Create User
  - Adds a new user to the file with a unique ID, name, and age.
  - Automatically verifies that the entered ID is unique.
+ Read Users
  - Displays all user records stored in the file.
  - Notifies the user if no records are present.
+ Update User
  - Allows modification of user details by ID.
  - Gives options to update: Name, Age or Both
+ Delete User
  - Removes a user record by their unique ID.
+ File Handling
  - Automatically creates users.txt if it doesn’t exist.
