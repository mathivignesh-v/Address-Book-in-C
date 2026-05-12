#ifndef CONTACT_H
#define CONTACT_H

#define MAX_CONTACTS 100

typedef struct
 {
    char name[50];
    char phone[20];
    char email[50];
} Contact;

typedef struct 
{
    Contact contacts[MAX_CONTACTS];
    int contactCount;
} AddressBook;

/* Core operations */
void createContact(AddressBook *);
void listContacts(AddressBook *);
void searchContact(AddressBook *);
void editContact(AddressBook *);
void deleteContact(AddressBook *);
void initialize(AddressBook *);
void saveAndExit(AddressBook *);

/* File operations */
void saveContactsToFile(AddressBook *);
void loadContactsFromFile(AddressBook *);

#endif
