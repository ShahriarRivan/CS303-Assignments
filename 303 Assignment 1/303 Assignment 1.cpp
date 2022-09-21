
#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>

using namespace std;



class C1      //----------------------------- This is the class called "C1" which will contain all the modefying operations
{
private:
	int Arr[100];  //------------------------ Initializing assigning an array with a max capacity of 100 elements just for this program
	int DataSize;  //------------------------ Initializing DataSize variable to hold the value for the number of data the file has
	string fName{ "NewFile.txt" };  //------- File name is assigned to a string variable which will be used in the following codes
public:
	C1()   //-------------------------------- Constructor will always check and update the number of data in the file everytime the class
	{      //                                 - is called as the number of data will change throughout the program
		ifstream MyFile;
		MyFile.open(fName); 
		int temp, count = 0;

		while (MyFile >> temp)  //----------- loop to get a data count separate from the function which inputs the data in an array
		{
			count++;
		}

		DataSize = count;  //---------------- DataSize is the number of integers in the file

		MyFile.close();
	}

	//==================================================================================================================


	int InsertDataInArray()    //----------- This function assigns the data from the file to each array index
	{
		ifstream MyFile;
		int num[100], count = 0, temp;

		MyFile.open(fName);

		if (!MyFile.is_open())   //--------- Checking whether the was opened successfully or not and prints an error if unsuccessful
		{
			cout << "Opening the file was not successful" << endl;
			return EXIT_FAILURE;
		}

		while (MyFile >> temp)  //---------- While loop to insert the data from the file to the array "Arr[]"
		{
			Arr[count] = temp;
			count++;
		}

		MyFile.close();
		return EXIT_SUCCESS;
	}
	
	//==================================================================================================================

	int find(int num)      //--------------- Function to find a number in the array by matching each array index with the desired number
	{
		for (int i = 0; i < DataSize; i++)
		{
			if (Arr[i] == num)
			{
				return i;    //------------- When found it returns the index at which the match was found
			}
			
		}
		return -10;  //--------------------- Returns a negative because the index will never be negative so negative number will only mean 
	}                //                      one thing that will later be "interpreted as no match found"

	//==================================================================================================================

	int modify(int index, int newNum)   //-- This function replaces an integer of an user selected index with the desired new integer
	{
		int temp;
		temp = Arr[index];
		Arr[index] = newNum;
		return temp;                    //-- Returns 'temp' to show the user what the previous number was 
	}

	//==================================================================================================================


	void AddData(int newNum)       //------- Adds a new number at the end of the array
	{
		Arr[DataSize] = newNum;    //------- It takes the index as 'DataSize' because ,unlike index which starts from 0,
	}                              //        datasize is the max size which is basically 'max-index+1'. So it adds a new position at the end.

	//==================================================================================================================


	void removeData(int index)     //------- This  function removes the number in the desired index and all the data shifts left to fill up the empty gap
	{
		int temp;
		for (int i = index; i < DataSize; i++)
		{
			if (i == DataSize - 1)
			{
				Arr[i] = NULL;
				DataSize -= 1;
			}
			else
			{
				Arr[i] = Arr[i + 1];
			}
		}
	}

	//==================================================================================================================


	void Print(int start, int end)   //------ This function prints all the elements of the array to the screen
	{
		for (int i = start; i <= DataSize-end; i++)
		{
			cout << Arr[i]<< endl;
		}
		
	}

};


//============================================================================================================================================================



void SelectOptions(int option)   //------------------ This function (separate from the class) calls the class to direct the tasks to be done based on the options selected from the main fucntion
{
	C1 MyObject;                    // Creating an onject of the class C1
	int input;
	MyObject.InsertDataInArray();   // Calls a method of the class which inputs all the data from the file to the array
	
	if (option == 1)   // Option 1 was chosen from the main menu this will run
	{
		cout << "\nEnter the integer you want to locate: ";  // Prompts the user to enter the number they want to search and assigns it to a variable on the next line
		cin >> input;
		if (MyObject.find(input) == -10)  //based on the return number from the method of "C1" it can determine if a match was found or not. in this case -10 means no match found
		{
			cout << "The integer you are looking for was not found" << endl;  // prints no match found message 
		}
		else  // if the return isn anything other than -10 that means a match was found and  it prints the matched index on the mext line
		{
			cout << "The integer '" << input << "' was found in index " << MyObject.find(input) << endl;
		}
		
	}
	if (option == 2)     // Option 2 was chosen from the main menu this will run
	{
		int index;  // the user is prompted to enter the index they want to modefy and the new number they want to change it to in the next few lines
		cout << "Please enter the index you wish to modefy: ";
		cin >> index;
		cout << "\nPlease enter the new integer : ";
		cin >> input;
		cout << "The index " << index << " was modefied\nWhich previously had the integer: " << MyObject.modify(index, input) << "\nNow it has been changed to: "<<input << endl;
		//  in the line above the modefied index, the old number the index contained and the new number is printed to tyeh screen
	}
	if (option == 3)     // Option 3 was chosen from the main menu this will run
	{
		cout << "Enter the integer you wish to add at the end of the array: "; // user is prompted to enter a number they wish to add to the array
		cin >> input;
		MyObject.AddData(input);
		cout << "The new array is:" << endl; 
		MyObject.Print(0, 0);     // the new updated array is printed to the screen
	}
	if (option == 4)     // Option 4 was chosen from the main menu this will run
	{
		cout << "Enter the index you wish to remove: ";  // the user is prompted to enter the index they wish to delete 
		cin >> input;
		MyObject.removeData(input);
		MyObject.Print(0, 1);   // the new updated array is printed to the screen
	}
}


//============================================================================================================================================================


int main()
{
	bool Continue=true;
	int selection;
	cout << "Please enter the number of the corresponding functions you wish to test" << endl;
	cout << "1.Check if a certain integer exists in the array" << endl;
	cout << "2. Modify the value of an integer" << endl; 
	cout << "3. Add a new integer to the end of the array" << endl;
	cout << "4. Remove an integer corresponding to a index" << endl;
	cout << "\n****__NOTE: Index starts from '0'__****\n\n" << endl;   // Reminds the user to be careful when entering the "index" as it starts from 0 and not 1
	//--------------------------------------in the above lines the user is shown all the options of the operations they can run on the file data
	while (Continue == true)  // while loop will run until the user enters a valid input, whuch is integer between 1-4
	{
		cout << "You entered: ";
		cin >> selection;
		if (selection==1 || selection==2 || selection == 3 || selection == 4)
		{
			SelectOptions(selection); // is a valid number was input the selection option function will be called to run and handle the class methods
		
			break;    // breaks the loop as a correct input was entered
		}
		else
		{
			cout << "!! Invalid input. Try Again !!\n\n\n" << endl;  // a warning is displayed if an invalid number was entered and continued with the loop to take another input until a valid value entered 
		}
	}

	cout << "\n\n_____See you later!_____" << endl;  // lastly a goodbye message ending the program



}





