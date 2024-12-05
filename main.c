#include<stdio.h>
#include<string.h>
#include<stdlib.h>

struct book
{
    int bookID;
    char title[50];
    char author[50];
    char year[10];

    struct book* next;

};

struct reader
{
    int readerID;
    char firstName[50];
    char lastName[50];
    char adress[100];
    char pesel[12];
    char email[100];
    char contact[12];

    struct checkOut* checkOutList;
    struct reader* next;

};

struct checkOut
{
    int readerID;
    int checkOutID;
    char title[50];
    char author[50];
    char checkOutDate[12];
    char returnDate[12];
    char expectedReturnDate[12];

    struct checkOut* next;
};

typedef struct reader Reader;
typedef struct book Book;
typedef struct checkOut CheckOut;

Reader* readReaders(char* fileName);
Book* readBooks(char* fileName);
void readCheckOuts(char * fileName, Reader* reader);
void addReader(Reader* reader);
Reader* removeReader(Reader* reader, int readerID);
void editReader(Reader* reader, int readerID);
void addBook(Book* book);
Book* removeBook(Book* book, int selectedCopyID);
void editBook(Book* book, int copyID);
int compare_firstName(const void* obj1, const void* obj2);
int compare_lastName(const void* obj1,const void* obj2);
int compare_pesel(const void* obj1,const void* obj2);
int compare_author(const void* obj1,const void* obj2);
int compare_title(const void* obj1,const void* obj2);
int compare_year(const void* obj1,const void* obj2);
int compare_returnDate(const void* obj1,const void* obj2);
int compare_checkOutDate(const void* obj1,const void* obj2);
int compare_expectedReturnDate(const void* obj1,const void* obj2);
Reader* readerArray(Reader* reader,int* len);//void??
Book* bookArray(Book* book,int* len);
void displayAllReaders(Reader* reader);
void displayReader(Reader* reader,int readerID);
void displaySortedReaders(Reader* arr,int len,int sort);
void findReader(Reader* reader,char *data,int choice,int sort);
void displayAllBooks(Book* book);
void displayBook(Book* book,int bookID);
void displaySortedBooks(Book* arr,int len,int sort);
void findBook(Book* book,char *Dane,int choice,int sort);
void readerAccount(CheckOut* arr,int len,int sort);
void displayReaderAccount(Reader* reader,int readerID,int mode,int sort,char* today);
void checkOutBook(Reader* reader,Book* book,int readerID,int bookID);
void returnBook(Reader* reader,int readerID,int checkOutID);
void saveReaders(char* fileName,Reader* reader);
void saveBooks(char* fileName,Book* book);
void saveCheckOuts(char* fileName,Reader* reader);



