#include<bits/stdc++.h>
#include<tr1/unordered_map>
using namespace std;
using namespace tr1;

vector< vector<string> > Input; //The main Input dataset
vector< vector<int> > Dataset;  //The hashed dataset
unordered_map<string, int> umap;
unordered_map<int, string> rmap;
vector<int> result;
float mincount;
int vertices=0;
vector< vector<int> > Solution;

struct node
{
  int frequency;
  //struct node* parent;
  int value;
  struct node** children;
};

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

struct node *createnode()
{
	struct node *temp = NULL;
	temp = (struct node*)malloc(sizeof(struct node));
	if(temp)
	{
		int i;
		//temp->occur = 0;
		temp->value = -1;
    temp->frequency=0;
		temp->children = (struct node**)malloc((umap.size()+1)*sizeof(node*));
		for(i = 0; i <= umap.size(); i++)
		{
			temp->children[i] = NULL;
		}
	}
	return temp;
};

struct node Insert_word(struct node* Trie, vector<int> word, int frequency)
{
  struct node* traverse;
  traverse=Trie;
  vector<int>::iterator it;
  for(it=word.begin();it!=word.end();it++)
  {
    if(!traverse->children[*it])
    {
      traverse->children[*it]=createnode();
    }
    traverse=traverse->children[*it];
    traverse->value=*it;
    //cout << *it<< "------\n";
    
  }
  traverse->frequency=frequency;
  return *Trie;
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

int is_frequent(struct node* Trie, vector<int> vec)
{
  struct node* traverse=Trie;
  for(int k=0;k<vec.size();k++)
  {
    if(traverse->children[vec[k]])
      traverse=traverse->children[vec[k]];
    else
      return -1;
  }
  return 0;
}

int get_freq(struct node* Trie, vector<int> vec)
{
  struct node* traverse=Trie;
  for(int k=0;k<vec.size();k++)
  {
    if(traverse->children[vec[k]])
      traverse=traverse->children[vec[k]];
    else
      return -1;
  }
  return traverse->frequency;
}

vector< vector<int> > calc(vector< vector<int> > itemset,struct node* Trie)
{
  vector< vector<int> > answer;
  int var=0;
  for(int i=0;i<itemset.size();i++)
  {
    for(int j=i+1;j<itemset.size();j++)
    {
      vector<int> s1=itemset[i];
      s1.erase(s1.end()-1);
      vector<int> s2=itemset[j];
      s2.erase(s2.end()-1);
      if(s1==s2)
      {
        vector<int> temp=s1;
        temp.push_back(itemset[i][itemset[i].size()-1]);
        temp.push_back(itemset[j][itemset[j].size()-1]);
        var=0;
        for(int q=0;q<temp.size();q++)
        {
          vector<int> tem = temp;
          tem.erase(tem.begin()+q,tem.begin()+q+1);
          int check=is_frequent(Trie,tem);
          //cout << rmap[itemset[i][itemset[i].size()-1]] << " " << rmap[itemset[j][itemset[j].size()-1]] << " -> " << check <<"\n";
          if(check==-1)
          {
            var=-1;
            break;
          }
        }
        if(var==0)
        {
          int freq = calc_freq(temp);
          if(freq>=mincount)
          {
            answer.push_back(temp);
            Solution.push_back(temp);
            *Trie=Insert_word(Trie, temp, freq);
          }
        }
      }
    }
  }
  return answer;
}


void printer(struct node* Trie)
{
  struct node* traverse;
  traverse=Trie;
  cout << rmap[traverse->value] << "->";
  for(int i=0;i<=16;i++)
  {
    if(traverse->children[i])
    {
      printer(traverse->children[i]);
    }
  }
  cout << "\n";
}

long long int power(long long int a,long long int b)
{
  long long int ans=1;
  for(int i=0;i<b;i++)
    ans*=a;
  return ans;
}

int main()
{
  string temp,line,input,output;
  int i;
  vector<string> lines;
  float confidence,support,flag;
  unordered_map<int, int> counts;

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
    ofstream outputfile(output.c_str());
    ifstream inputfile(input.c_str());  //Read the input file
    //ifstream inputfile("TextbookInput.csv");
    //ifstream inputfile("inp.csv");
    //support=0.01;
    int counter=0;
    set<string> items;
    if(inputfile.is_open())
    {
      while(getline(inputfile, line))
      {
        lines = split(line, ',');
        Input.push_back(lines);
        for(int i=0;i<lines.size();i++)
        {
          items.insert(lines[i]);
        }
        lines.clear();
      }
      set<string>::iterator its;
      for(its=items.begin();its!=items.end();its++)
      {
          umap[*its]=counter;
          rmap[counter]=*its;
          counter++;
      }
      inputfile.close();
    }
    else
      cout << "Unable to open input file\n";
    unordered_map<string, int>:: iterator itr;
    struct node* Trie = createnode();
    for(int i=0;i<Input.size();i++) //Create the map of the dataset
    {
      vector<int> temp;
      Dataset.push_back(temp);
      for(int j=0;j<Input[i].size();j++)
      {
        Dataset[i].push_back(0);
        Dataset[i][j]+=umap[Input[i][j]];
      }
    }
    for(int i=0;i<Dataset.size();i++) //Find the count of each item
    {
      for(int j=0;j<Dataset[i].size();j++)
      {
        counts[Dataset[i][j]]++;
      }
    }
    // for(int i=0;i<counts.size();i++)
    // {
    //   cout << rmap[i] << ":" << counts[i] << " ";
    // }
    // cout << "\n";
    mincount=ceil((float)support*Dataset.size()); //The minimum count to be a frequent itemset
    vector< vector<int> > itemset;
    unordered_map<int,int> mapping;
    for(int i=0;i<umap.size();i++)
    {
      if((float)counts[i]>=mincount)
      {
        result.push_back(i);  //Frequent items of length 1
        mapping[i]=result.size()-1;
        //  cout << rmap[i] << "\n";
        vector< int> temp;
        temp.push_back(i);
        Solution.push_back(temp);
        *Trie=Insert_word(Trie, temp, counts[i]);
      }
    }
    itemset.clear();
    vector< vector<int> > second;
    vector<int> temp;
    for(int i=0;i<result.size();i++)
    {
      second.push_back(temp);
      for(int j=0;j<result.size();j++)
      {
        second[i].push_back(0);
      }
    }
    // for(int i=0;i<Dataset.size();i++)
    // {
    //   for(int j=0;j<Dataset[i].size();j++)
    //   {
    //     for(int k=j+1;k<Dataset[i].size();k++)
    //     {
    //       if(counts[Dataset[i][j]]>=mincount && counts[Dataset[i][k]]>=mincount)
    //       {
    //         second[mapping[Dataset[i][j]]][mapping[Dataset[i][k]]]++;
    //       }
    //     }
    //   }
    // }

    /**/

    for(int i=0;i<result.size();i++)
    {
      for(int j=i+1;j<result.size();j++)
      {
        for(int k=0;k<Dataset.size();k++)
        {
          //if(IsSubset(Dataset[k],vector<int> (result[i],result[j])))
          if(find(Dataset[k].begin(), Dataset[k].end(), result[i])!=Dataset[k].end() && find(Dataset[k].begin(), Dataset[k].end(), result[j])!=Dataset[k].end())
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
        //  cout << rmap[result[i]] << "," << rmap[result[j]] << "\n";  //Frequent itemsets of length 2
          vector<int> temp;
          temp.push_back(result[i]);
          temp.push_back(result[j]);
          itemset.push_back(temp);
          Solution.push_back(temp);
          *Trie=Insert_word(Trie, temp, second[i][j]);
        }
      }
    }
    while(true) //For frequent itemsets of higher lengths
    {
      vector< vector<int> > gotanswer=calc(itemset,Trie);
      // for(int i=0;i<gotanswer.size();i++)
      // {
      //   for(int j=0;j<gotanswer[i].size();j++)
      //   {
      //     cout << rmap[gotanswer[i][j]] << ",";
      //   }
      //   cout << "\n";
      // }
      if(gotanswer.size()==0)
        break;
      itemset.clear();
      itemset=gotanswer;
    }
    outputfile << Solution.size() << "\n";
    for(int i=0;i<Solution.size();i++)
    {
      for(int j=0;j<Solution[i].size()-1;j++)
      {
        outputfile << rmap[Solution[i][j]] << ",";
      }
      outputfile << rmap[Solution[i][Solution[i].size()-1]] << "\n";
    }
    unordered_map<int, string>:: iterator it;
    // for(it=rmap.begin();it!=rmap.end();it++)
    // {
    //   cout << it->first << "->" << it->second << "\n";
    // }
    //cout << "***************\n";
    /////////To find Association rules
    //printer(Trie);
    if(flag==1)
    {
      vector<string> rules;
      for(int i=0;i<Solution.size();i++)
      {
        vector<int> temp=Solution[i];
        vector<int> subs,nosubs;
        long long int len=power(2,temp.size());
        for(long long int i=0;i<len;i++)
        {
          subs.clear(),nosubs.clear(); 
          for(int j=0;j<temp.size();j++)
          {
            if(i&(1<<j))
            {
              subs.push_back(temp[j]);
            }
            else
            {
              nosubs.push_back(temp[j]);
            }
          }
          //subs is a subset
          vector<int>::iterator it;
          float lfreq=(float)get_freq(Trie,subs);
          float freq=(float)get_freq(Trie,temp);
          string s="";
          if(subs.size()!=0 && nosubs.size()!=0 && freq>=ceil(lfreq*confidence))
          {
            for(it=subs.begin();it!=subs.end()-1;it++)
            {
              s+=rmap[*it]+',';
            }
            s+=rmap[*(subs.end()-1)]+",=>,";
            for(it=nosubs.begin();it!=nosubs.end()-1;it++)
            {
              s+=rmap[*it]+",";
            }
             s+=rmap[*(nosubs.end()-1)]+"\n";
             rules.push_back(s);
          }
        }
      }
      outputfile << rules.size() << "\n";
      for(int i=0;i<rules.size();i++)
      {
        outputfile << rules[i];
      }
    }
    outputfile.close();
  }
  else
    cout << "Unable to open config file\n";
  return 0;
}
