//
// Array Visualisation for CIS6007 WRIT1
//

#include <iostream>
#include <string>
#include <random>
#include "gl_stuff.h"
#include "Array2D.h"
#include <tbb/tbb.h>
#include <ctime>



using namespace std;
using namespace tbb;


#pragma region Function Prototypes



void initPattern(Array2D<int>& array); // Initialise grid with "alive" and "dead" cell patterns
void update(void);




//Any live cell with fewer than two live neighbours dies, as if by underpopulation.
//Any live cell with two or three live neighbours lives on to the next generation.
//Any live cell with more than three live neighbours dies, as if by overpopulation.
//Any dead cell with exactly three live neighbours becomes a live cell, as if by reproduction.



// Main update function - apply Game of Life rules here

#pragma endregion


//
// size of the grid here
//
Array2D<int>						myArray = Array2D<int>(100, 100);


// Starting point for our program...
int main(int argc, char* argv[])
{
	// Initialise OpenGL window...
	gl_init(argc, argv, update, "CIS6007 WRIT1 - Game of Life Demo", true);

	// Initialise our Game of Life starting pattern...
	initPattern(myArray);

	// Start the main loop - this calls our update function (below) to update our game of life generations.
	// Note: We never return from glutMainLoop until we quit the application
	glutMainLoop();

    return 0;
}


// Initialise grid with "alive" and "dead" cell patterns
void initPattern(Array2D<int>& array) {

	// 1. First clear the array (set all cells to "dead" ie. 0)
	parallel_for(
		0,
		array.w * array.h,
		[&](int i) {

			int x = i % array.w;
			int y = i / array.h;
			array(x, y) = 0;
		}
	);

	//2. Setup random number generator
	random_device						rd;
	mt19937								mt(rd());
	uniform_int_distribution<int>		iDist(0, 1);

	srand(time(NULL));
	cout << rand()%1;

	//3. Set cells randomly to be "dead" (0) or "alive" (1)
	
	parallel_for(
		0,
		myArray.w * myArray.h,
		[&](int i) {

			int x = i % myArray.w;
			int y = i / myArray.h;
			myArray(x, y) = iDist(mt);// (int)round(rDist(mt));
		}
	);
	
	// NOTE: *** REPLACE STEP 3 WITH YOUR OWN CODE TO SETUP THE LIVE CELL PATTERNS
	myArray(2, 2) = 1;
	myArray(2, 3) = 1;
	myArray(2, 4) = 1;
}


// Main update function - apply Game of Life rules here
// Note: This is called by FreeGLUT's main event loop - YOU DON'T NEED TO CALL THIS - IT'S CALLED FOR YOU!!!
void update(void) {

	//
	// *** ADD PARALLEL CODE HERE TO UPDATE GAME OF LIFE ***
	//


	
	// Redraw the screen to show latest generation
	renderLatestGeneration(myArray);
}
