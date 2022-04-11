//program 10 (larger program)
//gas purchase list
//Carter McKinnon COP2220 Fall 2021
//Basic Program that allows users to enter and track gas purchases


#define _CRT_SECURE_NO_WARNINGS //for Visual Studio compiler
#pragma warning(disable:6031) //ignore scanf warnings for Visual Studio compiler
#include<stdio.h>
#include<ctype.h>
#include<string.h>

#define SIZE 150 //size of the list
#define SIZE2 20//size of character arrays

typedef struct {
	// initializing variables
	char gasType[SIZE2];
	char lastName[SIZE2];
	char firstName[SIZE2];	

	int itemNumber;
	int numGallons;

	double totalCost;
	double pricePerGallon;

}gasPurchase;

//function prototypes

//greets the user
void Greeting();

//function that displays the menu options and gets the users selection
void RunMenu(char* selectionPtr);

//function that processes the user's selection
void ProcessSelection(char selection, gasPurchase list[], int* count);

//function that powers the add transaction feature
void AddTransaction(gasPurchase list[], int* count);

//function that sets the gas prices
int SetPrice(gasPurchase list[], int count);

//fucntion that calculates the total price of the purchase
void CalculateTotal(gasPurchase list[], int count);

//function that displays the list of purchases
void PrintList(gasPurchase list[], int count);

//function that prints the e85 purchases
void PrintE85_purchases(gasPurchase list[], int count);

//function that prints the diesel purchases
void PrintDiesel_purchases(gasPurchase list[], int count);


int main()
{
	//greet the user
	Greeting();
	
	//declare the gas purchase list
	gasPurchase list[SIZE];

	//declare and initialize count to 0
	int count = 0;

	//declare a character for the menu choice
	char input;

	//run the menu choices
	RunMenu(&input);
	
	//begin the while or while loop
	while (input != 'q') //test
	{
		//process the selection
		ProcessSelection(input, list, &count);

		//be sure to update the while loop (call run menu function to get the selection)
		 //update
		RunMenu(&input);
	}

	//say goodbye
	printf("\nThank you for using the program! Have a great day!");
	
	return 0;
}


//function definitions

void Greeting()
//Greets the user
{
	printf("Welcome to the gas purchase list program!\n");
	printf("\nWhen you enter a purchase, you will enter the customer last name, first name, the gas type item number (1 through 5), and the number of gallons purchased\n");
	printf("\n--- If you do not enter a valid item number, your entry will not be added to the list ---\n");
	printf("\n--- The total purchase price will be calculated based on the following prices per gallon ---\n");
	printf("\nRegular Gas (87): $3.09");
	printf("\nMid-Grade gas (89): $3.42");
	printf("\nPremium gas (93): $3.73");
	printf("\nDiesel: $3.19");
	printf("\nE85: $3.02");
}

void RunMenu(char* selectionPtr)
//input: the user's selection (input/output parameter)
//display the program options and get the users selection (A, P, S, or Q)
//use an input/output parameter for the selection
{
	printf("\n------------------------------------------------------------------------------------\n");
	printf("What would you like to do?\n");
	printf("Please select from the following options:\n\n");
	printf("'A' Add a gas purchase\n");
	printf("'P' Display the purchase list\n");
	printf("'E' Display the first name, last name, and total cost of any E85 purchases\n");
	printf("'D' Display the first name, last name, and total cost of any Diesel pruchases\n");
	printf("'Q' to quit\n");
	printf("Please enter your selection>>   ");
	scanf(" %c", selectionPtr);

	//changing the selection to lowercase
	*selectionPtr = tolower(*selectionPtr);
}

void ProcessSelection(char selection, gasPurchase list[], int* count)
//input: the user's selection by copy (input parameter)
//input/output: the gasPurchase list and count 
//display a message that the selection has been entered
//call the required function for each selection (A, P, or S)
{
	if (selection == 'a')
	{
		printf("\n----------------------------------\n");
		printf("You selected %c\n", selection);

		//ask and get the first and last name
		printf("\nEnter the customer last name>>  ");
		scanf("%s", list[*count].lastName);
		printf("\nPlease enter the customer's first name>>  ");
		scanf("%s", list[*count].firstName);

		//call the Add Transaction function
		AddTransaction(list, count);

		//keep track of how manyitems are in the list
		printf("\nThere are now %d gas purchases in the list", *count);

	}
	else if (selection == 'p')
	{
		//display purchase list option
		printf("\n----------------------------------\n");
		printf("You selected %c\n", selection);

		//running view purchases function
		PrintList(list, *count);

	} 
	else if (selection == 'e')
	{
		//display e85 purchases
		printf("\n----------------------------------\n");
		printf("You selected %c\n", selection);

		//running view e85 purchases funtion
		PrintE85_purchases(list, *count);
	}
	else if (selection == 'd')
	{
		//display diesel purchases
		printf("\n----------------------------------\n");
		printf("You selected %c\n", selection);

		//running view diesel purchases function
		PrintDiesel_purchases(list, *count);
	}
	else
	{
		printf("\n----------------------------------\n");
		printf("You selected %c\n", selection);
		printf("\nThat is not a valid option\n");

	}
}


