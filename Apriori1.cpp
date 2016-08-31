#include <map>
#include <set>
#include <list>
#include <cmath>
#include <ctime>
#include <deque>
#include <queue>
#include <stack>
#include <string>
#include <bitset>
#include <cstdio>
#include <limits>
#include <vector>
#include <climits>
#include <cstring>
#include <cstdlib>
#include <fstream>
#include <numeric>
#include <sstream>
#include <iostream>
#include <algorithm>

using namespace std;

typedef struct node{
	long long int val;
	long long int frequency_of_val;
	vector<node*> children;
}node;


long long int binary_search(vector<long long int> array,long long int data,long long int start,long long int end)
{
	if (start>end)
		return -1;
	if (end==start)
		if (array[start]==data)
			return start;
		else
			return -1;
	long long int mid = (start+end)/2;
	if (array[mid]==data)
		return mid;
	else if (array[mid]>data)
		return binary_search(array,data,start,mid-1);
	else if (array[mid]<data)
		return binary_search(array,data,mid+1,end);
}



vector< vector<string> > read_file(string filename)
{
	FILE *config;
	config = fopen(filename.c_str(),"rt");
	vector< vector<string> > config_file;
	if(config)
	{
		char line[1024];
		int count = 0;
		while(fgets(line,sizeof line,config)!=NULL)
		{
			vector<string> a;
			char * fields = strtok (line,",\n");
			while(fields!=NULL)
			{
				a.push_back(fields);
				fields = strtok(NULL,",\n");
			}
			if (a.size()!=0)
				config_file.push_back(a);
			count+=1;
		}
		fclose(config);
	}
	return config_file;
}

vector<string > read_file_as_array(string filename)
{
	FILE *config;
	config = fopen(filename.c_str(),"rt");
	vector<string> a;
	if(config)
	{
		char line[1024];
		int count = 0;
		while(fgets(line,sizeof line,config)!=NULL)
		{
			char * fields = strtok (line,",\n");
			while(fields!=NULL)
			{
				a.push_back(fields);
				fields = strtok(NULL,",\n");
			}
			count+=1;
		}
		fclose(config);
	}
	return a;
}

void print_2d_array(vector< vector<long long int> > a)
{
	for (int i = 0; i <a.size(); i++)
	{
		for (int i1 = 0; i1 < a[i].size();i1++)
			cout<<a[i][i1]<<" ";
		cout<<endl;
	}
}

void print_1d_array(vector<long long int> a)
{
	for (int i = 0; i <a.size(); i++)
		cout<<a[i]<<" ";
	cout<<endl;
}


//to get frequency of any data set of any size
long long int frequency(vector<long long int> element,vector<vector<long long int> > input)
{
	long long int count = 0,final_count=0;
	for (int i = 0; i < input.size();i++)
	{
		count = 0;
		for (int j=0;j<element.size();j++)
		{
			if (binary_search(input[i],element[j],0,input[i].size()-1)!=-1)
				count++;
			else{
				break;
			}
		}
		if (count==element.size())
			final_count++;
	}
	return final_count;
}

//return if two item set have same prefix
bool prefix(vector<long long int> a,vector<long long int> b)
{
	if (a.size()!=b.size())
		return false;
	int i=0;
	while(i < a.size()-1)
	{
		if (a[i]!=b[i])
			return false;
		i++;
	}

	return true;
}

long long int search(node * head,long long int val,long long int start,long long int end)
{
	cout<<head->val<<endl;
	if (start>end)
		return -1;
	if (end==start)
		if (head->children[start]->val==val)
			return start;
		else
			return -1;
	long long int mid = (start+end)/2;
	if (head->children[mid]->val==val)
		return mid;
	else if (head->children[mid]->val>val)
		return search(head,val,start,mid-1);
	else if (head->children[mid]->val<val)
		return search(head,val,mid+1,end);

}

node * insert(node * head,vector<long long int> value,long long int count)
{
	node *temp_head = head;
	long long int length_of_child = temp_head->children.size()-1;
	cout<<"inserting at node:	"<<temp_head->val<<"having count "<<length_of_child<<endl;
	print_1d_array(value);
	if (value.size()==0)
		return head;
	long long int search_value = search(temp_head,value[0],0,length_of_child);
	if (search_value==-1)
	{
		node *temp=(node*)malloc(sizeof(node));
		temp->val = value[0];
		// temp->frequency_of_val = count;
		temp_head->children.resize(1);
		temp_head->children.push_back(temp);
		// cout<<temp_head->children.size()<<endl;
		// temp_head->children.push_back(temp);
		//check the order while inserting
		return head;
	}
	else
	{
		vector<long long int> val_temp(value.begin()+1,value.end());
		temp_head->frequency_of_val+=count;
		temp_head->children[search_value] = insert(temp_head->children[search_value],val_temp,count);
		return head;
	}
}

