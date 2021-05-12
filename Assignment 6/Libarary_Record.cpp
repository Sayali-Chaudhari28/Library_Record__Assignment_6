/***********************************************************************************************************************************
												ASSIGNMENT 6
TITLE:College Library maintains records of books.  Write a program using C++  for following operations :
1. Add a new book details. 
2. Search a book in library.
3. Sort books  based on ISBN numbers.
4. List all books of specific author.
Use  appropriate data structure.
-----------------------------------------------------------------------------------------------------------------------------------
NAME		: Sayali Narendra Chaudhari
ROLL NO.	: 2377
C NUMBER	: C22020222303
DIV			: A
BATCH		: A3
GITHUB LINK	: https://github.com/Sayalinc28/Library_Record__Assignment_6/blob/master/Assignment%206/Libarary_Record.cpp
************************************************************************************************************************************/

#include <iostream>
#include <string>
using namespace std;
class node {
	string author_name, book_name, publication;
	int isbn_no;
	node* next;
public:
	friend class Library;
	node(string author, string book, string publication_, int isbn){
		author_name = author;
		book_name = book;
		publication = publication_;
		isbn_no = isbn;
		next = NULL;
	}
};
class Library {
	node* head;
public:
	Library() {
		head = NULL;
	}
	void add_new_book();
	void list_specific_author_book();
	node* search_book(int);
	node* middle(node* start, node* last);
	void display();

	//for sorting
	void sort_books();
	void swap(node*, node*);
};

//---------------------ADD NEW BOOK DETAILS TO LIBRARY-------------------
void Library::add_new_book() {
	string author, book, publication_;
	int isbn;
	cout << "Enter book name: ";
	cin >> book;
	cout << "Enter author name: ";
	cin >> author;
	cout << "Enter publication: ";
	cin >> publication_;
	cout << "Enter ISBN number: ";
	cin >> isbn;
	node* new_node = new node(author, book, publication_, isbn);
	if (head == NULL) {
		head = new_node;
	}
	else {
		node* temp;
		temp = head;
		while (temp->next != NULL) {
			temp = temp->next;
		}
		temp->next = new_node;
		new_node->next = NULL;
	}
	cout << "\n----------------------------------------------";
	cout << "\nNew book added to library!";
	cout << "\nBook name: " << new_node->book_name;
	cout << "\nAuthor Name: " << new_node->author_name;
	cout << "\nPublication: " << new_node->publication;
	cout << "\nISBN Number: " << new_node->isbn_no;
}
void Library :: display() {
	node* temp;
	cout << "\nISBN NO.\tAUTHOR NAME\t\tBOOK NAME\t\tPUBLICATION";
	for (temp = head; temp != NULL; temp = temp->next) {
		cout << "\n" << temp->isbn_no <<"\t\t"<< temp->author_name << "\t\t\t" << temp->book_name << "\t\t\t" << temp->publication;
	}
}

//------------------LIST ALL BOOKS OF SPECIFIC AUTHOR----------------------
void Library::list_specific_author_book() {						//Using sequential search
	node* temp;
	string specific_author; int flag = 0;
	cout << "Enter the author name of book you want: ";
	cin >> specific_author;
	cout << "\n...................................................................................................................";
	cout << "\nISBN NO.\t\tAUTHOR NAME\t\t\tBOOK NAME\t\tPUBLICATION";
	cout << "\n...................................................................................................................";
	for (temp = head; temp != NULL; temp = temp->next) {
		if (specific_author == temp->author_name) {
			cout <<"\n"<< temp->isbn_no <<"\t\t"<< temp->author_name << "\t\t" << "\t" << temp->book_name << "\t\t" << temp->publication;
			flag = 1;
		}
	}
	if (flag == 0) {
		cout << "No such author's book found in the library";
	}
}

//-------------------------------SORTING BOOKS-----------------------------
void Library::swap(node* temp, node* temp2)
{
	string name_, author_, publication_;
	int isbn_;

	name_ = temp->book_name;                               //swap temp1=i 
	author_ = temp->author_name;
	publication_ = temp->publication;
	isbn_ = temp->isbn_no;

	// i=j
	temp->book_name = temp2->book_name;
	temp->author_name = temp2->author_name;
	temp->publication = temp2->publication;
	temp->isbn_no = temp2->isbn_no;

	// j=temp1
	temp2->book_name = name_;
	temp2->author_name = author_;
	temp2->publication = publication_;
	temp2->isbn_no = isbn_;
}
void Library::sort_books() {
		node* i, * j;
		for (i = head; i->next != NULL; i = i->next)
		{
			for (j = i->next; j != NULL; j = j->next)
			{
				if (i->isbn_no > j->isbn_no)
				{
					swap(i, j);
				}
			}
		}
		display();
}


