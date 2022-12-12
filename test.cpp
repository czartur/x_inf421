#include <iostream>
#include <regex>
#include <string>
#include <vector>

using namespace std;

int solution(vector<int> A)
{
  vector<int>row;
  for(auto x : A){
    //cout << row.size() << endl;
    if(row.empty()) row.push_back(x);
    else {
      for(int i=0; i<=row.size(); i++){
        if(i == row.size()) row.push_back(x);
        else if(row[i] > x) {row[i] = x; break;}
      }
    }
  }
  return row.size(); 
}

vector<int> toIntVector(string str)
{
  std::vector<int> out;
  std::string i;
  std::istringstream tokenStream(str);
  while (std::getline(tokenStream, i, ','))
  {
    out.push_back(atoi(i.c_str()));
  }
  return out;
}

int main()
{
  // Read in from stdin, solve the problem, and write answer to stdout.
  string AS;
  cin >> AS;
  vector<int> A = toIntVector(AS);
  cout << solution(A);
}
