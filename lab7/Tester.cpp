//Main Program to test Binary Min Heap functions
#include <iostream>
#include <string>
#include <fstream>
#include <stdexcept>
#include "myBinaryMinHeap.hpp"
using namespace std;
int main(int argc, char *argv[])
{
      if (argc != 3)
      {
            std::cout << "You have to provide one test instance file and output file name to run the test main!\n";
            return 0;
      }

      //File Intiallization for input and output files
      ifstream inFile;
      ifstream inFile1;
      inFile.open(argv[1]);
      ofstream outfile(argv[2]);

      //Open input and out file and sstart with Binary Min Heap methods
      if (inFile.is_open() and outfile.is_open())

      {
            int num;
            //Binary Min Heap object with <int> as templete type
            myBinaryMinHeap<int> BH;
            while (!inFile.eof())
            {
                  inFile >> num;
                  /**
*  @Pre  A new instance has been read from input file
*  @Post Add the input instance from input file into Binary Min Heap using insert
*/
                  BH.insert(num);
            }
            /**
*  @Pre  The current Binary Min Heap as input and write to output file
*  @Post Prints all the elements of Binary Min Heap in LevelOrder to output file
*/
            BH.levelOrder(outfile);
            outfile << "\n";
            /**
*  @Pre  The current Binary Min Heap as input and write to output file
*  @Post Prints minimum element of Binary Min Heap to output file
*/
            outfile << BH.findMin() << "\n";
            /**
*  @Pre  The current Binary Min Heap as input and write to output file
*  @Post Check if Binary Min Heap is empty or not
*/
            outfile << BH.isEmpty() << "\n";
            outfile << "\n";
            /**
  *  @Pre  Current Binary Min Heap as input
  *  @Post Remove first 5 elements from input files from Binary Min Heap
  */
            int count = 0;
            while (count < 5)
            {
                  BH.deleteMin();
                  count = count + 1;
            }
            /**
*  @Pre  The current  Binary Min Heap as input and write to output file
*  @Post Prints minimum element of  Binary Min Heap to output file
*/
            outfile << BH.findMin() << "\n";
            /**
  *  @Pre  Current Binary Min Heap as input
  *  @Post Remove first 5 elements from input files from Binary Min Heap
  */
            count = 0;
            while (count < 5)
            {
                  int min = BH.findMin();
                  BH.deleteMin(min);
                  count = count + 1;
            }
            outfile << "\n";
            /**
*  @Pre  The current  Binary Min Heap as input and write to output file
*  @Post Prints minimum element of  Binary Min Heap to output file
*/
            outfile << BH.findMin() << "\n";
            outfile << "\n";
            /**
*  @Pre  The current  Binary Min Heap as input and write to output file
*  @Post  makes Binary Min Heap empty
*/
            BH.makeEmpty();

            /**
*  @Pre  The current Binary Min Heap as input and write to output file
*  @Post Check if Binary Min Heap is empty or not
*/
            outfile << BH.isEmpty() << "\n";
      }
      else
      {
            cout << "The instance.txt file cannot be opened";
      }
      inFile.close();
      outfile.close();
}