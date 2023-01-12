/*
Name: Marlon Alejandro, 5002573038, 1001, ASSIGNMENT_4
Description: Create function that call it self to create a desired output
Input: User inputed
Output: Output to terminal
*/

#include <iostream>
#include <exception>

using namespace std;

const int WIDTH = 4;
const int HEIGHT = 5;

//Function prototypes
int power(const int&, int);
bool isValueInArray(int[], int, int, const int&);
void findTheX(char grid[HEIGHT][WIDTH], const int& x, const int& y);

//First maze to solve
char maze1[HEIGHT][WIDTH] = {
	{' ', ' ', ' ', ' '},
	{' ', ' ', ' ', ' '},
	{' ', ' ', ' ', ' '},
	{' ', ' ', 'X', ' '},
	{' ', ' ', ' ', ' '},
};

//Second maze to solve
char maze2[HEIGHT][WIDTH] = {
	{' ', 'X', 'O', ' '},
	{' ', ' ', 'O', ' '},
	{' ', ' ', 'O', ' '},
	{' ', ' ', 'O', ' '},
	{' ', ' ', ' ', ' '},
};

//Array for the search function
int arr[16]{ 1, 2, 5, 6, 7, 9, 10, 12,
			15, 18, 19, 20, 22, 23, 28, 30 };

//Main just calls each of the individual recursion functions
int main()
{
	int functionToTest = -1;

	//Print a prompt
	cout << "Which function should be tested?" << endl;
	cout << "(1) power" << endl;
	cout << "(2) isValueInArray" << endl;
	cout << "(3) findTheX" << endl;

	cin >> functionToTest; //Read in the choice
	while (cin.fail() || functionToTest < 1 || functionToTest > 4)
	{
		cout << "Error, invalid choice. Please pick a number 1-4" << endl;
		cin.ignore(1024, '\n');
		cin.clear();
	}

	//After the read works, run the testing code for the choice
	switch (functionToTest)
	{
		case 1:
			cout << "2^10 = " << power(2, 10) << endl;
			cout << "4^0 = " << power(4, 0) << endl;
			break;
		case 2:
			cout << "Is 2 in the array? " <<
				(isValueInArray(arr, 0, 16, 2) ? "yes" : "no") << endl;
			cout << "Is 6 in the array? " <<
				(isValueInArray(arr, 0, 16, 6) ? "yes" : "no") << endl;
			cout << "Is 21 in the array? " <<
				(isValueInArray(arr, 0, 16, 21) ? "yes" : "no") << endl;
			break;
		case 3:
			cout << "---- Maze 1 ----" << endl;
			findTheX(maze1, 1, 1);
			cout << "---- Maze 2 ----" << endl;
			findTheX(maze2, 3, 2);
			break;
	}
}

/**/
int power(const int& base, int pow)
{
	//Check for the base case; anything to the 0th is trivial to solve
	//Otherwise, recursively take the power of a base with a lower power

	//anything to the power of 0 is one
	// if power == 0 return 1
	if(pow==0){
		return 1;
	}

	//multiplies the base and the results of the recursibly called function
	// until base case is reached
	return base*power(base,pow-1);

}

/* */
bool isValueInArray(int arr[], int start, int length, const int& value)
{
	//Check if the array is of length 0, in which case, the solution is trivial
	//(we can't find any value in an empty array)
	if(length==0){
		return false;
	}

	//Check if the current element being looked at is a match
	//If so, we found it
	
	//Calculations for the length of the left and right sub arrays and the index the middle is 
	//at for your convenience
	int leftLength = length / 2;
	int rightLength = length - leftLength;
	int middle = start + leftLength;

	//If we did not find the element, recursively search for it

	//check the value in the middle of the array
	if(arr[middle]==value){
		return true;
	} 

	// return false if there is only one remaining
	//value in the array
	if(length==1){
		return false;
	}

	//if the value is lesser than the value in the array
	//traverse to the lower half of the array
	if(arr[middle]>value){
		return isValueInArray(arr,0,leftLength,value);
	}

	//if the value is higher than the value in the array
	//traverse to the upper half of the array
	if(arr[middle]<value){
		return isValueInArray(arr,middle,rightLength,value);

	}
	return false;
}
/* */
void findTheX(char grid[HEIGHT][WIDTH], const int& x, const int& y)
{
	//If the char at the current spot is an X, then we solved it
	//Print the message andmark the spot as a O now to make sure we don't find it twice
	//Else if the char is an 'O', it is either a wall or has been verified 
	//to not contain the X
	if(grid[y][x]=='X'){
		cout<<"Found the X at (" << x << ", "<< y << ")" << endl;   // if X is found, output to terminal
		grid[y][x]='O';		                                        //then set X to O 
	}
	else if(grid[y][x]=='O'){
		return;                                                     //if the space is marked as O, then skip
	}
	if(grid[y][x]!='O'){
		grid[y][x]='O';
	}
	//If this is not the X or an O, mark this spot as a O then recursively try the right, left, above
	//and below spots only if each ear in bounds of the array
	// if(grid[y][x]!='O' || grid[y][x]=='X'){
		if(y<HEIGHT-1)
			findTheX(grid, x, y+1);                          //bound check if y doesnt exceed height
		if(y>0)
			findTheX(grid, x, y-1);                          //bound check if y isn't less than 0
		if(x>0)
			findTheX(grid, x-1, y);                          //bound check if x isn't less than 0
		if(x<WIDTH-1)
			findTheX(grid, x+1, y);                          //bound check if x doesnt exceed width
	// }

	//You can assume the grid always has dimensions of the consts HEIGHT and WIDTH
	//by the parameter declaration above and that the X is always findable. Consider
	//that with row major arrays, y should come before x when accessing, as well
}