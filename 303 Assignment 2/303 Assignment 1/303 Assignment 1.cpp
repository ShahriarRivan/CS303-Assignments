
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
	int getDataSize()
	{
		return DataSize;
	}

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



void SelectOptions(string option)   //------------------ This function (separate from the class) calls the class to direct the tasks to be done based on the options selected from the main fucntion
{
	C1 MyObject;                    // Creating an onject of the class C1
	int  dataSize= MyObject.getDataSize(), count=0, count2=0;
	string input;
	bool run = true;
	MyObject.InsertDataInArray();   // Calls a method of the class which inputs all the data from the file to the array
	
	if (option == "1")   // Option 1 was chosen from the main menu this will run
	{
		while (run == true)
		{
			count = 0;
			try
			{
				cout << "\nEnter the integer you want to locate: ";  // Prompts the user to enter the number they want to search and assigns it to a variable on the next line
				cin >> input;
				for (int i = 0; i < input.length(); i++)
				{
					if (isdigit(input[i]) != 0)
					{
						count++;
					}
				}
				if (count== input.length())
				{
					run = false;
				}
				else
				{
					throw 101;
				}
			}
			catch (int x)
			{
				cout << "\n----------------------------\n!!***Please enter again***!!\n!!       Error: " << x << "       !!\n----------------------------" << endl;
			}           
		}
		if (MyObject.find(stoi(input)) == -10)  //based on the return number from the method of "C1" it can determine if a match was found or not. in this case -10 means no match found
		{
			cout << "The integer you are looking for was not found" << endl;  // prints no match found message 
		}
		else  // if the return isn anything other than -10 that means a match was found and  it prints the matched index on the mext line
		{
			cout << "The integer '" << input << "' was found in index " << MyObject.find(stoi(input)) << endl;
		}
		
	}
	if (option == "2")     // Option 2 was chosen from the main menu this will run
	{
		string index;

		while (run == true) // Assignment 2--testing and handling exception inside the while loop so that the user is shown an error and prompted to enter valid input until done so
		{
			count = 0;
			count2 = 0;
			try
			{    // the user is prompted to enter the index they want to modefy and the new number they want to change it to in the next few lines
				cout << "Please enter the index you wish to modefy: ";
				cin >> index;
				cout << "\nPlease enter the new integer : ";
				cin >> input;
				for (int i = 0; i < input.length(); i++) //loop testing is all the characters inside the input is an integer
				{
					if (isdigit(input[i]) != 0)
					{
						count++;
					}
				}
				for (int j = 0; j < index.length(); j++) //loop testing is all the characters inside the index-input is an integer
				{
					if (isdigit(index[j]) != 0)
					{
						count2++;
					}
				}
				if ((count==input.length()) && (count2==index.length()) && ((stoi(index))<dataSize))
				{
					run = false;
				}
				else
				{
					throw 101; //error code '101' means invalid input
				}
			}
			catch (int x)
			{
				cout << "\n----------------------------\n!!***Please enter again***!!\n!!       Error: " << x << "       !!\n----------------------------" << endl;
			}
		}
		cout << "The index " << index << " was modefied\nWhich previously had the integer: " << MyObject.modify((stoi(index)), (stoi(input))) << "\nNow it has been changed to: "<<input << endl;
		//  in the line above the modefied index, the old number the index contained and the new number is printed to tyeh screen
	}
	if (option == "3")     // Option 3 was chosen from the main menu this will run
	{
		//---
		while (run == true)// Assignment 2--testing and handling exception inside the while loop so that the user is shown an error and prompted to enter valid input until done so.
		{
			count = 0;
			try
			{
				cout << "Enter the integer you wish to add at the end of the array: "; // user is prompted to enter a number they wish to add to the array.
				cin >> input;
				for (int i = 0; i < input.length(); i++) //loop testing is all the characters inside the input is an integer
				{
					if (isdigit(input[i]) != 0)
					{
						count++;
					}
				}
				if (count == input.length()) 
				{
					run = false;
				}
				else
				{
					throw 101; //error code '101' means invalid input
				}
			}
			catch (int x)
			{
				cout << "\n----------------------------\n!!***Please enter again***!!\n!!       Error: " << x << "       !!\n----------------------------" << endl;
			}
		}
		//---
		
		MyObject.AddData(stoi(input));
		cout << "The new array is:" << endl; 
		MyObject.Print(0, 0);     // the new updated array is printed to the screen
	}
	if (option == "4")     // Option 4 was chosen from the main menu this will run
	{
		cout << "Enter the index you wish to remove: ";  // the user is prompted to enter the index they wish to delete 
		cin >> input;
		MyObject.removeData(stoi(input));
		MyObject.Print(0, 1);   // the new updated array is printed to the screen
	}
}


//================================== ^^^ Assignment 1 ^^^ ==========================================================================================================================









class employee  //employee abstract class
{
private:
	string Fname, Lname, ID;
public:
	virtual void calcWeeklySalary() = 0;  //Abstract function to calculate weekly salary
	virtual void calcVacation() = 0;      //Abstract function to calculate Vacation days earned so far
	virtual void calcHealthcare() = 0;    //Abstract function to calculate how much of the weekly salary went to Health care payments

	void setName(string fname, string lname)
	{
		Fname = fname;
		Lname = lname;
	}
	void setID(string id)
	{
		ID = id;
	}
	void printNameID()   // Function printing the employee's name and id
	{
		cout << "\n\nName: " << Fname << " " << Lname << endl;
		cout << "ID  : " << ID << endl;

	}



};

class professional : public employee  //child class of employee class for salaried employees which has its own calculation for salary, vacation and healthcare payment
{
private:

