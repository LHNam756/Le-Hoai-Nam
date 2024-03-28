#include <iostream>
#include <string>



using namespace std;
#define MAX 100

int main(int argc, char** argv)
{

    int beerLevel = 0, bobLevel = 0;
    string keyPress = "";
    cout << "beer: " << beerLevel << "bob: " << bobLevel << endl;
    do
    {
        keyPress = "";

        while(cin>>keyPress)
        {

            int tmp = keyPress.length();
            beerLevel = beerLevel + tmp;
            bobLevel = bobLevel + tmp*2;
            cout << "beer: " << beerLevel << "bob: " << bobLevel << endl;
            if(bobLevel > MAX || beerLevel >= MAX)
            {
                break;
            }
            cout << "beer: " << beerLevel << "bob: " << bobLevel << endl;
            if(bobLevel > 0 && bobLevel < MAX)
            {
                bobLevel = 0;
            }
            cout << "beer: " << beerLevel << "bob: " << bobLevel << endl;
        }
    }while(!(beerLevel == MAX || bobLevel > MAX));
    if (bobLevel < MAX && beerLevel == MAX)
    {
        cout << "You Win!\n";
    }
    else if (bobLevel > MAX || beerLevel > MAX)
    {
        cout << "You Lose!\n";
    }
    return 0;


}
