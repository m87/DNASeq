#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <fstream>

using namespace std;

string DNA;
int n,k;
vector<string> chip, nchip;
map<string, vector<string> > mchip;
map<string, vector<string> >::const_iterator itr;

void get_chip();
void get_nchip();
void make_chip();

int main(int argc, char *argv[])
{

    ifstream is;
    is.open(argv[1]);

    is >> n;
    is >> k;
    is >> DNA;
    

    get_chip();
    get_nchip();

    make_chip();

    for(itr = mchip.begin(); itr!=mchip.end();++itr){
        cout << (*itr).first << " ";
        for(int i=0; i<(*itr).second.size();i++)
            cout  << (*itr).second[i] << ":";
        cout << endl;
    }

    for(int i=0;i<n-2*k+2;i++)
        cout << nchip[i] << endl;



    vector<string>().swap(chip);   
    vector<string>().swap(nchip);   
    mchip.clear();
    return 0;
}


void get_chip(){
    for(int i=0;i<n-k+1;i++){
       chip.push_back(DNA.substr(i,k)); 
 
    }
}


void get_nchip(){
    for(int i=0;i<n-2*k+2;i++){
       nchip.push_back(DNA.substr(i,k-1));
       for(int j=0;j<k-1;j++)
           nchip.back()+="x";

        nchip.back()+=DNA.substr(i+2*k-2,1);

    }
}

void make_chip(){
    vector<string> tmp;
    for(int i=0;i<n-k+1;i++){
        tmp.clear();
        tmp.push_back("-");
        for(int j=0; j<n-k+1;j++){
            if(i==j) continue;
            
            if(mchip.find(chip[i])==mchip.end()){
                if(chip[i]==chip[j])
                {
                    tmp[0]="o";
                }else{

                    if(chip[i].substr(1,k-1) == chip[j].substr(0,k-1))
                        tmp.push_back(chip[j]);

                };

            }

        }
        mchip.insert(pair<string, vector<string> >(chip[i],tmp));        
    }

}

