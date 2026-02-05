//UID:24BCS10773

#include <iostream>
using namespace std;
int main(){
    int t;
    cin >> t;
    while(t--){
       int n;
       cin >> n;
       if(n < 5){
            cout << "-1" << endl;
            continue;
       }
        for(int i = 1; i <= n; i += 2){
            if(i == 5) 
              continue;
            cout << i << " ";
        }
        cout << "5 4 ";
        for(int i = 2; i <= n; i +=2){
            if(i == 4)
              continue;
            cout << i << " ";
        }
        cout << endl;
    }
    return 0;
}
