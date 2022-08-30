#ifndef tokenize_h_RPK
#define tokenize_h_RPK

#include<vector>
#include<string>
#include<iostream>

class Tokenize{
	public:
		static std::vector<std::string> tokenize(std::string s,std::string delim=" "){
			size_t pos = 0;
			std::vector<std::string> tokens;// = new std::vector<std::string>();
			while((pos=s.find(delim)) != std::string::npos){
				tokens.push_back(s.substr(0,pos));
				s.erase(0,pos+delim.length());
			}
			tokens.push_back(s);
			return tokens;
		}

		static std::string toLowercase(std::string s){
			for(int i = 0;i<s.length();i++){
				if(s.at(i) <= 90 && s.at(i) >= 65){
					s.at(i) = s.at(i) + 32;
				}
			}
			return s;
		}

		static bool contains(std::string big, char small){
			for(auto e:big){
				if(e==small){
					return true;
				}
			}
			return false;
		}
};

#endif
