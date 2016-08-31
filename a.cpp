#include<bits/stdc++.h>

using namespace std;

vector< vector<string> > Input; //The main Input dataset
vector< vector<int> > Dataset;  //The hashed dataset
vector<string> items;
//set<string> items;
vector<int> result;
float mincount;

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

bool IsSubset(std::vector<int> A, std::vector<int> B)
{
    std::sort(A.begin(), A.end());
    std::sort(B.begin(), B.end());
    return std::includes(A.begin(), A.end(), B.begin(), B.end());
}

int calc_freq(vector<int> v)
{
  int answer=0;
  for(int i=0;i<Dataset.size();i++)
  {
    if(IsSubset(Dataset[i],v))
      answer++;
  }
  return answer;
}

vector< vector<int> > calc(vector< vector<int> > itemset)
{
  vector< vector<int> > answer;
  for(int i=0;i<itemset.size();i++)
  {
    for(int j=i+1;j<itemset.size();j++)
    {
      vector<int> s1=itemset[i];
      s1.erase(s1.end()-1);
      vector<int> s2=itemset[j];
      s2.erase(s2.end()-1);
      if((s1.size()==0 && s2.size()==0) || s1==s2)
      {
        vector<int> temp=s1;
        temp.push_back(itemset[i][itemset[i].size()-1]);
        temp.push_back(itemset[j][itemset[j].size()-1]);
        int freq = calc_freq(temp);
        if(freq>=mincount)
        {
          answer.push_back(temp);
        }
      }
    }
  }
  return answer;
}


int main()
{
  string temp,line,input,output;
  int i;
  vector<string> lines;
  float confidence,support,flag;
  ifstream myfile("config.csv");  //Read from config file
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
    support=0.001;
    //ifstream inputfile(input.c_str());  //Read the input file
    ifstream inputfile("TextbookInput.csv");
    //ifstream inputfile("inp.csv");
    if(inputfile.is_open())
    {
      while(getline(inputfile, line))
      {
        lines = split(line, ',');
        Input.push_back(lines);
        for(int i=0;i<lines.size();i++)
        {
          //items.insert(lines[i]);
          if (find(items.begin(), items.end(), lines[i]) == items.end())
            items.push_back(lines[i]);  //Make a set of all items in the dataset
        }
        lines.clear();
      }
    }
    else
      cout << "Unable to open input file\n";
    for(int i=0;i<Input.size();i++) //Create the map of the dataset
    {
      vector<int> temp;
      Dataset.push_back(temp);
      for(int j=0;j<Input[i].size();j++)
      {
        Dataset[i].push_back(0);
        for(int k=0;k<items.size();k++)
        {
          if(Input[i][j]==items[k])
          {
              Dataset[i][j]+=k;
              break;
          }
        }
        //cout << Dataset[i][j] << " ";
      }
      //cout << "\n";
    }
    int count[items.size()+1]={0};
    for(int i=0;i<Dataset.size();i++) //Find the count of each item
    {
      for(int j=0;j<Dataset[i].size();j++)
      {
        count[Dataset[i][j]]++;
      }
    }
    cout << "support-->" << support*Dataset.size() << "\n";
    mincount=(float)support*Dataset.size(); //The minimum count to be a frequent itemset
    vector< vector<int> > itemset;
    for(int i=0;i<items.size();i++)
    {
      if((float)count[i]>=(float)support*Dataset.size())
      {
        cout << items[i] << "\n";
        result.push_back(i);  //Frequent items of length 1
      }
    }

    //int second[result.size()+1][result.size()+1]={0};
    vector< vector<int> > second;
    vector<int> temp;
    for(int i=0;i<result.size();i++)
    {
      second.push_back(temp);
      for(int j=0;j<result.size();j++)
      {
        //second[i][j]=0;
        second[i].push_back(0);
      }
    }
    for(int i=0;i<result.size();i++)
    {
      for(int j=i+1;j<result.size();j++)
      {
        for(int k=0;k<Dataset.size();k++)
        {
          if(IsSubset(Dataset[k],vector<int> (result[i],result[j])))
          {
            second[i][j]++;
          }
        }
      }
    }
    for(int i=0;i<result.size();i++)
    {
      for(int j=0;j<result.size();j++)
      {
        if(second[i][j]>=mincount )
        {
          cout << items[result[i]] << "," << items[result[j]] << "\n";  //Frequent itemsets of length 2
          vector<int> temp;
          temp.push_back(result[i]);
          temp.push_back(result[j]);
          itemset.push_back(temp);
        }
      }
    }
    //cout << items.size() << " " << result.size() << " " << itemset.size() << "\n";
    //exit(0);
    while(true) //For frequent itemsets of higher lengths
    {
      vector< vector<int> > gotanswer=calc(itemset);
      for(int i=0;i<gotanswer.size();i++)
      {
        for(int j=0;j<gotanswer[i].size();j++)
        {
          cout << items[gotanswer[i][j]] << " ";
        }
        cout << "\n";
      }
      if(gotanswer.size()==0)
        break;
      itemset.clear();
      itemset=gotanswer;
    }
  }
  else
    cout << "Unable to open config file\n";
  return 0;
}
