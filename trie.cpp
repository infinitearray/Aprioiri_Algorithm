#include<bits/stdc++.h>

using namespace std;

struct node
{
  struct node* parent;
  struct node* children[26];
  vector<int> occurences;
};

void InsertWord(struct Node* trie, char* word, int index)
{
  struct node* traverse = trie;
  while(*word!='\0')
  {
    if(traverse->children[*word-'a']==NULL)
    {
        traverse->children[*word-'a']=(struct node*)calloc(1, sizeof(struct node));
        traverse->children[*word-'a']->parent=traverse;
    }
    traverse=traverse->childern[*word='a'];
    ++word;
  }
  traverse->occurences.push_back(index);
}

int main()
{
  return 0;
}
