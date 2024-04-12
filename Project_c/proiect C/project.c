#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#define MAX_SIZE 100

typedef struct {
    char username[50];
    char password[50];
    int balance;
    time_t lastLogin;
} Account;

int deposit_amount, withdraw_amount, bet;
int getAccountBalance(char* username);
int checkAccount(char* username, Account* account);
int manageAccount(Account* account, int newAccount);
void updateAccountBalance(char* username, int newBalance);
void menu();
void menu2();
void deposit(Account* account);
void withdraw(Account* account);
void account_details(Account* account);
void blackjack(Account* account);
void HiLo(Account* account);
int registerlogin(Account* account);
int logout(Account* account);

int main()
{
    int choice;
    Account account;
    Account newAccount;

    if(registerlogin(&account) == -1)
    {
        return 0;
    }

    printf("\n");

        while(1)
    {
        menu();
        printf("\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch(choice)
        {
            case 1:
                deposit(&account); 
                break;
            case 2:
                withdraw(&account);
                break;
            case 3:
                account_details(&account);
                break;
            case 4:
                blackjack(&account);
                break;
            case 5:
                HiLo(&account);
                break;
            case 6:
                if(logout(&account) == 0)
                {
                    return 0;
                }
                break;
            default:
                printf("Invalid choice!!\n");
                break;
        }
    }

}

//The checkAccount function in C is used to check if a given username exists in a CSV file named "accounts.csv".
int checkAccount(char* username, Account* account) {
    FILE* file = fopen("accounts.csv", "r");
    if (file == NULL) {
        printf("Error opening file!\n");
        return 0;
    }

    char line[256];
    Account existingAccount;
    while (fgets(line, sizeof(line), file)) {
        sscanf(line, "%[^,],%[^,],%d\n", existingAccount.username, existingAccount.password, &existingAccount.balance);
        if (strcmp(existingAccount.username, username) == 0) {
            fclose(file);
            return 1;
        }
    }

    fclose(file);
    return 0;
}

// The getAccountBalance function in C is used to retrieve the balance of a given account from a CSV file named "accounts.csv".
int getAccountBalance(char* username) {
    FILE* file = fopen("accounts.csv", "r");
    if (file == NULL) {
        printf("Unable to open file.\n");
        return 0;
    }

    char line[256];
    while (fgets(line, sizeof(line), file)) {
        char accountUsername[50];
        int balance;
        char password[50];

        sscanf(line, "%[^,],%[^,],%d", accountUsername, password, &balance);

        if (strcmp(accountUsername, username) == 0) {
            fclose(file);
            return balance;
        }
    }

    fclose(file);
    return 0;
}

// The manageAccount function in C is used to manage (create or update) an account in a CSV file named "accounts.csv".
int manageAccount(Account* account, int newAccount) {
    if (checkAccount(account->username, account)) {
        if (newAccount) {
            printf("Account already exists.\n");
            return 0;
        }
    }

    FILE* file = fopen("accounts.csv", "a");
    if (file != NULL) {
        fprintf(file, "%s,%s,%d\n", account->username, account->password, account->balance);
        fclose(file);
        return 1;
    } else {
        printf("Unable to open file.\n");
        return 0;
    }
}

// The updateAccountBalance function in C is used to update the balance of a given account in a CSV file named "accounts.csv".
void updateAccountBalance(char* username, int newBalance) {
    FILE* file = fopen("accounts.csv", "r");
    if (file == NULL) {
        printf("Unable to open file.\n");
        return;
    }

    Account accounts[100];
    int numAccounts = 0;
    while (fscanf(file, "%[^,],%[^,],%d\n", accounts[numAccounts].username, accounts[numAccounts].password, &accounts[numAccounts].balance) == 3) {
        if (strcmp(accounts[numAccounts].username, username) == 0) {
            accounts[numAccounts].balance = newBalance;
        }
        numAccounts++;
    }
    fclose(file);

    file = fopen("accounts.csv", "w");
    if (file == NULL) {
        printf("Unable to open file.\n");
        return;
    }

    for (int i = 0; i < numAccounts; i++) {
        fprintf(file, "%s,%s,%d\n", accounts[i].username, accounts[i].password, accounts[i].balance);
    }
    fclose(file);
}

// The print_card function in C is used to print a representation of a playing card based on its number.
void print_card(int card_num) {
    switch (card_num) {
        case 1: 
        {
            printf(" ------- \n");
            printf("|       |\n");
            printf("|   A   |\n");
            printf("|       |\n");
            printf(" ------- \n");
            break;
        }
        case 2:
        case 3:
        case 4:
        case 5:
        case 6:
        case 7:
        case 8:
        case 9:
        case 10:
        {
            printf(" ------- \n");
            printf("|       |\n");
            printf("|  %2d   |\n", card_num);
            printf("|       |\n");
            printf(" ------- \n");
            break;
        }
        case 11:
        {
            printf(" ------- \n");
            printf("|       |\n");
            printf("|   J   |\n");
            printf("|       |\n");
            printf(" ------- \n");
            break;
        }
        case 12:
        {
            printf(" ------- \n");
            printf("|       |\n");
            printf("|   Q   |\n");
            printf("|       |\n");
            printf(" ------- \n");
            break;
        }
        case 13:
        {
            printf(" ------- \n");
            printf("|       |\n");
            printf("|   K   |\n");
            printf("|       |\n");
            printf(" ------- \n");
            break;
        }
    }
}

// The get_card function in C is used to generate a random card number between 1 and 13.
int get_card() {
    return rand() % 13 + 1;
}

void menu()
{ 
    printf(" \nMAIN MENU\n");
    printf("1.Deposit money\n");
    printf("2.Withdraw money\n");
    printf("3.Account details\n");
    printf("4.Play Blackjack\n");
    printf("5.Play HiLo\n");
    printf("6.Logout\n");
}

void menu2()
{
    printf("1.Register\n");
    printf("2.Login\n");
    printf("3.Exit\n");
}

void deposit(Account* account)
{
    printf("\n");
    printf("  DEPOSITING MONEY\n");
    for (int i = 0; i < 50; i++) 
    {
       printf("-");
    }
    printf("\nEnter the amount you want to deposit: ");
    scanf("%d", &deposit_amount);
    account->balance += deposit_amount;
    printf("Amount deposited successfully\n");
    printf("Account balance: %d\n", account->balance);
    printf("Press any key to continue...\n");
    while (getchar() != '\n');
    getchar();

    updateAccountBalance(account->username, account->balance);
}

void withdraw(Account* account)
{
    printf("\n");
    printf("  WITHDRAWING MONEY\n");
    for (int i = 0; i < 50; i++) 
    {
       printf("-");
    }
    printf("\nEnter the amount you want to withdraw: ");
    scanf("%d", &withdraw_amount);
    if(withdraw_amount > account->balance)
    {
        printf("Insufficient balance\n");
    }
    else
    {
        account->balance -= withdraw_amount;
        printf("Amount withdrawn successfully\n");
        printf("Account balance: %d\n", account->balance);
    }
    printf("Press any key to continue...\n");
    while (getchar() != '\n');
    getchar();

    if(withdraw_amount <= account->balance)
    {
        updateAccountBalance(account->username, account->balance);
    }
}

void account_details(Account* account) {
    printf("\n");
    printf("  ACCOUNT DETAILS\n");
    for (int i = 0; i < 50; i++) 
    {
       printf("-");
    }
    printf("\nUsername: %s\n", account->username);
    printf("Account password: %s\n", account->password);
    printf("Account balance: %d\n", account->balance);
    printf("Press any key to continue...\n");
    while (getchar() != '\n');
    getchar();
}

void blackjack(Account* account) {
    srand(time(NULL));

    int bet;
    printf("\nEnter your bet: ");
    scanf("%d", &bet);

    if (bet > account->balance) {
        printf("\nYou don't have enough balance for this bet.\n");
        return;
    }

    int playerTotal = 0, dealerTotal = 0;
    int card, cardValue;

    card = get_card();
    cardValue = (card > 10) ? 10 : card;
    printf("\nDealer's first card: \n");
    print_card(card);
    dealerTotal += cardValue;

    card = get_card();
    cardValue = (card > 10) ? 10 : card;
    printf("\nYour first card: \n");
    print_card(card);
    if (card == 1) {
        int ace_value;
        printf("You drew an Ace. Choose its value (1 or 11): ");
        scanf("%d", &ace_value);
        if (ace_value == 11) {
            cardValue = 11;
        }
    }
    playerTotal += cardValue;

    card = get_card();
    cardValue = (card > 10) ? 10 : card;
    printf("\nYour second card: \n");
    print_card(card);
    if (card == 1) {
        int ace_value;
        printf("You drew an Ace. Choose its value (1 or 11): ");
        scanf("%d", &ace_value);
        if (ace_value == 11) {
            cardValue = 11;
        }
    }
    playerTotal += cardValue;

    card = get_card();
    cardValue = (card > 10) ? 10 : card;
    dealerTotal += cardValue;

    while (playerTotal < 21) {
        char choice;
        printf("\nYour total is %d. Do you want another card? (y/n): ", playerTotal);
        scanf(" %c", &choice);

        if (choice == 'y') {
            card = get_card();
            cardValue = (card > 10) ? 10 : card;
            printf("You drew: \n");
            print_card(card);
            if (card == 1) {
                int ace_value;
                printf("You drew an Ace. Choose its value (1 or 11): ");
                scanf("%d", &ace_value);
                if (ace_value == 11) {
                    cardValue = 11;
                }
            }
            playerTotal += cardValue;
        } else {
            break;
        }
    }

    while (dealerTotal < 17) {
        card = get_card();
        card = get_card();
        cardValue = (card > 10) ? 10 : card;
        dealerTotal += cardValue;
    }

    printf("\nDealer's total is %d.\n", dealerTotal);

    if (playerTotal > 21) {
        printf("\nYou busted. You lose.\n");
    } else if (dealerTotal > 21) {
        printf("\nDealer busted. You win!\n");
        account->balance += bet;
    } else if (playerTotal > dealerTotal) {
        printf("\nYou win!\n");
        account->balance += bet;
    } else if (dealerTotal > playerTotal) {
        printf("\nYou lose.\n");
        account->balance -= bet;
    } else {
        printf("\nIt's a tie.\n");
    }

    printf("\nYour balance is now %d.\n", account->balance);

    printf("\nPress any key to continue...");
    while (getchar() != '\n');
    getchar();
}

void HiLo(Account* account) {
    srand(time(NULL));

    printf("\nEnter your bet: ");
    scanf("%d", &bet);

    if (bet > account->balance) {
        printf("\nYou don't have enough balance for this bet.\n");
        return;
    }

    int first_card = get_card();
    if (first_card >= 11 || first_card == 1) {
        print_card(first_card);
        first_card = 10;
    } else {
        print_card(first_card);
    }

    char prediction;
    printf("\nDo you think the next card will be higher or lower? Enter 'h' for higher, 'l' for lower: ");
    scanf(" %c", &prediction);

    int second_card = get_card();
    if (second_card >= 11 || second_card == 1) {
        print_card(second_card);
        second_card = 10;
    } else {
        print_card(second_card);
    }

     if (second_card == first_card) {
        printf("\nIt's a tie!\n");
    } else if ((prediction == 'h' && second_card > first_card) || (prediction == 'l' && second_card < first_card)) {
        printf("\nCongratulations! You won %d\n", bet * 2);
        account->balance += bet;
    } else {
        printf("\nSorry, you lost your bet of %d\n", bet);
        account->balance -= bet;
    }

    updateAccountBalance(account->username, account->balance);

    printf("\nPress any key to continue...");
    while (getchar() != '\n');
    getchar();
}

int registerlogin(Account* account)
{
    Account newAccount;
    int choice; 
    while(1) {
        do {
            printf("\n");
            menu2();
            printf("\n");
            printf("Enter your choice: ");
            scanf("%d", &choice);
            getchar();
        } while(choice != 1 && choice != 2 && choice != 3);
        
        if(choice == 1) {
            printf("\n");
                printf("Enter username: ");
                fgets(newAccount.username, sizeof(newAccount.username), stdin);
                newAccount.username[strcspn(newAccount.username, "\n")] = '\0';

                printf("Enter password: ");
                fgets(newAccount.password, sizeof(newAccount.password), stdin);
                newAccount.password[strcspn(newAccount.password, "\n")] = '\0';

                newAccount.balance = 0;

                if(manageAccount(&newAccount, 1)){
                    printf("Account created successfully.\n");
                }
            } 
        else if(choice == 2) {
            printf("\n");
            printf("Enter your name: ");
            fgets(account->username, sizeof(account->username), stdin);
            account->username[strcspn(account->username, "\n")] = '\0';
            
            printf("Enter your account password: ");
            fgets(account->password, sizeof(account->password), stdin);
            account->password[strcspn(account->password, "\n")] = '\0';

            account->balance = getAccountBalance(account->username);

            if (checkAccount(account->username, account)) {
                printf("\nWelcome %s!\n", account->username);
                account->balance += 100;
                updateAccountBalance(account->username, account->balance);
                break;
            } 
            else {
                printf("Account not found. Please register before logging in.\n");
            }
        }
        else if(choice == 3) {
            printf("Goodbye!\n");
            return -1;
        }
        else {
            printf("Invalid choice. Please enter 1, 2 or 3.\n");
        }
    }
    return 0;
}

int logout(Account* account) {
    // Save any unsaved changes
    updateAccountBalance(account->username, account->balance);
    printf("You have been logged out. See you next time!\n");
    if (registerlogin(account) == -1)
    {
        return 0;
    }
    else
    {
        return 1;
    }
}