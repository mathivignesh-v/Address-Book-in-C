#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "contact.h"
#include "file.h" 
#include "populate.h"

void listContacts(AddressBook *addressBook) 
{
    // Sort contacts based on the chosen criteria
    if(addressBook->contactCount == 0)
    {
        printf("No contacts available\n");
        return ;
    }
    printf("------------------------------------------------------------------------------\n");
    printf("| S.no |       Name       |       Phone no     |                Mail         |\n");
    printf("------------------------------------------------------------------------------\n");
    for(int i=0;i<addressBook->contactCount;i++)
    {
        printf("| %-4d | %-17s|\t%-15s|\t%-20s |\n",i+1, addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
    }
    printf("------------------------------------------------------------------------------\n");
}

void initialize(AddressBook *addressBook) 
{
    addressBook->contactCount = 0;

    // REMOVE dummy data, because it overwrites file data
    // populateAddressBook(addressBook);

    loadContactsFromFile(addressBook);
}

void saveAndExit(AddressBook *addressBook)
{
    saveContactsToFile(addressBook);
    printf("Contacts saved. Goodbye!\n");
    exit(0);
}



void createContact(AddressBook *addressBook)
{
    if (addressBook->contactCount >= MAX_CONTACTS)
    {
        printf("Address book is full . Cannot add more contacts.\n");
        return;
    }

    Contact newContact;

    // NAME VALIDATION
    
    while (1)
    {
        int valid = 1;
        printf("Enter Name        : ");
        scanf(" %[^\n]", newContact.name);

        for (int i = 0; newContact.name[i] != '\0'; i++)
        {
            char c = newContact.name[i];

            if (!((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c == ' ') || (c == '.')))
            {
                valid = 0;
                break;
            }
        }

        if (valid)
            break;
        else
            printf("Invalid name! Use only letters and spaces.\n");
    }
   // printf("Count now = %d\n", addressBook->contactCount);


    // PHONE VALIDATION

    while (1)
    {
        int valid = 1, length = 0;
        printf("Enter Phone Number: ");
        scanf(" %[^\n]", newContact.phone);

        while (newContact.phone[length] != '\0')
        {
            length++;
        }

        if (length != 10)
        {
            valid = 0;
        }

        for (int i = 0; newContact.phone[i] != '\0'; i++)
        {
            char c = newContact.phone[i];
            if (!(c >= '0' && c <= '9'))
            {
                valid = 0;
                break;
            }
        }

        if (!valid)
        {
            printf("Invalid phone! Enter exactly 10 digits.\n");
            continue;
        }

        // DUPLICATE PHONE CHECK
        int duplicate = 0;
        for (int i = 0; i < addressBook->contactCount; i++)
        {
            int same = 1;
            for (int j = 0; newContact.phone[j] != '\0' || addressBook->contacts[i].phone[j] != '\0'; j++)
            {
                if (newContact.phone[j] != addressBook->contacts[i].phone[j])
                {
                    same = 0;
                    break;
                }
            }
            if (same)
            {
                duplicate = 1;
                break;
            }
        }

        if (duplicate)
        {
            printf("Contact already exists with this phone number!\n");
            return;
        }

        break;
    }

    // -------------------------
    // EMAIL VALIDATION
    // -------------------------
    while (1)
    {
        int valid = 1;
        int atCount = 0, dotCount = 0;

        printf("Enter Email       : ");
        scanf(" %[^\n]", newContact.email);

        for (int i = 0; newContact.email[i] != '\0'; i++)
        {
            char c = newContact.email[i];

            if (!((c >= 'a' && c <= 'z') || (c >= '0' && c <= '9') || c == '@' || c == '.' || c == '_' || c == '-'))
            {
                valid = 0;
                break;
            }

            if (c == '@') atCount++;
            if (c == '.') dotCount++;
        }

        if (atCount != 1 || dotCount == 0)
            valid = 0;

        if (!valid)
        {
            printf("Invalid email! Allowed: letters, digits, @ . _ -\n");
            continue;
        }

        // DUPLICATE EMAIL CHECK
        int duplicate = 0;
        for (int i = 0; i < addressBook->contactCount; i++)
        {
            int same = 1;
            for (int j = 0; newContact.email[j] != '\0' || addressBook->contacts[i].email[j] != '\0'; j++)
            {
                if (newContact.email[j] != addressBook->contacts[i].email[j])
                {
                    same = 0;
                    break;
                }
            }
            if (same)
            {
                duplicate = 1;
                break;
            }
        }

        if (duplicate)
        {
            printf("Contact already exists with this email!\n");
            return;
        } 

        break;
    }

    // ADD CONTACT
    addressBook->contacts[addressBook->contactCount] = newContact;
    addressBook->contactCount++;

    printf("\nContact added successfully!\n");
}


void searchContact(AddressBook *ab) 
// search contact //
{
    char key[50];
    printf("Enter Name/Number/email to search : ");
    scanf(" %[^\n]",key);

    int found = 0;
    for (int i = 0; i < ab->contactCount; i++) 
    {
        if (strstr(ab->contacts[i].name, key) || strstr(ab->contacts[i].phone, key) || strstr(ab->contacts[i].email, key)) 
        {
            {
                printf("%d) Name : %s\n   Phone: %s\n   Email: %s\n\n",i+1,ab->contacts[i].name,ab->contacts[i].phone,ab->contacts[i].email);
                found = 1;
            }
        }
    }
           if(found != 1)
            {
                printf(".... No details available ....");
            }
        }

void editContact(AddressBook *addressBook)
{
    char key[50];
    printf("Enter Name/Number/Email to edit : ");
    scanf(" %[^\n]", key);

    int foundIndexes[100];
    int foundCount = 0;

    // Search contacts
    for (int i = 0; i < addressBook->contactCount; i++)
    {
        if (strstr(addressBook->contacts[i].name, key) || strstr(addressBook->contacts[i].phone, key) || strstr(addressBook->contacts[i].email, key))
        {
            foundIndexes[foundCount++] = i;
        }
    }

    // No match found
    if (foundCount == 0)
    {
        printf("\nNo matching contact found!\n");
        return;
    }

    // Show matches
    printf("\n--- Matching Contacts ---\n");
    for (int i = 0; i < foundCount; i++)
    {
        int index = foundIndexes[i];
        printf("%d) %s\t%s\t%s\n",i + 1,addressBook->contacts[index].name,addressBook->contacts[index].phone,addressBook->contacts[index].email);
    }

    int editIndex;

    // Direct edit if only one match
    if (foundCount == 1)
    {
        editIndex = foundIndexes[0];
        printf("\nOnly one match found.\n");
    }
    else
    {
        int choice;
        printf("\nSelect contact number to edit : ");
        if (scanf("%d", &choice) != 1)
        {
            printf("Invalid input!\n");
            while (getchar() != '\n');
            return;
        }

        if (choice < 1 || choice > foundCount)
        {
            printf("Invalid choice!\n");
            return;
        }

        editIndex = foundIndexes[choice - 1];
        while (getchar() != '\n');
    }

    // display contact
    printf("\n--- Editing Contact ---\n");
    printf("Name  : %s\n",  addressBook->contacts[editIndex].name);
    printf("Phone : %s\n",  addressBook->contacts[editIndex].phone);
    printf("Email : %s\n\n", addressBook->contacts[editIndex].email);

    // Edit menu
    int option;
    printf("What do you want to edit?\n");
    printf("1. Name\n");
    printf("2. Phone\n");
    printf("3. Email\n");
    printf("4. Edit ALL (Name + Phone + Email)\n");
    printf("Enter choice : ");
    if (scanf("%d", &option) != 1)
    {
        printf("Invalid input!\n");
        while (getchar() != '\n');
        return;
    }

    getchar();

    char newValue[100], newPhone[100], newEmail[100];

    switch (option)
    {
        case 1:
            printf("Enter new name : ");
            scanf(" %[^\n]", addressBook->contacts[editIndex].name);
            break;

        case 2:
            printf("Enter new phone : ");
            scanf(" %[^\n]", newValue);

            for (int i = 0; i < addressBook->contactCount; i++)
            {
                if (i != editIndex &&
                    strcmp(addressBook->contacts[i].phone, newValue) == 0)
                {
                    printf("\nContact already exists with this phone number!\n");
                    return;
                }
            }

            strcpy(addressBook->contacts[editIndex].phone, newValue);
            break;

        case 3:
            printf("Enter new email : ");
            scanf(" %[^\n]", newValue);

            for (int i = 0; i < addressBook->contactCount; i++)
            {
                if (i != editIndex &&
                    strcmp(addressBook->contacts[i].email, newValue) == 0)
                {
                    printf("\nContact already exists with this email!\n");
                    return;
                }
            }

            strcpy(addressBook->contacts[editIndex].email, newValue);
            break;

        case 4:
            printf("Enter new name  : ");
            scanf(" %[^\n]", addressBook->contacts[editIndex].name);

            printf("Enter new phone : ");
            scanf(" %[^\n]", newPhone);

            // Phone duplicate check
            for (int i = 0; i < addressBook->contactCount; i++)
            {
                if (i != editIndex &&  strcmp(addressBook->contacts[i].phone, newPhone) == 0)
                {
                    printf("\nContact already exists with this phone number!\n");
                    return;
                }
            }

            printf("Enter new email : ");
            scanf(" %[^\n]", newEmail);

            // Email duplicate check
            for (int i = 0; i < addressBook->contactCount; i++)
            {
                if (i != editIndex && strcmp(addressBook->contacts[i].email, newEmail) == 0)
                {
                    printf("\nContact already exists with this email!\n");
                    return;
                }
            }

            // Apply all updates
            strcpy(addressBook->contacts[editIndex].phone, newPhone);
            strcpy(addressBook->contacts[editIndex].email, newEmail);

            break;

        default:
            printf("Invalid option!\n");
            return;
    }

    printf("\nContact updated successfully!\n");
}

void deleteContact(AddressBook *addressBook)
{
    char key[50];
    printf("Enter Name/Number/Email to delete : ");
    scanf(" %[^\n]", key);

    int foundIndexes[100];
    int foundCount = 0;

    // Search contacts
    for (int i = 0; i < addressBook->contactCount; i++)
    {
        if (strstr(addressBook->contacts[i].name, key) || strstr(addressBook->contacts[i].phone, key) || strstr(addressBook->contacts[i].email, key))
        {
            foundIndexes[foundCount++] = i;
        }
    }

    // No match found
    if (foundCount == 0)
    {
        printf("\nNo matching contact found!\n");
        return;
    }

    // Show matches
    printf("\n--- Matching Contacts ---\n");
    for (int i = 0; i < foundCount; i++)
    {
        int index = foundIndexes[i];
        printf("%d) %s\t%s\t%s\n",i + 1,addressBook->contacts[index].name,addressBook->contacts[index].phone,addressBook->contacts[index].email);
    }

    int deleteIndex;

    // Auto-select if only one match
    if (foundCount == 1)
    {
        deleteIndex = foundIndexes[0];
        printf("\nOnly one match found.\n");
    }
    else
    {
        // Ask user which contact to delete
        int choice;
        printf("\nSelect contact number to delete : ");
        scanf("%d", &choice);

        if (choice < 1 || choice > foundCount)
        {
            printf("Invalid choice!\n");
            return;
        }

        deleteIndex = foundIndexes[choice - 1];
    }

    // Show "Deleting Contact" 
    printf("\n--- Deleting Contact ---\n");
    printf("Name  : %s\n",  addressBook->contacts[deleteIndex].name);
    printf("Phone : %s\n",  addressBook->contacts[deleteIndex].phone);
    printf("Email : %s\n\n", addressBook->contacts[deleteIndex].email);


    // Ask for confirmation
    char ch;
    printf("Are you sure you want to delete this contact? (y/n): ");
    scanf(" %c", &ch);

    if (ch == 'y' || ch == 'Y')
    {
        // Delete contact: shift all next entries left
        for (int i = deleteIndex; i < addressBook->contactCount - 1; i++)
        {
            addressBook->contacts[i] = addressBook->contacts[i + 1];
        }

        addressBook->contactCount--;

        printf("\nContact deleted successfully!\n");
    }
    else
    {
        printf("\nDeletion cancelled.\n");
    }
}

   

