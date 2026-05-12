#include <stdio.h>
#include <string.h>
#include "contact.h"

//#define FILE_NAME "contacts.txt"

void saveContactsToFile(AddressBook *ab) 
{
    FILE *fp = fopen("contacts.csv", "w");
    if (!fp)
     {
        printf("Error saving file!\n");
        return;
    }

    for (int i = 0; i < ab->contactCount; i++) 
    {
        fprintf(fp, "%s\t%s\t%s\n",ab->contacts[i].name,ab->contacts[i].phone,ab->contacts[i].email);
    }

    fclose(fp);
    printf("Contacts saved successfully.\n");
}

void loadContactsFromFile(AddressBook *ab) 
{
    FILE *fp = fopen("contacts.csv", "r");
    if (!fp) 
    {
        return ;
     }                 // No file yet

    ab->contactCount = 0;

    while (!feof(fp) && ab->contactCount < MAX_CONTACTS) 
    {
        Contact *c = &ab->contacts[ab->contactCount];
        if (fscanf(fp, "%s\t%s\t%s\n", c->name, c->phone, c->email) == 3)
         {
            ab->contactCount++;
        }
    }

    fclose(fp);
    printf("\n%d contacts loaded.\n", ab->contactCount);
}