//---------------------------SEARCH BOOK BY ISBN NUMBER-------------------------------
node* Library::middle(node* start, node* last)
{
	if (start == NULL) {
		return NULL;
	}

	node* slow = start;
	node* fast = start->next;

	while (fast != last)
	{
		fast = fast->next;
		if (fast != last)
		{
			slow = slow->next;
			fast = fast->next;
		}
	}

	return slow;
}
node* Library ::search_book(int value)				//Binary Search
{
	node* start = head;
	node* last = NULL;
	node* mid;
	do
	{
		if (head == NULL) {
			cout << "Library is Empty";
			break;
		}
		// Find middle
		node* mid = middle(start, last);

		// If middle is empty
		if (mid == NULL)
			return NULL;

		// If value is present at middle
		if (mid->isbn_no == value) {

			return mid;
		}
		// If value is more than mid
		else if (mid->isbn_no < value)
			start = mid->next;

		// If the value is less than mid.
		else
			last = mid;

	} while (last == NULL || last != start);
}
int main() {
	Library l;
	int choice;
	do {
		cout << "\t\nWELCOME TO LIBRARY";
		cout << "\n----------------------------------------------";
		cout << "\n1. Add new book details \n2. List all books of specific author \n3. Sort books based on ISBN number \n4. Search book in the library \n5. Exit";
		cout << "\n______________________________________________";
		cout<<"\nEnter your choice : ";
		cin >> choice;
		switch (choice) {
		case 1: l.add_new_book();
			cout << "\n______________________________________________\n";
			break;
		case 2: l.list_specific_author_book();
			cout << "\n______________________________________________\n";
			break;
		case 3:	l.sort_books();
			cout << "\n...................................................................................................................";
			break;
		case 4: int ISBN;
			cout << "\nTo check a specific book is available in library or not Enter ISBN no. of book: " << endl;
			cin >> ISBN;
			if (l.search_book(ISBN) != NULL)
			{
				cout << "\nBOOK PRESENT\n";
			}
			break;
		case 5: exit(0);
		}
	} while (choice != 5);
	return 0;
}

/***************************************************************************************************************************
WELCOME TO LIBRARY
----------------------------------------------
1. Add new book details
2. List all books of specific author
3. Sort books based on ISBN number
4. Search book in the library
5. Exit
______________________________________________
Enter your choice : 1
Enter book name: Java_Reference
Enter author name: Herbert
Enter publication: Blackbook
Enter ISBN number: 1276

----------------------------------------------
New book added to library!
Book name: Java_Reference
Author Name: Herbert
Publication: Blackbook
ISBN Number: 1276
______________________________________________

WELCOME TO LIBRARY
----------------------------------------------
1. Add new book details
2. List all books of specific author
3. Sort books based on ISBN number
4. Search book in the library
5. Exit
______________________________________________
Enter your choice : 1
Enter book name: cpp
Enter author name: Balguruswami
Enter publication: Nirali
Enter ISBN number: 87

----------------------------------------------
New book added to library!
Book name: cpp
Author Name: Balguruswami
Publication: Nirali
ISBN Number: 87
______________________________________________

WELCOME TO LIBRARY
----------------------------------------------
1. Add new book details
2. List all books of specific author
3. Sort books based on ISBN number
4. Search book in the library
5. Exit
______________________________________________
Enter your choice : 2
Enter the author name of book you want: Herbert

...................................................................................................................
ISBN NO.                AUTHOR NAME                     BOOK NAME               PUBLICATION
...................................................................................................................
1276            Herbert                 Java_Reference          Blackbook
______________________________________________

WELCOME TO LIBRARY
----------------------------------------------
1. Add new book details
2. List all books of specific author
3. Sort books based on ISBN number
4. Search book in the library
5. Exit
______________________________________________
Enter your choice : 3

ISBN NO.        AUTHOR NAME             BOOK NAME               PUBLICATION
87              Balguruswami                    cpp                     Nirali
1276            Herbert                 Java_Reference                  Blackbook
...................................................................................................................

WELCOME TO LIBRARY
----------------------------------------------
1. Add new book details
2. List all books of specific author
3. Sort books based on ISBN number
4. Search book in the library
5. Exit
______________________________________________
Enter your choice : 2
Enter the author name of book you want: abcd

...................................................................................................................
ISBN NO.                AUTHOR NAME                     BOOK NAME               PUBLICATION
...................................................................................................................
No such author's book found in the library
______________________________________________

WELCOME TO LIBRARY
----------------------------------------------
1. Add new book details
2. List all books of specific author
3. Sort books based on ISBN number
4. Search book in the library
5. Exit
______________________________________________
Enter your choice : 4

To check a specific book is available in library or not Enter ISBN no. of book:
34343

BOOK NOT PRESENT

WELCOME TO LIBRARY
----------------------------------------------
1. Add new book details
2. List all books of specific author
3. Sort books based on ISBN number
4. Search book in the library
5. Exit
______________________________________________
Enter your choice : 3

ISBN NO.        AUTHOR NAME             BOOK NAME               PUBLICATION
87              Balguruswami                    cpp                     Nirali
1276            Herbert                 Java_Reference                  Blackbook
...................................................................................................................
WELCOME TO LIBRARY
----------------------------------------------
1. Add new book details
2. List all books of specific author
3. Sort books based on ISBN number
4. Search book in the library
5. Exit
______________________________________________
Enter your choice : 5

WELCOME TO LIBRARY
----------------------------------------------
1. Add new book details
2. List all books of specific author
3. Sort books based on ISBN number
4. Search book in the library
5. Exit
______________________________________________
Enter your choice : 4

To check a specific book is available in library or not Enter ISBN no. of book:
43
Library is Empty
...........................................................................................................................
Time Complexity:
accept_details  : O(1)
Find by Author  : O(n)
Linear Search   : O(n)
sort by ISBN    : O(n^2)
Binary Search   : O(n)
***************************************************************************************************************************/