int main()
{
    Book* books = readBooks("Books.txt");
    Reader* readers = readReaders("Readers.txt");
    readCheckOuts("CheckOuts.txt", readers);

    printf("*************************");
    printf("WELCOME TO THE LIBRARY MANAGEMENT SYSTEM");
    printf("*************************\n\n");

    char today[12];
    int choice;
    int tmp;
    printf("Enter today's date: YYYY/MM/DD\n");
    scanf("%s",today);
    do
    {
        system("cls");
        printf("1 - Add\n2 - Remove\n3 - Edit\n4 - Display\n5 - Account balance\n6 - Search\n7 - Check out\n8 - Return book\n9 - Save changes\n0 - Exit\n\nEnter your choice:\n");
        scanf("%d",&choice);
        switch(choice)
        {
            case 1:
            {
                system("cls");
                printf("1 - Reader\n2 - Book\n\nEnter your choice: ");
                scanf("%d",&choice);
                if(choice == 1)
                {
                    system("cls");
                    addReader(readers);
                    printf("Added.\n");
                }
                else if(choice == 2)
                {
                    system("cls");
                    addBook(books);
                    printf("Added.\n");
                }else
                {
                    system("cls");
                    printf("Invalid option\n");
                }
                system("pause");
                choice = 1;
                break;
            }
            case 2:
            {
                system("cls");
                printf("1 - Reader\n2 - Book\n\nEnter your choice: ");
                scanf("%d",&choice);
                if(choice == 1)
                {
                    system("cls");
                    printf("Enter reader's ID:\n");
                    scanf("%d",&choice);
                    readers = removeReader(readers,choice);

                }
                else if(choice == 2)
                {
                    system("cls");
                    printf("Enter book ID:\n");
                    scanf("%d",&choice);
                    books = removeBook(books,choice);

                }else
                {
                    system("cls");
                    printf("Invalid option.\n");
                }
                system("pause");
                choice = 2;
                break;
            }
            case 3:
            {
                system("cls");
                printf("1 - Reader\n2 - Book\n\nEnter your choice: ");
                scanf("%d",&choice);
                if(choice == 1)
                {
                    system("cls");
                    printf("Enter reader's ID\n");
                    scanf("%d",&choice);
                    editReader(readers,choice);

                }
                else if(choice == 2)
                {
                    system("cls");
                    printf("Enter book's ID\n");
                    scanf("%d",&choice);
                    editBook(books,choice);

                }else
                {
                    system("cls");
                    printf("Invalid option.\n");
                }
                system("pause");
                choice = 3;
                break;
            }
            case 4:
            {
                system("cls");
                printf("1 - Reader\n2 - Book\n3 - All readers\n4 - All books\n\nEnter your choice: ");
                scanf("%d",&choice);
                if(choice == 1)
                {
                    system("cls");
                    printf("Enter readers ID:\n");
                    scanf("%d",&choice);
                    displayReader(readers,choice);

                }
                else if(choice == 2)
                {
                    system("cls");
                    printf("Enter book's ID:\n");
                    scanf("%d",&choice);
                    displayBook(books,choice);

                }
                else if(choice == 3)
                {
                    system("cls");
                    printf("Sorted by:\n1 - First names\n2 - last Name\n3 - personal identity number\n0 - Default(ID)\n\nEnter your choice: ");
                    scanf("%d",&choice);
                    if(choice != 0)
                    {
                        system("cls");
                        int len=0;
                        Reader* array = readerArray(readers,&len);
                        displaySortedReaders(array,len,choice);
                        free(array);
                    }
                    else
                    {
                        system("cls");
                        displayAllReaders(readers);
                    }

                }
                else if(choice == 4)
                {
                    system("cls");
                    printf("Sorted by:\n1 - Author\n2 - Title\n3 - Year\n0 - Default(ID)\n\nEnter your choice: ");
                    scanf("%d",&choice);
                    if(choice != 0)
                    {
                        system("cls");
                        int len=0;
                        Book* array = bookArray(books,&len);
                        displaySortedBooks(array,len,choice);
                        free(array);
                    }
                    else
                    {
                        system("cls");
                        displayAllBooks(books);
                    }
                }
                else
                {
                    system("cls");
                    printf("Invalid option.\n");
                }
                system("pause");
                choice = 4;
                break;
            }
            case 5:
                {
                    int sort;
                    system("cls");
                    printf("Enter reader's ID\n");
                    scanf("%d",&tmp);
                    system("cls");
                    printf("1 - Full history list\n2 - Currently borrowed\n3 - Books after expected return date(outdated)\n\nEnter your choice: ");
                    scanf("%d",&choice);
                    system("cls");
                    printf("Sorted by:\n1 - Check out date\n2 - Return date\n3 - Expected return date\n0 - Default\n");
                    scanf("%d",&sort);
                    system("cls");
                    if((choice>=1&&choice<=3) && (sort>=0&&sort<=3))
                    {
                        displayReaderAccount(readers,tmp,choice,sort,today);
                    }
                    else
                    {
                        printf("At least one invalid option was chosen.\n");
                    }
                    system("pause");
                    choice = 5;
                    break;
                }
            case 6:
                {
                    system("cls");
                    char napis[101];
                    printf("1 - Readers\n2 - Books\n\nEnter your choice: ");
                    scanf("%d",&choice);
                    system("cls");
                    if(choice == 1)
                    {
                        printf("Search by:\n1 - First name\n2 - Last Name\n3 - Personal identity number\n\nEnter your choice: ");
                        scanf("%d",&choice);
                        system("cls");
                        printf("Sorted by\n1 - First name\n2 - Last Name\n3 - Personal identity number\n0 - Default\n\nEnter your choice: ");
                        scanf("%d",&tmp);
                        system("cls");
                        printf("Enter phrase to find it(case sensitive): Max. 100 characters\n");

                        scanf("%s",napis);
                        system("cls");
                        if((choice>=1&&choice<=3) && (tmp>=0&&tmp<=3))
                        {
                        findReader(readers,napis,choice,tmp);
                        }
                        else
                        {
                            printf("At least one invalid option was chosen.\n");
                        }
                    }
                    else if(choice == 2)
                    {
                        printf("Search by:\n1 - Title\n2 - Author\n3 - Year\n\nEnter your choice: ");
                        scanf("%d",&choice);
                        system("cls");
                        printf("Sorted by:\n1 - Author\n2 - Title\n3 - Year\n0 - Default\n\nEnter your choice: ");
                        scanf("%d",&tmp);
                        system("cls");
                        printf("Enter phrase to find it(case sensitive): Max. 100 characters\n");
                        scanf("%s",napis);
                        system("cls");
                        if((choice>=1&&choice<=3) && (tmp>=0&&tmp<=3))
                        {
                            findBook(books,napis,choice,tmp);
                        }
                        else
                        {
                            printf("At least one invalid option was chosen.\n");
                        }

                    }
                    system("pause");
                    choice = 6;
                    break;
                }
            case 7:
                {
                    system("cls");
                    printf("Enter reader's ID:\n");
                    scanf("%d",&choice);
                    system("cls");
                    printf("Enter book ID:\n");
                    scanf("%d",&tmp);
                    system("cls");
                    checkOutBook(readers,books,choice,tmp);
                    system("pause");
                    choice = 7;
                    break;
                }
            case 8:
                {
                    system("cls");
                    printf("Enter reader's ID:\n");
                    scanf("%d",&choice);
                    system("cls");
                    printf("Enter check out ID:\n");
                    scanf("%d",&tmp);
                    system("cls");
                    returnBook(readers,choice,tmp);
                    system("pause");
                    choice = 8;
                    break;
                }
            case 9:
                {
                    saveReaders("Readers.txt",readers);
                    saveBooks("Books.txt",books);
                    saveCheckOuts("CheckOuts.txt",readers);
                    system("cls");
                    printf("Changes saved.\n");
                    system("pause");
                    choice = 9;
                    break;
                }
            case 0:
                {

                    break;
                }
            default:
                {
                    system("cls");
                    printf("Invalid option.\n");
                    system("pause");
                    break;
                }
        }
    }while(choice!=0);

    return 0;
}



