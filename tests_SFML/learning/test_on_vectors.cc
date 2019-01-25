#include <vector>
#include <iostream>
#include <exception>

using namespace std;

int main(){

    vector<string> intVector;

    try{
        intVector.push_back(NULL);
    } catch (exception const &ex1) {
        cerr << "Erreur : " << ex1.what() << endl;
    }
    try{
        intVector.push_back(NULL);
    } catch (exception const &ex1) {
        cout << "Erreur : " << ex1.what() << endl;
    }
    try{
        intVector.push_back(NULL);
    } catch (exception const &ex1) {
        cout << "Erreur : " << ex1.what() << endl;
    }

    try{
        intVector.push_back("a");
    } catch (exception const &ex2) {
        cout << "Erreur : " << ex2.what() << endl;
    }
    try{
        intVector.push_back("b");
    } catch (exception const &ex2) {
        cout << "Erreur : " << ex2.what() << endl;
    }
    try{
        intVector.push_back("it's real nigga hour's");
    } catch (exception const &ex2) {
        cout << "Erreur : " << ex2.what() << endl;
    }
    int i = 1;
    for (vector<string>::iterator it = intVector.begin(); it != intVector.end(); it++){
        cout << i++ << " : " << (*it) << endl;
    }

    return 0;
}