void AddTransaction(gasPurchase list[], int* count)
//input/output: the gasPurchase list and count 
//add a gas purchase transaction to the list and 
//add 1 to the "value at" count only if the itemNumber is valid 
{

	int validNumber = 1; // do not know if the user will enter a valid item number

	//display the gas purchase options
	printf("\n--- The total purchase price will be calculated based on the following prices per gallon ---\n");
	printf("\n1. Regular Gas (87): $3.09");
	printf("\n2. Mid-Grade gas (89): $3.42");
	printf("\n3. Premium gas (93): $3.73");
	printf("\n4. Diesel: $3.19");
	printf("\n5. E85: $3.02");

	//ask and get the item number
	printf("\nPlease enter the item number:\n");
	scanf("%d", &list[*count].itemNumber);

	//ask and get the number of gallons
	printf("Please enter the number of gallons>>  ");
	scanf("%d", &list[*count].numGallons);

	//call the set Price function
	validNumber = SetPrice(list, *count);

	if (validNumber == 1)
	{
		//calculate the total (call the function)
		CalculateTotal(list, *count);

		*count = *count + 1;
		printf("\nThe gas purchase transaction has been added to the list\n");

	}
	else// not a valid item number
	{
		printf("\nYou did not enter a valid item number, the gas purchase transaction will not be added to the list\n");
	}

}



int SetPrice(gasPurchase list[], int count)
//input/output: the gasPurchase list
//input count by copy (input parameter)
//checks to see if the itemNumber is valid
//sets the pricePerGallon and gasType
//returns a 1 if the itemNumber is valid and returns 0 if the itemNumber is not valid
{
	int returnValue = 1; // do not know if the user will enter a valid item number

	if (list[count].itemNumber == 1)
	{
		list[count].pricePerGallon = 3.09;
		strcpy(list[count].gasType, "Regular");
	}
	else if (list[count].itemNumber == 2)
	{
		list[count].pricePerGallon = 3.42;
		strcpy(list[count].gasType, "Mid-Grade");
	}
	else if (list[count].itemNumber == 3)
	{
		list[count].pricePerGallon = 3.73;
		strcpy(list[count].gasType, "Premium");
	}
	else if (list[count].itemNumber == 4)
	{
		list[count].pricePerGallon = 3.19;
		strcpy(list[count].gasType, "Diesel");
	}
	else if (list[count].itemNumber == 5) {
		list[count].pricePerGallon = 3.02;
		strcpy(list[count].gasType, "E85");
	}
	else
	{
		printf("\nInvalid Input\n");
		returnValue = 0; //the user did not enter a valid item number
	}
	//return a 1 or a 0
	return returnValue;
}


void CalculateTotal(gasPurchase list[], int count)
//input/output: the gasPurchase list
//input count by copy (input parameter)
//and Calculates the totalCost based on the itemNumber
{
	//calculate the total
	list[count].totalCost = list[count].numGallons * list[count].pricePerGallon;
}


void PrintList(gasPurchase list[], int count)
//input/output: the gasPurchase list
//input count by copy (input parameter)
//prints the contents of the list onto the screen 
{
	int i;
	printf("\n-----------------------------------------------------\n");
	if (count == 0)
	{
		printf("\nNo purchase has been entered.\n");
	}
	//use a loop to print the list
	for (i = 0; i < count; i++)
	{
		printf("\n-----------------------------------------------------\n");
		printf("\nFirst Name: %s", list[i].firstName);
		printf("\nLast Name: %s", list[i].lastName);
		printf("\nGas Type: %s", list[i].gasType);
		printf("\nPrice Per Gallon: $%.2f", list[i].pricePerGallon);
		printf("\nNumber of Gallons Purchased: %d", list[i].numGallons);
		printf("\nTotal Purchase Price: $%.2f", list[i].totalCost);
		
	}
}

void PrintE85_purchases(gasPurchase list[], int count)
//input/output: the gasPurchase list
//input count by copy (input parameter)
//Searches the array and prints the name and 
//totalCost of any E85 purchases(list and count)
{
	int i;
	printf("\n-----------------------------------------------------\n");
	printf("\nE85 purchases, item number 5:\n");
	if (count == 0)
	{
		printf("\nNo purchase has been entered.\n");
	}
	//use a loop to search the list
	for(i = 0; i < count; i++)
	{
		if (list[i].itemNumber == 5)
		{
			//print the customer first and last name and total cost
			printf("\nFirst Name: %s", list[i].firstName);
			printf("\nLast Name: %s", list[i].lastName);
			printf("\nTotal Purchase Price: $%.2f", list[i].totalCost);
		}
	}

}

void PrintDiesel_purchases(gasPurchase list[], int count)
//input/output: the gasPurchase list
//input count by copy (input parameter)
//Searches the array and prints the name and 
//totalCost of any Diesel purchases(list and count)
{
	int i;
	printf("\n-----------------------------------------------------\n");
	printf("\nDiesel purchases, item number 4:\n");
	if (count == 0)
	{
		printf("\nNo purchase has been entered.\n");
	}
	for (i = 0; i < count; i++)
	{
		if (list[i].itemNumber == 4)
		{
			//print the customer first and last name and total cost
			printf("\nFirst Name: %s", list[i].firstName);
			printf("\nLast Name: %s", list[i].lastName);
			printf("\nTotal Purchase Price: $%.2f", list[i].totalCost);
		}
	}

}