Reader* readReaders(char* fileName)
{
    FILE* file;
    file = fopen(fileName, "r");

    Reader* root = (Reader*)malloc(sizeof(Reader));
    Reader* tmp = root;
    fseek(file, 0, SEEK_END);
    long end = ftell(file);
    fseek(file, 0, SEEK_SET);
    while(!feof(file))
    {
        fscanf(file, "%d %s %s %s %s %s %s",&tmp->readerID, tmp->firstName, tmp->lastName, tmp->adress, tmp->pesel, tmp->email, tmp->contact);
        tmp->checkOutList = NULL;
        if( end != ftell(file))
        {
            tmp->next = (Reader*)malloc(sizeof(Reader));
            tmp = tmp->next;
        }
    }

    fclose(file);
    return root;

}

Book* readBooks(char* fileName)
{
    FILE* file;
    file=fopen(fileName,"r");

    Book* root = (Book*)malloc(sizeof(Book));
    Book* tmp=root;
    fseek(file,0,SEEK_END);
    long end = ftell(file);
    fseek(file,0,SEEK_SET);
    while(!feof(file))
    {
        fscanf(file,"%d %s %s %s",&tmp->bookID,tmp->title,tmp->author,tmp->year);
        if(ftell(file) !=end)
        {
            tmp->next=(Book*)malloc(sizeof(Book));
            tmp=tmp->next;
        }
        else
        {
            tmp->next=NULL;
        }
    }
    fclose(file);
    return root;
}


void readCheckOuts(char *fileName,Reader* reader)
{
    FILE *file;
    file=fopen(fileName,"r");
    CheckOut *root = (CheckOut*)malloc(sizeof(CheckOut));
    CheckOut *tmp = root;
    Reader* tmpr = reader;
    CheckOut* tmprc = NULL;
    fseek(file,0,SEEK_END);
    long end = ftell(file);
    fseek(file,0,SEEK_SET);

    while(!feof(file))
    {
        fscanf(file,"%s %s %s %d %s %s %d",tmp->checkOutDate,tmp->returnDate,tmp->expectedReturnDate, &tmp->readerID,tmp->author,tmp->title,&tmp->checkOutID);
        if(end != ftell(file))
        {
             tmp->next=(CheckOut*)malloc(sizeof(CheckOut));
             tmp=tmp->next;
        }
        else
        {
            tmp->next=NULL;
        }
    }
    tmp=root;
    while(tmp != NULL)
    {
        while(tmpr !=NULL)
        {
            if(tmp->readerID == tmpr->readerID)
            {
                break;
            }
            tmpr=tmpr->next;
        }
        tmprc=tmpr->checkOutList;
        if(tmprc != NULL)
        {
            while(tmprc->next !=NULL)
            {
                tmprc = tmprc->next;
            }
            tmprc->next =tmp;
            tmprc=tmprc->next;
        }
        else
        {
            tmpr->checkOutList=tmp;
            tmprc = tmpr->checkOutList;
        }
        tmp = tmp->next;
        tmprc->next=NULL;
        tmpr = reader;
    }
    fclose(file);
    return;
}


