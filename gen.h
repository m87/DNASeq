#ifndef GEN_H
#define GEN_H
#include <string>
#include <vector>
#include <map>

using std::string;
using std::vector;
using std::map;
using std::pair;

//using namespace std;

string getlast(string solution, int k);

void check_rep(vector<string>& rn, vector<string>& r, const vector<string>& nchip) ;
void get_chip(vector<string>& chip, const string& DNA, int n, int k) ;
void get_nchip(vector<string>& nchip, const string& DNA, int n, int k) ;
bool find(vector<string> vec, string c);
void make_chip(map<string, vector<string> >& mchip, vector<string>& r,  vector<string>& chip,int n,int k );







#endif


