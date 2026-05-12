address_book : main.o populate.o file.o contact.o
	gcc -o address_book main.o populate.o file.o contact.o
main.o:main.
	gcc - main.
populate.o:populate.
	gcc - populate.
file.o:file.
	gcc - file.
contact.o:contact.
	gcc - contact.
clean:
	rm *.exe *.o