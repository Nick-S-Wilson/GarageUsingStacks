#include <iostream>
#include <cstring>
#include <stack>
#include <string>
#include <fstream>
#include <stdlib.h>

using namespace std;


int licensePlatesCounter[20] = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };

int main()
{
	//garage declaration (move to header?)
	class garage
	{
	private:
		stack<string> lane1[10];	// lane 1
		stack<string> lane2[10];	// lane 2
		stack<string> street[20];	// street
		string licensePlates1[10];	// array for lane 1
		string licensePlates2[10];	// array for lane 2
		string licensePlatesStreet[20]; // array for street
		int lane1count = 0;		//count for lane 1
		int lane2count = 0;		// count for lane 2
		int streetCount = 0;	// count for street
	public:
		void pushing(string x) {

			if (lane1count == 10) // if lane one is full
			{
				if (lane2count == 10) // if lane two is also full
				{
					cout << "Garage full! Car NOT added." << endl;
					return;
				}
				else // if lane two is not full, add car to it
				{
					lane2[lane2count].push(x);
					licensePlates2[lane2count] = lane2[lane2count].top();
					lane2count++;
					cout << x << " added to Lane 2." << endl;
					return;
				}
			}// end full checks

			else if (lane1count <= lane2count) // lane comparison, adds to lane 1
			{
				lane1[lane1count].push(x);
				licensePlates1[lane1count] = lane1[lane1count].top();
				lane1count++;
				cout << x << " added to Lane 1." << endl;
				return;
			}
			else // lane comparison, adds to lane 2
			{
				lane2[lane2count].push(x);
				licensePlates2[lane2count] = lane2[lane2count].top();
				lane2count++;
				cout << x << " added to Lane 2." << endl;
				return;
			}
			return;
		};// end pushing


		void popping(string y) {


			//**Lane 1 search**

			int n = lane1count - 1; // counter var. starts at top of stack.
			char licenseFound1 = 'n';
			int popCount1 = 0; // number of pops to get to license plate.

			while (n >= 0)//searches top to bottom.
			{
				if (licensePlates1[n] == y)
				{
					licenseFound1 = 'y'; //marks license plate found

					while (popCount1 > 0)
					{
						if (lane2count < 10)
						{
							licensePlates2[lane2count] = licensePlates1[lane1count - 1]; //moves top of lane 1 onto lane 2.
							lane2[lane2count].push(licensePlates2[lane2count]); //push onto lane 2
							lane1[lane1count - 1].pop(); //pop off of lane 1

							cout << "Moved " << licensePlates1[lane1count - 1] << " to lane 2." << endl;
							licensePlatesCounter[lane1count - 1]++;

							lane2count++;
							lane1count--;


							popCount1--;
						}
						else
						{

							licensePlatesStreet[streetCount] = licensePlates1[lane1count - 1]; //moves top of lane 1 onto street.
							street[streetCount].push(licensePlatesStreet[streetCount]); //push onto street
							lane1[lane1count - 1].pop(); //pop off of lane 1
							licensePlatesCounter[lane1count - 1]++;//+1 moving into street
							licensePlatesCounter[lane1count - 1]++;//+1 moving back into garage

							streetCount++;
							lane1count--;

							popCount1--;
						}
					}//end while

					lane1[n].pop();
					cout << licensePlates1[lane1count - 1] << " Moved " << licensePlatesCounter[lane1count - 1] << " times." << endl;
					cout << licensePlates1[lane1count - 1] << " Removed from garage." << endl;
					lane1count--; //pushes the array back a space for overwriting the car removed.

					break;

				}//end if license plate is found

				popCount1++; //increment number of pops
				n--; // decrement counter


			}//end while (searched full stack).

			 //**end Lane 1 search**


			 //**Lane 2 search**

			int n2 = lane2count - 1; // counter var. starts at top of stack.
			char licenseFound2 = 'n';
			int popCount2 = 0; // number of pops to get to license plate.

			while (n2 >= 0)//searches top to bottom.
			{
				if (licensePlates2[n2] == y)
				{
					licenseFound2 = 'y'; //marks license plate found

					while (popCount2 > 0)
					{
						if (lane1count < 10)
						{
							licensePlates1[lane1count] = licensePlates2[lane2count - 1]; //moves top of lane 2 onto lane 1.
							lane1[lane1count].push(licensePlates1[lane1count]); //push onto lane 1
							lane2[lane2count - 1].pop(); //pop off of lane 2

							cout << "Moved " << licensePlates2[lane2count - 1] << " to lane 2." << endl;
							licensePlatesCounter[lane2count - 1]++;

							lane1count++;
							lane2count--;

							popCount2--;
						}
						else
						{

							licensePlatesStreet[streetCount] = licensePlates2[lane2count - 1]; //moves top of lane 2 onto street.
							street[streetCount].push(licensePlatesStreet[streetCount]); //push onto street
							lane2[lane2count - 1].pop(); //pop off of lane 2
							licensePlatesCounter[lane2count - 1]++;//+1 moving into street
							licensePlatesCounter[lane2count - 1]++;//+1 moving back into garage

							streetCount++;
							lane2count--;

							popCount2--;
						}
					}//end while

					lane2[n2].pop();
					cout << licensePlates2[lane2count - 1] << " Moved " << licensePlatesCounter[lane2count - 1] << " times." << endl;
					cout << licensePlates2[lane2count - 1] << " Removed from garage." << endl;
					lane2count--; //pushes the array back a space for overwriting the car removed.

					break;


				}//end if license plate is found

				popCount2++; //increment number of pops
				n2--; // decrement counter


			}//end while (searched full stack).

			 //** end Lane 2 search**




		};//end popping


		bool streetMove()
		{
			if (streetCount > 0)
			{
				pushing(licensePlatesStreet[streetCount - 1]);
				streetCount--;
				return 1;
			}
			else
				return 0;

		};//end streetMove


	};	//end garage declaration


	garage mytest1; //creates a new garage obj.


	string arraytest[20]; // array for license plates (max spots in garage is 20.
	int i = 0; //counter

	string licenseCheck; // temp variable for duplicates
	string line; //variable for input from file.
	const char *path = "G:\garageText.txt"; // specifies the path where the file is located.
	ifstream myfile; // variable for the file.
	myfile.open(path); // opens file for reading.

	while (!myfile.eof()) // loops until the end of the file.
	{
		myfile >> line; // reads in the license plate or command.

		if (line == "A") // arriving car
		{
			int m = 0;
			char checkA = 'n';

			while (m < i - 1)
			{
				if (arraytest[m] == arraytest[i - 1]) // checks all previous spots to see if the car already exists?
				{
					checkA = 'y';
					cout << "Car exists already!" << endl;
					break;
				}
				else
				{
					m++;
				}

			}//end while (checking if license plate already exists)

			if (checkA == 'n')
			{
				mytest1.pushing(arraytest[i - 1]);
			}
		}//end arrive




		else if (line == "D") // departing car
		{
			int m = 0;
			char checkD = 'n';

			while (m < i)
			{
				if (arraytest[m] == licenseCheck) // checks all previous spots to see if the car already exists?
				{
					checkD = 'y';
					mytest1.popping(arraytest[m]);

					//move cars in street back into garage.
					while (mytest1.streetMove() == 1)
					{
						cout << "moved car back into garage!" << endl;
					}


					//remove car from array! i--?
					break;
				}
				else
				{
					m++;
				}

			}//end while (checking if license plate already exists)

			if (checkD == 'n')
			{
				cout << "Car doesn't exist!" << endl;
			}

		}//end Depart





		else //license plate being read in.
		{
			int l = 0;
			char check = 'n';

			while (l <= i)
			{
				if (arraytest[l] == line)
				{
					check = 'y';
					licenseCheck = line; // the duplicate license is placed into a temp variable.
					break;
				}
				else
				{
					l++;
				}

			}//end while (checking if license plate already exists)

			if (check == 'n') //if license plate is unique, add it to the array and increment i.
			{
				arraytest[i] = line;
				i++;
			}


		}//end license plate




	} //end while (reading in from file)

	myfile.close(); // closes the file.



	system("pause");
	return 0;
}