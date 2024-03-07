#include <iostream>
#include <fstream>
#include <string>


using namespace std;

string inputFile(char* nameFile);
string gameInit(char* nameFile, int& numFalse, int& numTrue);
void gamestatus(string secretword, const char& playerGuess, int& numFalse, int& numTrue);
char guess();
void render();
void displayResult(string result);


int main()
{
    int numFalse, numTrue;
    string secretWord;
    char playerGuess;
    /*
    Khởi tạo: máy nghĩ từ tiếng Anh, số đếm lần đoán sai, đúng
    Nhập liệu: phán đoán của người chơi
    Cập nhật: xử lý kết quả đoán và thay đổi trạng thái trò chơi
    Hiển thị trạng thái trò chơi: người trên giá treo và secretWord
    Thông báo kết quả trò chơi*/
    secretWord = gameInit("words.txt", numFalse, numTrue);
    playerGuess = guess();
    gamestatus(secretWord, playerGuess, numFalse, numTrue);
    render();
    displayResult(secretWord);
    return 0;
}

string inputFile(char* nameFile)
{
    ifstream FILE;
    FILE.open(nameFile);
    if(FILE.fail())
    {
        cerr << "ERROR OPENING FILE!" << endl;
        exit(0);
    }
    string word;
    FILE >> word;
    FILE.close();
    return word;

}
 string gameInit(char* nameFile, int& numFalse, int& numTrue)
 {
     string SecretWord = inputFile(nameFile);
     numFalse = 5;
     numTrue = 0;
     return SecretWord;

 }

 void displayResult(string result)
 {
     cout << result << endl;
 }

 char guess()
 {
     char wordGuess;
     cin >> wordGuess;
     cout << wordGuess;
     return wordGuess;
 }

 void render()
 {

 }

void gamestatus(string secretWord,const char& playerGuess, int& numFalse, int& numTrue)
{
    //find index char in word;
    int len = secretWord.length();
    int flat = 0;
    for(int i = 0; i < len; i++)
    {
        flat = 0;
        if (playerGuess == secretWord[i])
        {
            flat = 1;
            break;
        }
    }
    (flat == 1)? numTrue++ : numFalse--;
    cout << "numTrue: " << numTrue << " numFalse: " << numFalse;

}