	double yearlysalary = 120000;  //Fixed yearly salary
	double weeklySalary = 0;
	double vacationPercentage = 0.041; // percentage of vacation days earned based on the amount of days worked
	double HcPercentCut = 0.096;       // weekly percentage cut for healthcare from the salary
	double HcContribution = 0;
	double daysWorked = 0;
	int vacationDaysEarned = 0;



public:
	void setDaysWorked(double DaysWorked)  //getting and setting days worked by the employee
	{
		daysWorked = DaysWorked;
	}
	void calcWeeklySalary()    //calculating weekly salary
	{
		weeklySalary = yearlysalary / 52;
	}
	void calcVacation()  //calculating vacation days earned
	{
		vacationDaysEarned = daysWorked * vacationPercentage;
	}
	void calcHealthcare()  // calculating the cut of healthcare from the weekly payment
	{
		HcContribution = (((yearlysalary / 52)) * HcPercentCut);
	}

	void printInfo()  // printing all the calculated info
	{
		calcWeeklySalary();
		calcVacation();
		calcHealthcare();
		cout << "                       Weekly Salary :  $ " << weeklySalary << endl;
		cout << "                Vacation days earned :  " << vacationDaysEarned << " days" << endl;
		cout << "Amount went to health Care every week:  $ " << HcContribution << endl;
		

	}



};



class nonProfessional : public employee //child class of employee class for hourly employees which has its own calculation for salary, vacation and healthcare
{
private:

	double hourlyRate = 25;   //hourly rate of the employee
	double vacationPercentage = 0.02; // percentage of vacation days earned based on the amount of days worked
	double weeklySalary = 0;
	double HcPercentCut = 0.07;  // weekly percentage cut for healthcare from the salary
	double HcContribution = 0;
	int vacationHoursEarned = 0;
	int hoursWorked = 0;
	int hrsWorkedThisMonth = 0;
public:
	void setHours(double HoursWorked)  //getting and setting hours worked by the employee this week
	{
		hoursWorked = HoursWorked;
	}
	void setHoursPerMonth(double HrsWorkedThisMonth) //getting and setting hours worked by the employee this month
	{
		hrsWorkedThisMonth = HrsWorkedThisMonth;
	}
	void calcWeeklySalary() //calculating weekly salary
	{
		weeklySalary = hoursWorked * hourlyRate;
	}
	void calcVacation()   //calculating vacation days earned
	{
		vacationHoursEarned = hrsWorkedThisMonth * vacationPercentage;
	}
	void calcHealthcare() // calculating the cut of healthcare from the weekly payment
	{
		HcContribution = ((hoursWorked * hourlyRate) * HcPercentCut);
	}

	void printInfo() // printing all the calculated info
	{
		calcWeeklySalary();
		calcVacation();
		calcHealthcare();

		cout << "                   Weekly Salary :  $ " << weeklySalary << endl;
		cout << "Vacation hours earned this month :  " << vacationHoursEarned << " hours" << endl;
		cout << "      Amount went to health Care :  $ " << HcContribution << endl;
	}
};



//================================== ^^^ Assignment 2 ^^^ ==========================================================================================================================

int main()
{
	professional proemployee;
	nonProfessional nonproemployee;
	employee* pro = &proemployee;
	employee* NoPro = &nonproemployee;

	string fname, lname, id;
	int  worked, nonWorked;
	char status;
	// ^ used for Assignment 2


	bool Continue=true;
	string selection;
	// ^ used for Assignment 1

	string optn;
	bool loop = true;
	
	
	while (loop == true)
	{
		cout << "Which program do you want to run?\n\n1. Modefying Data from a file (Assignment 1).\n2. Calculate Employee data (Assignment 2)\n !! Enter either 1 or 2\n\n" << endl;
		cin >> optn;
		if (optn == "1")  //option 1 for version 2 of assignment 1
		{
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
				if (selection == "1" || selection == "2" || selection == "3" || selection == "4")
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

			loop = false;
		}
		else if (optn == "2")  //option 2 for assignment 2 
		{
			cout << "Please enter some information about your employee." << endl;
			cout << "First Name: ";
			cin >> fname;    // enter employee's first name
			cout << "Last Name : ";
			cin >> lname;    // enter employee's last name
			fname[0] = toupper(fname[0]);  //converting first character of the name to uppercase
			lname[0] = toupper(lname[0]); //converting first character of the name to uppercase
			cout << "ID  : ";
			cin >> id;  // enter employee ID
			cout << "Is he Professional? Y/N: ";
			cin >> status;  // Status indicates if the employee is salaried or hourly

			if (status == 'y' || status == 'Y')  // for salaried employees
			{
				proemployee.setName(fname, lname);
				proemployee.setID(id);
				cout << "How many days did this person work so far this year? ";
				cin >> worked;
				proemployee.setDaysWorked(worked);
				cout << "\n\n-------------------------------------------------------------------------------------------" << endl;
				proemployee.printNameID();
				proemployee.printInfo();
				cout << "\n\n-------------------------------------------------------------------------------------------" << endl;

			}
			else if (status == 'n' || status == 'N') // fro hourly employees
			{
				nonproemployee.setName(fname, lname);
				nonproemployee.setID(id);
				cout << "How many hours did this person work this week? ";
				cin >> worked;
				cout << "How many hours did this person work this month? ";
				cin >> nonWorked;
				nonproemployee.setHours(worked);
				nonproemployee.setHoursPerMonth(nonWorked);
				cout << "\n\n-------------------------------------------------------------------------------------------" << endl;
				nonproemployee.printNameID();
				nonproemployee.printInfo();
				cout << "\n\n-------------------------------------------------------------------------------------------" << endl;
			}
			loop = false;
		}
		else
		{
			cout << "\n----------------------------\n!!***Please enter again***!!\n!!       Error: 101" << "       !!\n----------------------------" << endl;
		}
    }



	

}





