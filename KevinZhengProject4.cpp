#include <vector>
#include <iostream>
#include <string>
using namespace std;
void Max(string str,int& beg,int& end){ 
    int maxLen = 1,start = beg;
    int left,right;
    for(int i = beg;i <= end;i++){
        int oddLen = 1;
        left = i-1;
        right = i+1;
        while(left >= beg && right <= end && str[left] == str[right]){
            left--;
            right++;
            oddLen += 2;
        }
        if(oddLen > maxLen){
            maxLen = oddLen;
            start = left+1;
        }
        left = i;
        right = i+1;
        int evenLen = 0;
        while(left >= beg && right <= end && str[left] == str[right]){
            left--;
            right++;
            evenLen += 2;
        }
        if(evenLen > maxLen){
            maxLen = evenLen;
            start = left+1;
        }
    }
    beg = start;
    end = start + maxLen - 1;
}
int index = 0;
string all = "";
void Pipe(string str,int& beg,int& end){
    int lbeg = beg;
    int rend = end;
    Max(str,beg,end);
    int lend = beg - 1;
    int rbeg = end + 1;
    if(lbeg <= lend){
        Pipe(str,lbeg,lend);
    }
    if(index == 0){
        all = all +str.substr(beg,end-beg+1);
        index++;
    }
    else{
        all = all +"|"+ str.substr(beg,end-beg+1);
        index++;
    }
    if(rbeg <= rend){
        Pipe(str,rbeg,rend);
    }
}
int findMin(string s){
    int n = s.size();
    vector<vector<bool>> TTF(n, vector<bool>(n, false)); 
    vector<int> re(n+1, 0); 
    for (int i = 0; i <= n; i++)  
        re[i] = i - 1;
    for (int i = 1; i < n; i++) { //forward
        for (int j = i; j >= 0; j--) { //backward
            if (s[i] == s[j] && (i - j < 2 || TTF[j + 1][i - 1])) {  
                TTF[j][i] = true;
                re[i+1] = min(re[i+1], re[j] + 1);
            }
        }
    }
    return re[n]; //cuts
}
int main(){
    string s;
    while(cin >> s){
    int begin=0;
    int end = s.length()-1;
    int min = findMin(s);
    if (min==0){
        cout << min <<" "<<s<<endl;
    }
    else{
        cout<< min <<" ";
        Pipe(s,begin,end);
        if(all.substr(0,1)=="|"){
            cout<<all.substr(1,all.length());
            all="";
        }
        cout<<all<<endl;
        all ="";
    }
}
    return 0;
}
