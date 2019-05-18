#include <iostream>

using namespace std;

#include "../Utilities/Utils.h"
#include "../Utilities/Scanner.h"
#include "../Utilities/ScanLine.h"


static const string TAG = "Main: ";

int main(int argc, char *argv[])
{
  string inFileName1 = "";
  string inFileName2 = "";
  ofstream outStream;
 
  Scanner scanner1;
  Scanner scanner2;  

  string element = "";
 
  Utils::CheckArgs(2, argc, argv, "infilename (first matrix) outfilename (second matrix)");
  inFileName1 = static_cast<string>(argv[1]);
  inFileName2 = static_cast<string>(argv[2]);

  scanner1.openFile(inFileName1);
  scanner2.openFile(inFileName2);  
  
  while (scanner1.hasNext()) {

      element = scanner1.next();
      cout << element << endl;      
  }
  

  
  return 0;
}
