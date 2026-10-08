#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
using namespace std;

const int Maxrunners = 50;
const int Numdays = 7;
// Const ints for the maximum number of Runners and Days respectively.



// Structure to define a Runner's Name and Miles.
struct Runner
{
	string name;
	double mileage[Numdays];
	double Total;
	double Average;
};

// This grabs the file who's name it gets associated with in the Main.
// Then formats that info via the Runner Struct.
int ReadRunnerData(const string& file, Runner runners[]);

//This is what'll calculate the runner's statistics.
void stats(Runner runners[], int count);

//This will Display the statistics gathered from the above.
void display(const Runner runners[], int count);


// Reads the recorded data from the Runner File & returns the number of Runners.
int ReadRunnerData(string& file, Runner runners[])
{
	ifstream infile(file);

	// Tells you if the File had an error when attempting to open.
	if (!infile)
	{
		cout << "Why did you kill my old pal: " << file << endl;
		return 0;
	}

	int count = 0;

	// Allows the algorithm to loop as long as the number of runners is below the Maxrunner threshold (50).
	while (count < Maxrunners && infile >> runners[count].name)
	{
		// Tallys up the Mileage from each runner per day. (As dictated by the Numdays (7))
		for (int i = 0; i < Numdays; ++i)
		{
			infile >> runners[count].mileage[i];
		}
		//Ticks up the number of Runners for every Record Read.
		// (Very important that this is IN the while so it actually counts every time)
		// (Not below it, like I had it originally)...
		count++;
	}
	//Exits the file to allow the program to continue.
	infile.close();
	// Gives the Main a size to work with and quantify. 
	return count;
}


int main()
{
	Runner runners[Maxrunners];
	// This gives the ReadRunnerData a target to check.
	string file = "runners.txt";

	// This tells ReadRunnerData to actually start Reading said data.
	// (I may or may not have forgotten to add this and was confused for a good 20 min... Not my best moment).
	int Runnercount = ReadRunnerData(file, runners);

	// Makes sure that you didn't leave the file empty.
	if (Runnercount == 0)
	{
		cout << "No Records, Did you forget to fill in the File?" << endl;
		return 1;
	}
	
	// Plays the stats check.
	stats(runners, Runnercount);
	// Displays the stats checked.
	display(runners, Runnercount);

	return 0;
}

// The Function that parses out the Runners Statistics. Including the Total and Averages for each day.
void stats(Runner runners[], int count)
{
	for (int i = 0; i < count; ++i)
	{
		// This finds the Totals per day.
		runners[i].Total = 0;
		for (int j = 0; j < Numdays; ++j)
		{
			// This states the Mileage by adding the Totals of each day together.
			runners[i].Total += runners[i].mileage[j];
		}
		//This finds the Averages by dividing the Total by the number of days.
		runners[i].Average = runners[i].Total / Numdays;
	}
}

//Displays the formatted Stats as described.
void display(const Runner runners[], int count)
{
	// Allows the user to see and understand the format that will be used.
	cout << "Runner Detail Format: " << endl;
	cout << "Names: ";
	cout << "Totals, ";
	cout << "Averages." << endl;
	cout << endl;

	// The Formatted runner names and statistics as provided by the associated runner file.
	for (int i = 0; i < count; ++i)
	{
		cout << runners[i].name << ": ";
		cout << runners[i].Total << ", ";
		cout << runners[i].Average << "." << endl;
	}
}
