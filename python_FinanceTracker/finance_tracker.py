import json
import os
import datetime

TRANSACTION_LOG = "transaction_log.json"
BALANCE_LOG = "balance_log.json"

# --- Helper Functions --- #

def is_valid_input(testedVar, desiredType: type) -> bool:
    try:
        desiredType(testedVar)
    except:
        return False
    else:
        return True

# --- Main Code Function --- #

def save_transactions(transactions):
    try:
        with open(TRANSACTION_LOG, "w") as file:
            json.dump(transactions, file, indent=4)
    except:
        print("Save Error")


def load_program(transactions, transaction_ID, running_balance):
    if os.path.exists(TRANSACTION_LOG):
        try:
            with open(TRANSACTION_LOG, "r") as f:
                transactions = json.load(f)
        except:
            print("Transaction Retrieval Error")

    for ID in transactions:
        running_balance += transactions[ID][0]

        if int(transaction_ID) < int(ID):
            transaction_ID = ID
        else:
            transaction_ID = str(int(transaction_ID) + 1)

        #print(f"DEBUG: Transaction ID: {transaction_ID}")

    return transactions, transaction_ID, running_balance


def view_transactions(transactions, wait_for_input: bool) -> None:
    if not transactions:
        print("No transactions logged")
    else:
        print("\nYour current transactions are: ")
        for ID in transactions:
            print(f"ID:{ID} | "
                  f"Cost: ${transactions[ID][0]} | "
                  f"Description: {transactions[ID][1]} | "
                  f"Date: {transactions[ID][2]}")
    if wait_for_input:
        buffer = None
        while buffer is None:
            buffer = input("Hit enter when ready to continue")


def log_transaction(transactions, transaction_ID, purpose: str):
    if purpose == "income":
        str_bal_change = input("\nHow much money would you like to add to your balance? (-1 to go back)\n$")
    else:
        str_bal_change = input("\nHow much money would you like to deduct from your balance? (-1 to go back)\n$")

    while (not is_valid_input(str_bal_change, float) or (float(str_bal_change) < -1)):
        str_bal_change = input("Please input an amount more than 0 (-1 to go back)\n$")

    if str_bal_change == "-1":
        return transactions, transaction_ID, 0

    if purpose == "income":
        float_bal_change = float(str_bal_change)
    else:
        float_bal_change = float(str_bal_change) * -1

    transaction_desc = input("\nIf you'd like, provide a description:\n")
    transaction_date = datetime.datetime.now().strftime("%Y-%m-%d %H:%M:%S")
    t_data = [float_bal_change, transaction_desc, transaction_date]
    transactions.update({transaction_ID: t_data})
    transaction_ID = str(int(transaction_ID) + 1)

    save_transactions(transactions)

    return transactions, transaction_ID, float_bal_change


def delete_transaction(transactions, transaction_ID):
    if not transactions:
        print("There are no transactions to delete.\n")
        return transactions, 0
    
    view_transactions(transactions, False)
    ID_to_delete = input("Which transaction would you like to delete? (-1 to go back)\nPlease enter its ID: ")

    if ID_to_delete == "-1":
        return transactions, 0
    
    while (not is_valid_input(ID_to_delete, int) or
          (int(ID_to_delete) > int(transaction_ID)) or
          (ID_to_delete not in transactions)):
        
        ID_to_delete = input("Please input a valid transaction ID (-1 to go back): ")
        if ID_to_delete == "-1":
            return transactions, 0
        
    amount = transactions[ID_to_delete][0]
    transactions.pop(ID_to_delete)
    return transactions, amount


def menu(running_balance):
    print(f"\nYour current balance is ${running_balance}")
    str_choice = input("What would you like to do?\n "
                       "(1) Add income\n "
                       "(2) Add expense\n "
                       "(3) View transactions\n "
                       "(4) Delete transaction\n "
                       "(5) Quit program\n"
                       "Choice: ")

    while (not is_valid_input(str_choice, int) or (int(str_choice) < 1) or (int(str_choice) > 5)):
        str_choice = input("Please input 1-5: ")

    return int(str_choice)


def main():
    transactions = {}
    transaction_ID = '1'
    running_balance = 0

    print("Welcome. This is a basic finance tracker.")

    transactions, transaction_ID, running_balance = load_program(
        transactions, transaction_ID, running_balance
    )

    while True:
        choice = menu(running_balance)

        if choice == 1:
            transactions, transaction_ID, change = log_transaction(
                transactions, transaction_ID, "income"
            )
            running_balance += change

        elif choice == 2:
            transactions, transaction_ID, change = log_transaction(
                transactions, transaction_ID, "expense"
            )
            running_balance += change

        elif choice == 3:
            view_transactions(transactions, True)

        elif choice == 4:
            transactions, change = delete_transaction(transactions, transaction_ID)
            running_balance -= change

        elif choice == 5:
            save_transactions(transactions)
            print("Goodbye!")
            break

        else:
            print("Unsure how you got here honestly. Good job.")


if __name__ == "__main__":
    main()