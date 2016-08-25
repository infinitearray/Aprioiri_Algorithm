#include<bits/stdc++.h>

using namespace std;

int main()
{
  string line,input,output;
  ifstream myfile("config.csv");
  if(myfile.is_open())
  {
    while(getline(myfile, line))
    {
      cout << line.substr(line.find(",")+1,line.length()-1) << "\n";

    }
    myfile.close();
  }
  else
    cout << "Unable to open file\n";
  return 0;
}
