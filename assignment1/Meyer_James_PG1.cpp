//	Author: James Meyer
//	Roster Number: 39
//	Due Date: 9/10/2018
//	Programming Assignment Number 1
//	Fall 2018 - CS 3358 - 002
//
//	Instructor: Husain Gholoom
//
//	Discription: The following program generates a two dimensional array of
//	non-repeating numbers and determines if that array is a magic square. All
//	relevent data is stored in the square structure.

#include <iostream>
#include <ctime>
#include <cstdlib>
using namespace std;

struct square {
	int dim;	// dim is equal to "n" in accordance with
				// the formula magicnum = n(n^2 + 1) / 2.
	int array[10][10];

	int magic_num;
	int row_sum[10];
	int col_sum[10];
	int diag_sum[2];
};

// function prototypes
void init_square(struct square* s, int n);
void populate_square(struct square* s);
int array_find(int* a, int len, int target);
void display_square(struct square* s);
void sum_rows(struct square* s);
void sum_diagonals(struct square* s);
void sum_columns(struct square* s);
void is_magic_square(struct square* s);

// init_square
//	Initializes the content of a struct type square.
//	Accepts a pointer to the square, and its dimensions.
//	The dimensions must be between 2 and 10.
void init_square(struct square* s, int n){

	s->dim = n;
	for(int i = 0; i < 10; i++){
		for(int j = 0; j < 10; j++){
			s->array[i][j] = 0;
		}
	}

	s->magic_num = ( n * ( (n*n) + 1 ) ) / 2;
}

// populate_square
//	Fills the square with unique, non-repeating integers
//	between 1 and 100.
void populate_square(struct square* s){

	int area = s->dim * s->dim;		// n^2 (max=100,min=4)
	int unique[100];				// array is of pre-defined size
	for(int i = 0; i < 100; i++){
		unique[i] = 0;
	}

	srand( (unsigned) time(NULL) );	// seed rand
	int r = 0;						// recipient of rand

	for(int i = 0; i < area; i++){
		do{
			r = (rand() % 100) + 1;	// generate random number
		}while(array_find(unique, area, r) != -1);
		unique[i] = r;				// store r in unique list
	}

	int pos = 0;
	for(int i = 0; i < s->dim; i++){
		for(int j = 0; j < s->dim; j++){
			s->array[i][j] = unique[pos];
			pos++;
		}
	}

}

// find
//	Locates a "target" in the array "a".
//	Returns either the location or -1 in the
//	case the target is not found int the array.
int array_find(int* a, int len, int target){

	for(int i = 0; i < len; i++){
		if(target == a[i]){
			return i;
		}
	}
	return -1;
}

void display_square(struct square* s){
	cout << "\nThe magic sequence that is create for the size " << s->dim << ":\n";

	for(int i = 0; i < s->dim; i++){
		for(int j = 0; j < s->dim; j++){
			cout << s->array[i][j] << "\t";
		}
		cout << "\n";
	}
	cout << "\nThe magic number is " << s->magic_num << "\n\n";
}

void sum_rows(struct square* s){
	int sum = 0;
	for(int i = 0; i < s->dim; i++){
		for(int j = 0; j < s->dim; j++){
			sum = sum + s->array[i][j];
		}
		cout << "Sum of numbers in Row\t\t# " << i << "\t=\t" << sum << "\n";
		s->row_sum[i] = sum;
		sum = 0;
	}
}

void sum_diagonals(struct square* s){
	int sum = 0;
	for(int i = 0; i < s->dim; i++){
		sum = sum + s->array[i][i];
	}
	cout << "Sum of numbers in first diagonal\t" << "=\t" << sum << "\n";
	s->diag_sum[0] = sum;
	sum = 0;
	for(int i = s->dim -1; i > -1; i--){
		sum = sum + s->array[i][i];
	}
	cout << "Sum of numbers in second diagonal\t" << "=\t" << sum << "\n";
	s->diag_sum[1] = sum;
}

void sum_columns(struct square* s){
	int sum = 0;
	for(int i = 0; i < s->dim; i++){
		for(int j = 0; j < s->dim; j++){
			sum = sum + s->array[j][i];
		}
		cout << "Sum of numbers in Column\t# " << i << "\t=\t" << sum << "\n";
		s->col_sum[i] = sum;
		sum = 0;
	}
}

void is_magic_square(struct square* s){

	bool query = true;
	if(s->diag_sum[0] != s->magic_num || s->diag_sum[1] != s->magic_num){
		query = false;
	}

	for(int i = 0; i < s->dim && query == true; i++){
		if(s->row_sum[i] != s->magic_num || s->col_sum[i] != s->magic_num)
		{
			query = false;
		}
	}

	if(query == true){
		cout << "\nThe above is a magic square.\n";
	}else{
		cout << "\nThe above is not a magic square.\n";
	}
}

int main(void){

	cout << "Welcome to my magic sequence program. The function of the program is to\n\n"
	<< "\t1. Allow the user to enter the size of the magic square such as N.\n"
	<< "\t   N >= 2 and <= 10.\n"
	<< "\t2. Create an array of size N x N.\n"
	<< "\t3. Populate the array with distinct random numbers.\n"
	<< "\t4. Display the sum for each row, column, and diagnal then determine whether\n"
	<< "\t   the numbers in an N x N array are magic square numbers.\n";

	bool run = true;
	struct square sqr;	// create a square on the stack

	while(run == true){

		// beginning input
		// enter the size of the square.
		int size = -1;
		bool valid_size = false;
		do{
			cout << "\nEnter the size of the magic square: ";
			cin >> size;
			if(size >= 2 && size <= 10){
				valid_size = true;
			}else{
				cout << "\nError *** magic square size must be >= 2 and <= 10\n";
			}
		}while(valid_size == false);

		// square generation, computation, and output

		init_square(&sqr, size);	// initialize the square
		populate_square(&sqr);		// populate the square with nonrepeating ints

		display_square(&sqr);
		sum_rows(&sqr);
		sum_columns(&sqr);
		sum_diagonals(&sqr);
		is_magic_square(&sqr);

		// final input
		// exit or run the program again.
		char ch_run = '\0';	// set equal to null terminating character
		while(ch_run != 'N' && ch_run != 'n' && ch_run != 'Y' && ch_run != 'y'){
			cout << "\nWould you like to find another magic square? - Enter y/Y for yes\n"
			<< "or n/N for no: ";
			cin >> ch_run;

			if(ch_run == 'N' || ch_run == 'n'){
				run = false;
			}
		}
	}

	cout << "\nThis magic square algorithm is implemented by James Meyer.\n";
}
