#include "gen.h"

string getlast(string solution, int k) {
    string out;
    if(solution.length()<2*k-1) return "";
    out = solution.substr(solution.length()-2*k+1, k-1);
    for(int i=0; i<k-1; i++)
        out+="x";
    out += solution[solution.length()-1];
    return out;

}





void check_rep(vector<string>& rn, vector<string>& r, const vector<string>& nchip) {
    rn = nchip;
    bool flag=false;
    for(int i=0; i<rn.size(); i++) {
        flag =false;
        for(int j=0; j<rn.size(); j++) {
            if(i==j) continue;
            if(rn[i]==rn[j]) {
                rn.erase(rn.begin()+j);
                j--;
                flag=true;
            }

        }
        if(!flag) {
            rn.erase(rn.begin()+i);
            i--;
        }
    }
    flag=false;
    for(int i=0; i<r.size(); i++) {
        flag =false;
        for(int j=0; j<r.size(); j++) {
            if(i==j) continue;
            if(r[i]==r[j]) {
                r.erase(r.begin()+j);
                j--;
                flag=true;
            }

        }
        if(!flag) {
            r.erase(r.begin()+i);
            i--;
        }
    }



}


void get_chip(vector<string>& chip, const string& DNA, int n, int k) {
    for(int i=0; i<n-k+1; i++) {
        chip.push_back(DNA.substr(i,k));

    }
}


void get_nchip(vector<string>& nchip, const string& DNA, int n, int k) {
    for(int i=0; i<n-2*k+2; i++) {
        nchip.push_back(DNA.substr(i,k-1));
        for(int j=0; j<k-1; j++)
            nchip.back()+="x";

        nchip.back()+=DNA.substr(i+2*k-2,1);


    }
}



bool find(vector<string> vec, string c) {
    for(int i=0; i<vec.size(); i++)
        if(vec[i]==c)
            return true;

    return false;

}


void make_chip(map<string, vector<string> >& mchip,  vector<string>& r,  vector<string>& chip,
        int n,int k ) {
    vector<string> tmp;
    for(int i=0; i<n-k+1; i++) {
        tmp.clear();
        for(int j=0; j<n-k+1; j++) {
            if(i==j) continue;

            if(mchip.find(chip[i])==mchip.end()) {
                if(chip[i]==chip[j])

                {

                    if(chip[i].substr(1,k-1) == chip[j].substr(0,k-1) && !find(tmp,chip[j]))
                        tmp.push_back(chip[j]);

                    r.push_back(chip[i]);
                } else {

                    if(chip[i].substr(1,k-1) == chip[j].substr(0,k-1) && !find(tmp,chip[j]))
                        tmp.push_back(chip[j]);

                };

            }

        }
        mchip.insert(pair<string, vector<string> >(chip[i],tmp));
    }

    vector<string>().swap(tmp);
}