node * find_frequent_items_of_size_2(vector<vector<long long int> > frequent_items,vector< vector<long long int> > input_data,long long int min_support,node * head)
{
	if (frequent_items.size()==0)
		return head;
	// cout<<"here :	"<<frequent_items.size()<<endl;
	// cout<<"start"<<endl;
	long long int count;
	vector<vector<long long int> > next_frequent_items;
	for (int i = 0; i < frequent_items.size();i++)
	{
		for (int j = i+1; j < frequent_items.size();j++)
		{
			if (prefix(frequent_items[i],frequent_items[j]))
			{
				vector<long long int> union_of_both = frequent_items[i];
				// union_of_both.swap(frequent_items[i]);
				union_of_both.push_back(frequent_items[j][frequent_items[j].size()-1]);
				count = frequency(union_of_both,input_data);
				if (count>=min_support)
				{
					head = insert(head,union_of_both,count);
					next_frequent_items.push_back(union_of_both);
				}
			}
		}
	}
	// print_2d_array(frequent_items);
	// cout<<"break"<<endl;
	// cout<<next_frequent_items.size()<<endl;
	// print_2d_array(next_frequent_items);
	// cout<<"end"<<endl;
	head = find_frequent_items_of_size_2(next_frequent_items,input_data,min_support,head);
	return head;
}


node * find_frequent_items_of_size_1(vector<long long int> input,vector<vector<long long int> > input_data_2d,long long int min_support,node *head)
{
	node *temp = head;
	vector<vector<long long int> > frequent_items;
	long long int i = 0;
	while(i<input.size())
	{
		long long int count = 0;
		while(i<input.size() && input[i]==input[i+1])
		{
			i+=1;
			count+=1;
		}
		count+=1;
		if (count>=min_support)
		{
			vector<long long int> waste;
			waste.push_back(input[i]);
			frequent_items.push_back(waste);
			// node *temp1=(node*)malloc(sizeof(node));
			// temp1->val = input[i];
			// temp1->frequency_of_val = count;
			// temp->children.push_back(temp1);
			temp = insert(temp,waste,count);
		}
		i+=1;
	}
	// print_2d_array(frequent_items);

	temp = find_frequent_items_of_size_2(frequent_items,input_data_2d,min_support,temp);

	return head;
}

vector<string> hash_data(vector<string> input_data)
{
	vector<string> hash;
	for (int i = 0; i < input_data.size();i++)
	{
		if (find(hash.begin(),hash.end(),input_data[i])==hash.end())
			hash.push_back(input_data[i]);
	}
	return hash;
}

vector<long long int> convert1d(vector<string> input_data,vector<string> hash)
{
	vector<long long int> input_data_int;
	for (int i = 0; i < input_data.size();i++)
		input_data_int.push_back(find(hash.begin(),hash.end(),input_data[i])-hash.begin());
	return input_data_int;
}

vector<vector<long long int> > convert2d(vector<vector<string> > input_data,vector<string> hash)
{
	vector<vector<long long int> > input_data_2d_int;
	for (int i = 0; i < input_data.size();i++)
	{
		vector<long long int > waste;
		for (int j = 0; j < input_data[i].size();j++)
			waste.push_back(find(hash.begin(),hash.end(),input_data[i][j])-hash.begin());
		input_data_2d_int.push_back(waste);
	}
	return input_data_2d_int;
}

int main(int argc, char const *argv[])
{
	node *head=(node*)malloc(sizeof(node));
	head->val = -1;
	head->frequency_of_val = 0;
	vector< vector<string> > config_file,input_data_2d;
	vector<string> input_data;
	string filename = "config.csv";
	config_file = read_file(filename);

	//read the input as it is
	input_data_2d = read_file(config_file[0][1]);

	float x = atof(config_file[2][1].c_str());
	float y = input_data_2d.size();
	y = y *x;
	long long int min_support = (long long int)y;
	min_support = 1;
	// cout<<min_support<<endl;


	input_data = read_file_as_array(config_file[0][1]);
	sort(input_data.begin(),input_data.end());
	//convert the given string to int

	//make a hash
	vector<string> hash = hash_data(input_data);

	for (int i = 0; i < hash.size(); ++i)
		cout<<i<<"	"<<hash[i]<<endl;

	vector<long long int> input_data_int = convert1d(input_data,hash);
	vector<vector<long long int> > input_data_2d_int = convert2d(input_data_2d,hash);


	head = find_frequent_items_of_size_1(input_data_int,input_data_2d_int,min_support,head);

	// print_head()
	return 0;
}