void addReader(Reader* reader)
{
    Reader* tmp = reader;
    char data[100];
    int giveID;

    while(tmp->next != NULL)
    {
        tmp = tmp->next;
    }
    tmp->next = (Reader*)malloc(sizeof(Reader));
    giveID = tmp->readerID;
    tmp = tmp->next;
      tmp->readerID = giveID + 1;
    printf("Reader's fist name(max 50 characters):\n");
    scanf("%s", data);
    strcpy(tmp->firstName, data);
    printf("Reader's last name(max 50 characters):\n");
    scanf("%s", data);
    strcpy(tmp->lastName, data);
    printf("Reader's personal identity number(max 12 characters):\n");
    scanf("%s", data);
    strcpy(tmp->pesel, data);
    printf("Reader's adress(max 100 characters):\n");
    scanf("%s", data);
    strcpy(tmp->adress, data);
    printf("Reader's email(max 100 characters):\n");
    scanf("%s", data);
    strcpy(tmp->email, data);
    printf("Reader's contact number(max 12 characters):\n");
    scanf("%s", data);
    strcpy(tmp->contact, data);
    tmp->next=NULL;
}

Reader* removeReader(Reader* reader, int readerID)
{
    Reader* tmp = reader;
    Reader* tmp2 = reader;

    if (readerID == 1)
    {
        free(tmp);
        reader = reader->next;
        return reader;
    }

    while(tmp->next->readerID != readerID)
    {
        tmp = tmp->next;
        if(tmp->next == NULL)
        {
            printf("Reader not found");
        }
    }
    tmp2 = tmp->next;
    tmp->next = tmp2->next;
    free(tmp2);


    return reader;
}

void editReader(Reader* reader, int readerID)
{
    Reader* tmp = reader;
    char data[100];
    while(readerID != tmp->readerID)
    {
        tmp = tmp->next;
        if(tmp->next == NULL)
        {
             printf("Reader not found!");
        }
    }
    printf("Enter 'skip' if you want skip this one \n");
    printf("Reader's first name: ");
    scanf("%s", data);
    if(strcpy(data, "skip") !=0)
    {
        strcpy(tmp->firstName, data);
    }
    else
    {
        printf("Edit not done\n");
    }
    printf("Enter 'skip' if you want skip this one \n");
    printf("Reader's last name: ");
    scanf("%s", data);
    if(strcpy(data, "skip") !=0)
    {
        strcpy(tmp->lastName, data);
    }
    else
    {
        printf("Edit not done\n");
    }
    printf("Enter 'skip' if you want skip this one \n");
    printf("Reader's personal identity number: ");
    scanf("%s", data);
    if(strcpy(data, "skip") !=0)
    {
        strcpy(tmp->pesel, data);
    }
    else
    {
        printf("Edit not done\n");
    }
    printf("Enter 'skip' if you want skip this one \n");
    printf("Reader's adress: ");
    scanf("%s", data);
    if(strcpy(data, "skip") !=0)
    {
        strcpy(tmp->adress, data);
    }
    else
    {
        printf("No edits done\n");
    }
    printf("Enter 'skip' if you want skip this one \n");
    printf("Reader's email: ");
    scanf("%s", data);
    if(strcpy(data, "skip") !=0)
    {
        strcpy(tmp->email, data);
    }
    else
    {
        printf("No edits done\n");
    }
     printf("Enter 'skip' if you want skip this one \n");
    printf("Reader's contact number: ");
    scanf("%s", data);
    if(strcpy(data, "skip") !=0)
    {
        strcpy(tmp->contact, data);
    }
    else
    {
        printf("No edits done\n");
    }
}




void addBook(Book* book)
{
    Book* tmp = book;
    char data[100];
    int giveID;
    while(tmp->next != NULL)
    {
        tmp = tmp->next;
    }
    tmp->next = (Book*)malloc(sizeof(Book));
    giveID = tmp->bookID;
    tmp = tmp->next;
    tmp->bookID = giveID +1;
    printf("Book's title(max 50 characters):\n");
    scanf("%s", data);
    strcpy(tmp->title, data);
    printf("Book's author(max 50 characters):\n");
    scanf("%s", data);
    strcpy(tmp->author, data);
    printf("Book's year(max 10 characters):\n");
    scanf("%s", data);
    strcpy(tmp->year, data);
    tmp->next = NULL;
}

Book* removeBook(Book* book, int selectedCopyID)
{
    Book* tmp = book;
    Book* tmp2 = book;

    if(selectedCopyID == 1)
    {
        free(tmp);
        book = book ->next;
    }

    while(tmp->next->bookID != selectedCopyID)
    {
        tmp = tmp->next;
        if(tmp == NULL)
        {
            printf("Book not found");
            return book;
        }
    }

    tmp2 = tmp->next;
    tmp->next = tmp2->next;
    free(tmp2);

    return book;
}

