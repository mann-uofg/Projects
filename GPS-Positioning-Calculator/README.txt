GPS Position Calculation

Input

The program requires user input for the reference user and, optionally, the path to a file containing data for other users.

1. **Reference User Data:**
   - Enter the name, latitude, longitude, altitude, and time for the reference user.

2. **Input File:**
   - If using a file, provide the path to the file. The file should start with the number of users, followed by user data.

Output

The program displays user data, distances, and identifies the nearest user to the reference user.

Usage

1. Compile:
   
   gcc -o gps gps.c

2. Run:

   ./gps

