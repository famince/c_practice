#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <libconfig.h++>

using namespace std;
using namespace libconfig;

int main(int argc, char** argv)
{
  Config cfg;
  cfg.readFile("array_example.conf");

  const Setting& root = cfg.getRoot();
  const Setting &arr  = root["array"];
  int count = arr.getLength();
  cout << "arr.count = " << count << endl;
  cout << "element : " << *arr << endl;
}