void editBook(Book* book, int copyID)
{
    Book* tmp = book;
    char data[100];
    while(tmp->bookID != copyID)
    {
        tmp = tmp->next;
        if(tmp == NULL)
        {
            printf("Book not found");
            return;
        }
    }
    printf("Enter 'skip' if you want skip this one \n");
    printf("Book's title: ");
    scanf("%s", data);
    if(strcpy(data, "skip") !=0)
    {
        strcpy(tmp->title, data);
    }
    else
    {
        printf("Edit not done\n");
    }
    printf("Enter 'skip' if you want skip this one \n");
    printf("Book's author: ");
    scanf("%s", data);
    if(strcpy(data, "skip") !=0)
    {
        strcpy(tmp->author, data);
    }
    else
    {
        printf("Edit not done\n");
    }
    printf("Enter 'skip' if you want skip this one \n");
    printf("Book's year: ");
    scanf("%s", data);
    if(strcpy(data, "skip") !=0)
    {
        strcpy(tmp->year, data);
    }
    else
    {
        printf("Edit not done\n");
    }
}

int compare_firstName(const void* obj1, const void* obj2)
{
    Reader* reader1 = (Reader*)obj1;
    Reader* reader2 = (Reader*)obj2;
    int result = strcmp(reader1->firstName,reader2->firstName);
    return result;
}

int compare_lastName(const void* obj1,const void* obj2)
{
    Reader* reader1 = (Reader*)obj1;
    Reader* reader2 = (Reader*)obj2;
    int result = strcmp(reader1->lastName,reader2->lastName);
    return result;
}

int compare_pesel(const void* obj1,const void* obj2)
{
    Reader* reader1 = (Reader*)obj1;
    Reader* reader2 = (Reader*)obj2;
    int result = strcmp(reader1->pesel,reader2->pesel);
    return result;
}

int compare_author(const void* obj1,const void* obj2)
{
    Book* book1 = (Book*)obj1;
    Book* book2 = (Book*)obj2;
    int result = strcmp(book1->author,book2->author);
    return result;
}

int compare_title(const void* obj1,const void* obj2)
{
    Book* book1 = (Book*)obj1;
    Book* book2 = (Book*)obj2;
    int result = strcmp(book1->title,book2->title);
    return result;
}

int compare_year(const void* obj1,const void* obj2)
{
    Book* book1 = (Book*)obj1;
    Book* book2 = (Book*)obj2;
    int result = strcmp(book1->year,book2->year);
    return result;
}

int compare_returnDate(const void* obj1,const void* obj2)
{
    CheckOut* checkOut1 = (CheckOut*)obj1;
    CheckOut* checkOut2 = (CheckOut*)obj2;
    int result = strcmp(checkOut1->returnDate,checkOut2->returnDate);
    return result;
}

int compare_checkOutDate(const void* obj1,const void* obj2)
{
    CheckOut* checkOut1 = (CheckOut*)obj1;
    CheckOut* checkOut2 = (CheckOut*)obj2;
    int result = strcmp(checkOut1->checkOutDate,checkOut2->checkOutDate);
    return result;
}

int compare_expectedReturnDate(const void* obj1,const void* obj2)
{
    CheckOut* checkOut1 = (CheckOut*)obj1;
    CheckOut* checkOut2 = (CheckOut*)obj2;
    int result = strcmp(checkOut1->expectedReturnDate,checkOut2->expectedReturnDate);
    return result;
}

Reader* readerArray(Reader* reader,int* len)
{
    Reader* tmp = reader;
    int i;
    while(tmp != NULL)
    {
        (*len)++;
        tmp=tmp->next;
    }
    tmp=reader;
    Reader* arr = (Reader*) malloc(sizeof(Reader)*(*len));
    for(i=0;i<(*len);i++)
    {
        arr[i] = *tmp;
        tmp = tmp->next;
    }
    return arr;
}

Book* bookArray(Book* book,int* len)
{
    Book* tmp = book;
    int i;
    while(tmp != NULL)
    {
        (*len)++;
        tmp=tmp->next;
    }
    tmp=book;
    Book* arr = (Book*) malloc(sizeof(Book)*(*len));
    for(i=0;i<(*len);i++)
    {
        arr[i] = *tmp;
        tmp = tmp->next;
    }
    return arr;
}

