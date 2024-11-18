#include <iostream>
#include <vector>
#include <string>
#include <regex>

std::vector<int> parseNumbers(const std::string& input) {
    std::vector<int> numbers;
    std::regex re("(-?\\d+)");
    std::sregex_iterator begin(input.begin(), input.end(), re), end;
    for (auto it = begin; it != end; ++it) {
        numbers.push_back(std::stoi(it->str()));
    }
    return numbers;
}

int main() {
    std::string input = "Here are some numbers: -10, 20, -30, 40";
    std::vector<int> numbers = parseNumbers(input);
    for (int num : numbers) {
        std::cout << num << " ";
    }
    return 0;
}

