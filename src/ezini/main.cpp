#include "ezini.h"

#include <iostream>

using namespace std;

int main() {
	ezini::ini file;
	file.Load("D:\\Sources\\cxx\\pub\\ezini\\src\\ezini\\test.ini", "");
	for (auto& i : file.data()) {
		for (auto& j : i.second){
			cout << '[' << i.first << ']' << j.first << '=' << j.second << endl;
		}
	}
	return 0;
}