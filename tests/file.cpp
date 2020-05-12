#include <iostream>
#include <fstream>
#include <string>
#include <vector>

int main(){
//	std::ifstream file{"automataletras.txt", std::ios::binary};
//	std::vector<unsigned char> buffer(std::istreambuf_iterator<char>(file),{});
//	std::cout << buffer.size();
//	for(auto c: buffer){
//		std::cout<<c;
//	}
	std::string str = "hola";
	std::vector <unsigned char> buffer;
	for(auto c:str)
		buffer.push_back(c);
	std::cout<<buffer.size();
}
