#include<bits/stdc++.h>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

void splitter(const string &s, char delim, vector<string> &elems) {
    stringstream ss(s);
    string item;
    while (getline(ss, item, delim)) {
        elems.push_back(item);
    }
}

vector<string> split(const string &s, char delim) {
    vector<string> elems;
    splitter(s, delim, elems);
    return elems;
}

vector< vector<string> > Input;

int main()
{
  string temp,line,input,output;
  int i;
  vector<string> lines;
  float confidence,support,flag;
  ifstream myfile("config.csv");
  if(myfile.is_open())
  {
    i=0;
    while(getline(myfile, line))
    {
      temp = line.substr(line.find(",")+1,line.length()-1);
      if(i==0)
        input=temp;
      else if(i==1)
        output=temp;
      else if(i==2)
        support=std::atof(temp.c_str());
      else if(i==3)
        confidence=std::atof(temp.c_str());
      else if(i==4)
        flag=std::atof(temp.c_str());
      i++;
    }
    myfile.close();
    ifstream inputfile("input.csv");
    if(inputfile.is_open())
    {
      while(getline(inputfile, line))
      {
        lines.erase(lines.begin(), lines.end());
        lines = split(line, ',');
        Input.push_back(lines);
        lines.clear();
      }
    }
    else
      cout << "Unable to open input file\n";
    for(int i=0;i<Input.size();i++)
    {
      for(int j=0;j<Input[i].size();j++)
      {
        cout << Input[i][j] << " ";
      }
      cout << "\n";
    }
  }
  else
    cout << "Unable to open config file\n";
  return 0;
}
