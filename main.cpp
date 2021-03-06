#include <fstream>
#include <iostream>
#include <ctime>
#include "gen.h"

//#define DEBUG

using namespace std;

clock_t start,st;


int sumUsed =0;
int sumNUsed =0;
string DNA;
int n,k;
vector<string> chip, nchip,rn,r;
map<string, vector<string> > mchip;
map<string, vector<string> >::const_iterator itr;
map<string, int>::iterator itr2;
map<string, int>::const_iterator itr3;
vector<string> notused;
vector<vector<string> > canditates;

bool reverted = false;
bool stop = true;
bool flag;
string current;
vector<string> rev;
vector<string> solutions;
map<string,int> used, usedn;
string solution;

void printINFO() {

   cout << "current: " << current << endl;
    
    //   cout << "solution[" << solution.length() << ":" << solution << endl;
  //  cout << "getLast: " << getlast(solution,k) << endl;
/*    cout << "-----------used-----------" << endl;
    for(itr3 = used.begin(); itr3!=used.end(); ++itr3)
        cout << itr3->first << "::" << itr3->second << endl;
    cout << "--------------------------" << endl;
    cout << "-----------usedn-----------" << endl;
    for(itr3 = usedn.begin(); itr3!=usedn.end(); ++itr3)
        cout << itr3->first << "::" << itr3->second << endl;
    cout << "--------------------------" << endl;
   */ 
    cout << "-----------CANDIDATES------------" << endl;
    if(canditates.size()>0){
    for(int i=0;i<canditates.back().size();i++)
        cout << canditates.back()[i] << "::";
    cout <<endl;
    }
    cout << "--------------------------" << endl;

    }

void get_initUsed() {
map<string, vector<string> >::const_iterator itr;
    for(itr = mchip.begin(); itr!=mchip.end(); ++itr) {
        used.insert(pair<string, int >((*itr).first,0));
    }
}

void get_initUsedN() {
    for(int i=0; i<nchip.size(); i++){
        usedn.insert(pair<string, int >(nchip[i],0));
    }
}
//veryfikacja z częscią nieklasyczną chipu
bool verifyN(string cur) {
    if(solution.length()<2*k-1) return true;
    for(itr3=usedn.begin(); itr3!=usedn.end(); ++itr3) {
        if(itr3->second==0 || find(rn,itr3->first))
        {
            if(cur[cur.length()-1]==itr3->first[itr3->first.length()-1]
                    && solution.substr(solution.length()-2*k+2, k-1)==itr3->first.substr(0,k-1))
            {
                return true;
            }
        }
    }

    return false;
}


bool verify(string cur) {
    if(used[cur]==0 || find(r,cur))
    {
        return verifyN(cur);
    } else {
        return false;
   }
}
//generowanie kandydatow
bool getCandidates(string cur) {
    if(reverted) return true;
    vector<string> tmp;
    for(int i=0; i<mchip[cur].size(); i++)
    {
        if(verify(mchip[cur][i])) {
            tmp.push_back(mchip[cur][i]);
        }
    }
    canditates.push_back(tmp);
    if(tmp.size()==0)
        return false;
    else
        return true;
}

bool check(){

if(k-1+sumUsed+sumNUsed > n)
    return false;
else
    return true;


}

//test rozwiązania
bool test() {
    for(itr3 = used.begin(); itr3!=used.end(); ++itr3)
    {
        if(itr3->second==0)
            return false;
    }
    for(itr3 = usedn.begin(); itr3!=usedn.end(); ++itr3)
    {
        if(itr3->second==0 && find(nchip,itr3->first))
            return false;
    }
    return true;
}
//nawrót
bool revert() {
    reverted = true;

   //    if(canditates.back().size()==0) {
        canditates.pop_back();
        used[current]--;
        sumUsed--;
        sumNUsed++;
        usedn[getlast(solution,k)]--;
        rev.pop_back();
        current=rev.back();
        solution = solution.substr(0,solution.length()-1);
        canditates.back().pop_back();
        return true;
 //   }
    
    
}

bool revertspec(){
    reverted = true;
        sumUsed--;
        sumNUsed++;
        //canditates.pop_back();
        canditates.back().pop_back();
        rev.pop_back();
        used[current]--;
        current=rev.back();
        usedn[getlast(solution,k)]--;
        flag=true;
        solution = solution.substr(0,solution.length()-1);
        return true;





}



void  alg() {
    current = DNA.substr(0,k);
    solution = current;
    rev.push_back(current);
    used[current]++;
    while(stop) {
        #ifdef DEBUG
        //cout << "-------------_STEP -------" <<endl;
        printINFO();
        #endif

        //cout << rev.size() << endl;
        if(getCandidates(current)) {
 
            
            if(canditates.back().size()>0) {
                current = canditates.back().back();
                rev.push_back(current);
                used[current]++;
                sumUsed++;
                sumNUsed--;
                solution+=current[current.length()-1];
                usedn[getlast(solution,k)]++;
                reverted = false;
                if(solution.length() ==n) {
                    if(test()) {
                        solutions.push_back(solution);
                    revertspec(); 
                    } else {

                        #ifdef DEBUG
                        cout << "false test revert" <<endl;
                        #endif
                    
                        revertspec();
                    }
                }else{
                   if(!check())
                        revertspec();
                }
            }
            else {
                if(canditates.size()==1 && canditates.back().size()==0) break;
                #ifdef DEBUG
                cout << "no canditates in past revert" << endl;
                #endif
                revert();
            }
        }
        else {
            #ifdef DEBUG
            cout << "no canditates revert" << endl;
            #endif
            revert();
        }
    }
}


int main(int argc, char *argv[])
{
    ifstream is;
    is.open(argv[1]);

    is >> n;
    is >> k;
    is >> DNA;

    is.close();

    get_chip(chip, DNA, n, k);
    get_nchip(nchip, DNA, n, k);
    make_chip(mchip, r, chip,n,k);
    check_rep(rn,r,nchip);

    get_initUsed();
    get_initUsedN();

start = clock();
    alg();
st = clock();
cout << "Time elapsed " << (double) (st - start) / CLOCKS_PER_SEC << endl;
/*    for(itr=mchip.begin();itr!=mchip.end();++itr){
        cout << itr->first << "::" ;
        for(int i =0;i < itr->second.size();i++)
            cout << itr->second[i] << "-" ;
        cout << endl;

    }

*/


    string res = DNA.substr(0,n);
    
    for(int i =0 ; i<solutions.size(); i++)
    
    {
        cout << solutions[i].length() << endl;
        cout << solutions[i] << endl;
        if(res==solutions[i])
            cout << "+++++++++++++OK+++++++++++++" << endl;
        else {
            cout << "error" << endl;
        }


    }


    chip.clear();
    nchip.clear();
    rn.clear();

    vector<string>().swap(chip);
    vector<string>().swap(nchip);
    vector<string>().swap(rn);
    mchip.clear();

    return 0;
}


