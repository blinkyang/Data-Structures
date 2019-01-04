#include <iostream>
#include <unordered_map>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;
vector<vector<string>> findAnagrams(const vector<string>& dict);

int main()
{
  vector<string> word_list = {"debitcard", "elvis", "silent", "badcredit", "lives", "freedom","listen", "levis"};
   vector<vector<string>> result = findAnagrams(word_list);
   for (auto anagrams: result) {
      for (auto words: anagrams)
         cout << words << " ";
         cout << endl;
    }
   return 0;
}

vector<vector<string>> findAnagrams(const vector<string>& dict)
{
    vector<string> dict2 = dict; //Copying input character array into buffer array
    vector<vector<string>> out;  //Output 2D vector
    unordered_multimap<int, string> umap; //Unordered map for Hash map
    hash<string> strHash;                 //Base string Hash function

    for (int i = 0; i < dict.size(); i++)  //Sorting buffer array
    {
        sort(dict2[i].begin(), dict2[i].end());
    }

     for (int i = 0; i < dict.size(); i++)  //putting elements of original into Hash map according to sorted buffer
    {
        umap.insert({strHash(dict2[i]),dict[i]});
    }

    for ( int i = 0; i < umap.bucket_count(); i++) //Importing from hash map and inputing into 2D vector
    {
        out.push_back(vector<string>());
        for (auto x = umap.begin(i); x != umap.end(i); x++)
        out[i].push_back(x->second);
    }

        return out;
}
