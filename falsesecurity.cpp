#include <iostream>
#include <map>
#include <vector>
#include <algorithm>

const std::string 
encoder[] = {".-", "-...", "-.-.", "-..", ".", 
             "..-.", "--.", "....", "..", ".---","-.-",
             ".-..", "--", "-.", "---", ".--.", 
             "--.-", ".-.", "...", "-", "..-",
             "...-", ".--", "-..-", "-.--", "--.."};

std::map<std::string, char> 
decoder = {{".-", 'A'}, {"-...", 'B'}, {"-.-.", 'C'}, {"-..", 'D'}, {".", 'E'}, 
           {"..-.", 'F'}, {"--.", 'G'}, {"....", 'H'}, {"..", 'I'}, {".---", 'J'}, {"-.-", 'K'},
           {".-..", 'L'}, {"--", 'M'}, {"-.", 'N'}, {"---", 'O'}, {".--.", 'P'}, 
           {"--.-", 'Q'}, {".-.", 'R'}, {"...", 'S'}, {"-", 'T'}, {"..-", 'U'},
           {"...-", 'V'}, {".--", 'W'}, {"-..-", 'X'}, {"-.--", 'Y'}, {"--..", 'Z'}, 
           {"..--", '_'}, {".-.-", ','}, {"---.", '.'}, {"----", '?'}};

std::string encode_char(char c) {
  switch(c) {
    case '_': return "..--";
    case ',': return ".-.-";
    case '.': return "---.";
    case '?': return "----";
    default: return encoder[c - 'A'];
  }
}

std::string encode(std::string str, std::vector<int>& numbers) {
  std::string result = "";
  for(char c : str) {
    std::string e = encode_char(c);
    numbers.push_back(e.length());
    result += e;
  }
  return result;
}

std::string decode(const std::string& str, const std::vector<int> numbers) {
  std::string result;
  
  int index = 0;
  for(int n : numbers) {
    result += decoder[str.substr(index, n)];
    index += n;
  }
  return result;
}

int main() {
  while(true) {
    std::string line;
    std::getline(std::cin, line);
    if(std::cin.eof()) {
      return 0;
    }
    
    std::vector<int> numbers;
    std::string encoded = encode(line, numbers);
    
    std::reverse(std::begin(numbers), std::end(numbers));
    std::cout << decode(encoded, numbers) << std::endl;
  }
}