void displayAllReaders(Reader* reader)
{
    Reader* tmp = reader;
    while(tmp != NULL)
    {
        printf("ID: %d\nFirst name: %s\nLast Name: %s\nAdress: %s\nPersonal identity number: %s\nEmail: %s\nContact: %s\n",tmp->readerID,tmp->firstName,tmp->lastName,tmp->adress,tmp->pesel,tmp->email,tmp->contact);
        tmp = tmp->next;
    }
}
void displayReader(Reader* reader,int readerID)
{
    Reader* tmp = reader;
    while(tmp->readerID != readerID)
    {
        tmp = tmp->next;
        if(tmp == NULL)
        {
            printf("Reader not found.\n");
            return;
        }
    }
    if(tmp==NULL)
    {
        printf("Readers database is empty.\n");
    }
    printf("ID: %d\nFirst name: %s\nLast name: %s\nAdress: %s\nPersonal identity number: %s\nemail: %s\nContact: %s\n",tmp->readerID,tmp->firstName,tmp->lastName,tmp->adress,tmp->pesel,tmp->email,tmp->contact);
}

void displaySortedReaders(Reader* arr,int len,int sort)
{
    int i;
    switch(sort)
    {
    case 1:
        {
            qsort(arr,len,sizeof(Reader),compare_firstName);
            break;
        }
    case 2:
        {
            qsort(arr,len,sizeof(Reader),compare_lastName);
            break;
        }
    case 3:
        {
            qsort(arr,len,sizeof(Reader),compare_pesel);
            break;
        }
    case 0:
        {
            break;
        }
    default:
        {
            printf("Sort option invalid\n Readers displayed by default.\n");
            break;
        }
    }
    for(i=0;i<len;i++)
    {
        printf("ID: %d\nFirst name: %s\nLast name: %s\nAdress: %s\nPersonal identity number: %s\nemail: %s\nContact: %s\n",arr[i].readerID,arr[i].firstName,arr[i].lastName,arr[i].adress,arr[i].pesel,arr[i].email,arr[i].contact);
    }
}


void findReader(Reader* reader,char *data,int choice,int sort)
{
    Reader* tmp = reader;
    int len=0;
    int len_c=0;
    while(tmp != NULL)
    {
        len++;
        tmp=tmp->next;
    }
    Reader* arr = (Reader*) malloc(sizeof(Reader)*len);
    tmp=reader;
    switch(choice)
    {
    case 1:
        {
            while(tmp != NULL)
            {
                if(strcmp(tmp->firstName,data)==0)
                {
                    arr[len_c] = *tmp;
                    len_c++;
                    //printf("ID:%d\nFirst name:%s\nLast name:%s\nAdres:%s\nPersonal identity number:%s\nemail:%s\nTelefon%s\n",tmp->id_czyt,tmp->imie,tmp->nazwisko,tmp->adres,tmp->pesel,tmp->email,tmp->telefon);
                }
                tmp = tmp->next;
            }
            break;
        }
    case 2:
        {
            while(tmp != NULL)
            {
                if(strcmp(tmp->lastName,data)==0)
                {
                    arr[len_c] = *tmp;
                    len_c++;
                   // printf("ID:%d\nFirst name:%s\nLast name:%s\nAdress:%s\nPersonal identity number:%s\nemail:%s\nTelefon%s\n",tmp->id_czyt,tmp->imie,tmp->nazwisko,tmp->adres,tmp->pesel,tmp->email,tmp->telefon);
                }
                tmp = tmp->next;
            }
            break;
        }
    case 3:
        {
            while(tmp != NULL)
            {
                if(strcmp(tmp->pesel,data)==0)
                {
                    arr[len_c] = *tmp;
                    len_c++;
                    //printf("ID:%d\nFirst name:%s\nLast name:%s\nAdress:%s\nPersonal identity number:%s\nemail:%s\nTelefon%s\n",tmp->id_czyt,tmp->imie,tmp->nazwisko,tmp->adres,tmp->pesel,tmp->email,tmp->telefon);
                }
                tmp = tmp->next;
            }
            break;
        }
    default:
        {
            printf("Invalid Option.\n");
            return;
        }
    }
    displaySortedReaders(arr,len_c,sort);
}

void displayAllBooks(Book* book)
{
    Book* tmp = book;
    while(tmp != NULL)
    {
        printf("ID:%d\nTitle:%s\nAuthor:%s\nYear:%s\n",tmp->bookID,tmp->title,tmp->author,tmp->year);
        tmp = tmp->next;
    }
}
void displayBook(Book* book,int bookID)
{
    Book* tmp = book;
    while(tmp->bookID != bookID)
    {
        tmp = tmp->next;
        if(tmp == NULL)
        {
            printf("Book not found\n");
            return;
        }
    }
    printf("ID:%d\nTitle:%s\nAuthor:%s\nYear:%s\n",tmp->bookID,tmp->title,tmp->author,tmp->year);
}



