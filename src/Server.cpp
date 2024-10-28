#include <iostream>
#include <string>

bool match_pattern_recursize(std::string input_line, std::string pattern);
bool match_pattern(const std::string& input_line, const std::string& pattern);




int main(int argc, char* argv[]) {
    // Flush after every std::cout / std::cerr
    std::cout << std::unitbuf;
    std::cerr << std::unitbuf;

    // You can use print statements as follows for debugging, they'll be visible when running tests.
    std::cout << "Logs from your program will appear here" << std::endl;

    if (argc != 3) {
        std::cerr << "Expected two arguments" << std::endl;
        return 1;
    }

    std::string flag = argv[1];
    std::string pattern = argv[2];

    if (flag != "-E") {
        std::cerr << "Expected first argument to be '-E'" << std::endl;
        return 1;
    }


    // Uncomment this block to pass the first stage
    //
    std::string input_line;
    std::getline(std::cin, input_line);
    //
    try {
    	if (match_pattern(input_line, pattern)) {
             return 0;
         } else {
             return 1;
         }
     } catch (const std::runtime_error& e) {
         std::cerr << e.what() << std::endl;
         return 1;
     }
}

bool match_pattern_recursize(std::string input_line, std::string pattern) {
    if (pattern.empty()){
    	return true;
    }
    if (pattern[0] == ' ') {
        if (input_line[0] == ' ') {
            return match_pattern_recursize(input_line.substr(1, input_line.size()-1), pattern.substr(1, pattern.length()-1));
        }
        return false;
    }

    if (pattern[0] == '\\' && pattern[1] == 'd') {
        if (isdigit(input_line[0])) {
            return match_pattern_recursize(input_line.substr(1, input_line.size()-1), pattern.substr(2, pattern.length()-1));
        }
        return false;
    }

    if (pattern[0] == '\\' && pattern[1] == 'w') {

        if (isalnum(input_line[0])) {

            return match_pattern_recursize(input_line.substr(1, input_line.size()-1), pattern.substr(2, pattern.length()-1));
        }
        return false;
    }
    else {
        if (input_line[0] == pattern[0]) {

            return match_pattern_recursize(input_line.substr(1, input_line.length()-1), pattern.substr(1, pattern.length()-1));

        }
    }

    return false;
}




bool match_pattern(const std::string& input_line, const std::string& pattern) {
	if (pattern.length() == 1) {
        return input_line.find(pattern) != std::string::npos;
    }else if(pattern=="\\d"){
    	for(const auto& a: input_line){
    		if (isdigit(a)){
    			return true;
    		}
    	}
    	return false;
    }else if(pattern=="\\w"){
    	for(const auto &a:input_line){
    		if(isdigit(a) ||isalpha(a)){
    			return true;
    		}
    	}
    	return false;
    }else if (pattern.at(0) == '[' && pattern.at(pattern.length() - 1) == ']' && pattern.at(1)!='^') {
        for (const auto &l : pattern.substr(1, pattern.length() - 2)) {
            if (input_line.find(l) != std::string::npos) {
                return true;
            }
        }
        return false;
    }else if (pattern.at(0) == '[' && pattern.at(pattern.length() - 1) == ']' && pattern.at(1)=='^') {
        for (const auto &l : pattern.substr(1, pattern.length() - 2)) {
            if (input_line.find(l) != std::string::npos) {
                return false;
            }
        }
        return true;
    }else if (pattern.length() > 2 && pattern[0] == '\\') {

	        int i = 0;



	        while (i < input_line.length()) {

	            if (match_pattern_recursize(input_line.substr(i, input_line.length()-1), pattern)) return true;

	            i++;

	        }
	    }
    if (pattern.length() > 1 && pattern[0] == '^') {

        return match_pattern_recursize(input_line, pattern.substr(1, pattern.length()-1));

    }
	    return false;
}


