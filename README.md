# Bank and Casino System

This is a C-based console application for managing bank accounts and playing simple casino games like Blackjack and HiLo. The application allows users to create accounts, deposit and withdraw money, view account details, and play casino games to win or lose money.

## Features

- **Account Management**: Create new accounts, login, deposit, and withdraw money.
- **Account Details**: View account details including username, password, and balance.
- **Casino Games**: Play Blackjack and HiLo games to win or lose money.
- **Persistent Storage**: Account details are stored in a CSV file for persistent storage.

## How to Use

### Main Menu Options:
1. **Deposit money**: Add money to your account.
2. **Withdraw money**: Remove money from your account.
3. **Account details**: View details of your account.
4. **Play Blackjack**: Play a game of Blackjack.
5. **Play HiLo**: Play a HiLo card game.
6. **Logout**: Logout from your account.

### Casino Games:
- **Blackjack**: A simplified version of Blackjack where you can bet and try to beat the dealer's hand.
- **HiLo**: Predict whether the next card will be higher or lower than the current card.

## Requirements

- **C Compiler**: Ensure you have a C compiler installed (like GCC).

## How to Run

Go to your compiler, open the `project.c` file, and run it with the compiler. You can then enjoy it in your terminal!


## Functions Overview

- **checkAccount**: Verifies if a given username exists in the CSV file.
- **getAccountBalance**: Retrieves the balance of a given account from the CSV file.
- **manageAccount**: Manages (creates or updates) an account in the CSV file.
- **updateAccountBalance**: Updates the balance of a given account in the CSV file.
- **print_card**: Prints a representation of a playing card.
- **get_card**: Generates a random card number between 1 and 13.
- **menu**: Displays the main menu.
- **menu2**: Displays the registration/login menu.
- **deposit**: Handles depositing money into an account.
- **withdraw**: Handles withdrawing money from an account.
- **account_details**: Displays the details of an account.
- **blackjack**: Implements the Blackjack game logic.
- **HiLo**: Implements the HiLo card game logic.
- **registerlogin**: Handles user registration and login.
- **logout**: Logs out the user and updates the account balance.

## Account Management

### Register:
1. Select **Register** from the menu.
2. Enter your desired username and password.
3. Your account will be created with a starting balance of 0.

### Login:
1. Select **Login** from the menu.
2. Enter your username and password.
3. If the account exists, you will be logged in and awarded a bonus of 100 units.

### Logout:
1. Select **Logout** from the main menu.
2. Your account balance will be saved, and you will be logged out.