void displaySortedBooks(Book* arr,int len,int sort)
{
    int i=0;
    switch(sort)
    {
    case 1:
        {
            qsort(arr,len,sizeof(Book),compare_author);
            break;
        }
    case 2:
        {
            qsort(arr,len,sizeof(Book),compare_title);
            break;
        }
    case 3:
        {
            qsort(arr,len,sizeof(Book),compare_year);
            break;
        }
    case 0:
        {
            break;
        }
    default:
        {
            printf("Sort option invalid\n Books displayed by default.");
            break;
        }
    }
    for(i=0;i<len;i++)
    {
        printf("ID:%d\nTitle:%s\nAuthor:%s\nYear:%s\n",arr[i].bookID,arr[i].title,arr[i].author,arr[i].year);
    }
}

void findBook(Book* book,char *Dane,int choice,int sort)
{
    Book* tmp = book;
    int len=0;
    int len_c=0;
    while(tmp != NULL)
    {
        len++;
        tmp=tmp->next;
    }
    Book* arr = (Book*) malloc(sizeof(Book)*len);
    tmp=book;
    switch(choice)
    {
    case 1:
        {
            while(tmp != NULL)
            {
                if(strcmp(tmp->title,Dane)==0)
                {
                    arr[len_c] = *tmp;
                    len_c++;
                }
                tmp = tmp->next;
            }
            break;
        }
    case 2:
        {
            while(tmp != NULL)
            {
                if(strcmp(tmp->author,Dane)==0)
                {
                    arr[len_c] = *tmp;
                    len_c++;
                }
                tmp = tmp->next;
            }
            break;
        }
    case 3:
        {
            while(tmp != NULL)
            {
                if(strcmp(tmp->year,Dane)==0)
                {
                    arr[len_c] = *tmp;
                    len_c++;
                }
                tmp = tmp->next;
            }
            break;
        }
    case 4:
        {
            while(tmp != NULL)
            {
                if(strncmp(tmp->year,Dane,4)==0)
                {
                    arr[len_c] = *tmp;
                    len_c++;
                }
                tmp = tmp->next;
            }
            break;
        }
    default:
        {
            printf("Invalid Option.\n");
            return;
        }
    }
    displaySortedBooks(arr,len_c,sort);
}

void readerAccount(CheckOut* arr,int len,int sort)
{
    int i;
    if(len<=0)
    {
        printf("No check outs\n");
        return;
    }
    switch(sort)
    {
    case 1:
        {
            qsort(arr,len,sizeof(CheckOut),compare_checkOutDate);
            break;
        }
    case 2:
        {
            qsort(arr,len,sizeof(CheckOut),compare_returnDate);
            break;
        }
    case 3:
        {
            qsort(arr,len,sizeof(CheckOut),compare_expectedReturnDate);
            break;
        }
    case 0:
        {
            break;
        }
    default:
        {
            printf("Sort option invalid\n Checkouts displayed by default.");
            break;
        }
    }
    for(i=0;i<len;i++)
    {
        printf("Checkout ID: %d\nAuthor: %s \nTitle: %s \nDCheckout date: %s \nReturn date: %s \nExpected return Date: %s\n",arr[i].checkOutID,arr[i].author,arr[i].title,arr[i].checkOutDate,arr[i].returnDate,arr[i].expectedReturnDate);
    }
    free(arr);
    return;
}

void displayReaderAccount(Reader* reader,int readerID,int mode,int sort,char* today)
{
    Reader* tmp = reader;
    CheckOut* arr;
    while(readerID != tmp->readerID)
    {
        tmp = tmp->next;
        if(tmp == NULL)
        {
            printf("Nie znaleziono czytlenika\n");
            return;
        }
    }
    CheckOut* checkOut = tmp->checkOutList;
    int len=0;
    int len_c=0;
    while(checkOut != NULL)
    {
        len++;
        checkOut = checkOut->next;
    }
    if(len != 0)
    {
        arr = (CheckOut*) malloc(sizeof(CheckOut)*len);
    }
    checkOut = tmp->checkOutList;
    switch(mode)
    {
    case 2:// Current
        {
            while(checkOut != NULL)
            {
                if(strcmp(checkOut->returnDate,"0000/00/00")==0)
                {
                    arr[len_c] = *checkOut;
                    len_c++;
                }
                checkOut = checkOut->next;
            }

            break;
        }
    case 1:// History
        {
            while(checkOut != NULL)
            {
                arr[len_c] = *checkOut;
                len_c++;
                checkOut = checkOut->next;
            }

            break;
        }
    case 3:// Outdated
        {
            while(checkOut != NULL)
            {
                if(strcmp(checkOut->returnDate,"0000/00/00")==0 && strcmp(checkOut->expectedReturnDate,today)<0)
                {
                    arr[len_c] = *checkOut;
                    len_c++;
                }
                checkOut = checkOut->next;
            }

            break;
        }
    }
    readerAccount(arr,len_c,sort);
}


void checkOutBook(Reader* reader,Book* book,int readerID,int bookID)
{
    Reader* tmpr = reader;
    Book* tmpb = book;
    CheckOut* tmpc;
    int id;
    while(readerID != tmpr->readerID)
    {
        tmpr= tmpr->next;
        if(tmpr == NULL)
        {
            printf("Reader not found\n");
            return;
        }
    }
    tmpc = tmpr->checkOutList;
    while(bookID != tmpb->bookID)
    {
        tmpb = tmpb->next;
        if(tmpb == NULL)
        {
            printf("Book not found\n");
            return;
        }
    }
    if(tmpc != NULL)
    {
        while(tmpc->next != NULL)
        {
            tmpc = tmpc->next;
        }
        tmpc->next = (CheckOut*)malloc(sizeof(CheckOut));
        id = tmpc->checkOutID+1;
        tmpc = tmpc->next;
    }
    else
    {
        tmpc = (CheckOut*)malloc(sizeof(CheckOut));
        id = 1;
        tmpr->checkOutList = tmpc;
    }
    tmpc->next = NULL;
    printf("Enter check out date: YYYY/MM/DD\n");
    scanf("%s",tmpc->checkOutDate);
    printf("Enter expected return date : YYYY/MM/DD\n");
    scanf("%s",tmpc->expectedReturnDate);
    tmpc->readerID = tmpc->readerID;
    tmpc->checkOutID = id;
    strcpy(tmpc->returnDate,"0000/00/00");
    strcpy(tmpc->author,tmpb->author);
    strcpy(tmpc->title,tmpb->title);
}

void returnBook(Reader* reader,int readerID,int checkOutID)
{
    Reader* tmpr = reader;
    CheckOut* tmpc = NULL;
    while(tmpc->readerID != readerID)
    {
        tmpc= tmpc->next;
        if(tmpc == NULL)
        {
            printf("Reader not found\n");
            return;
        }
    }
    tmpc = tmpr->checkOutList;
    if(tmpr == NULL)
    {
        printf("No check outs.\n");
        return;
    }
    while(tmpc->checkOutID != checkOutID)
    {
        tmpr = tmpr->next;
        if(tmpr == NULL)
        {
            printf("Entered ID does not exist.\n");
            return;
        }
    }

    printf("Enter return date: YYYY/MM/DD\n");
    scanf("%s",tmpc->returnDate);
}

void saveReaders(char* fileName,Reader* reader)
{
    FILE *file;
    file = fopen(fileName,"w");
    Reader* tmp= reader;
    while(tmp != NULL)
    {
        fprintf(file,"%d\n%s\n%s\n%s\n%s\n%s\n%s",tmp->readerID,tmp->firstName,tmp->lastName,tmp->adress,tmp->pesel,tmp->email,tmp->contact);
        if(tmp->next != NULL)
        {
            fprintf(file,"\n");
        }
        tmp = tmp->next;
    }
    fclose(file);
}

void saveBooks(char* fileName,Book* book)
{
    FILE *file;
    file = fopen(fileName,"w");
    Book* tmp = book;
    while(tmp != NULL)
    {
        fprintf(file,"%d\n%s\n%s\n%s",tmp->bookID,tmp->title,tmp->author,tmp->year);
        if(tmp->next != NULL)
        {
            fprintf(file,"\n");
        }
        tmp=tmp->next;
    }
    fclose(file);
}

void saveCheckOuts(char* fileName,Reader* reader)
{
    FILE *file;
    file = fopen(fileName,"w");
    Reader* tmpr = reader;
    CheckOut* tmpc = reader->checkOutList;
    while(tmpr != NULL)
    {
        if(tmpr->next !=  NULL && tmpr!= reader && tmpc != NULL)
        {
            fprintf(file,"\n");
        }
        while(tmpc != NULL)
        {
            fprintf(file,"%s\n%s\n%s\n%d\n%s\n%s\n%d",tmpc->checkOutDate,tmpc->returnDate,tmpc->expectedReturnDate,tmpc->readerID,tmpc->author,tmpc->title,tmpc->checkOutID);

            if(tmpc->next != NULL)
            {
                fprintf(file,"\n");
            }
            tmpc = tmpc->next;
        }
        tmpr = tmpr->next;
        if(tmpr != NULL)
        {
        tmpc = tmpr->checkOutList;
        }
    }
    fclose(file);
}

