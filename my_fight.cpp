#include <iostream>
#include <vector>
#include <string>

struct Month {
    int daysCount;
};

std::vector<Month> GetAllMonths() {

    return {
        {31},
        {28},
        {31},
        {30},
        {31}, 
        {30},
        {31},
        {31},
        {30},
        {31},
        {30},
        {31}
   };
}

std::vector<std::vector<std::string>> add(std::vector<std::vector<std::string>> currentMonth, int OperationDate, std::string OperationDeal) {
        currentMonth[OperationDate - 1].push_back(OperationDeal);
        return currentMonth;
}

std::vector<std::vector<std::string>> next(std::vector<std::vector<std::string>> savedPreviousMonth, std::vector<std::vector<std::string>> currentMonth) {

        if(savedPreviousMonth.size() - currentMonth.size() == 0 || savedPreviousMonth.size() - currentMonth.size() == -1 || savedPreviousMonth.size() - currentMonth.size() == -3) {
            for(int i = 0; i < savedPreviousMonth.size(); i++) {
                    currentMonth[i].insert(currentMonth[i].end(), savedPreviousMonth[i].begin(), savedPreviousMonth[i].end());
            }
            return currentMonth;
        } else if(savedPreviousMonth.size() - currentMonth.size() == 1) {
            for(int i = 0; i < currentMonth.size(); i++) {
                    currentMonth[i].insert(currentMonth[i].end(), savedPreviousMonth[i].begin(), savedPreviousMonth[i].end());
            }
            currentMonth[29].insert(currentMonth[29].end(), savedPreviousMonth[30].begin(), savedPreviousMonth[30].end());
            return currentMonth;
        } else if(savedPreviousMonth.size() - currentMonth.size() == 3){
            for(int i = 0; i < currentMonth.size(); i++) {
                    currentMonth[i].insert(currentMonth[i].end(), savedPreviousMonth[i].begin(), savedPreviousMonth[i].end());
            }
            currentMonth[27].insert(currentMonth[27].end(), savedPreviousMonth[28].begin(), savedPreviousMonth[28].end());
            currentMonth[27].insert(currentMonth[27].end(), savedPreviousMonth[29].begin(), savedPreviousMonth[29].end());
            currentMonth[27].insert(currentMonth[27].end(), savedPreviousMonth[30].begin(), savedPreviousMonth[30].end());
            return currentMonth;
        }

        return currentMonth; 
}

void dump(std::vector<std::string>& dumpedString, std::vector<std::vector<std::string>> currentMonth, int OperationDate) {
    int count = 0;
    for(auto s : currentMonth[OperationDate - 1]) {
        count++;
    }
    std::string result = std::to_string(count) + " ";
    for(int i = 0; i < currentMonth[OperationDate - 1].size(); i++) {
        result += currentMonth[OperationDate - 1][i] + " ";
    }
    dumpedString.push_back(result);
}


int main() {
    std::vector<Month> monthVector = GetAllMonths();
    
    int q;
    std::string OperationType;
    int OperationDate;
    std::string OperationDeal;

    std::cin >> q;
    std::vector<std::string> dumpedString;
    std::vector<std::vector<std::string>> savedPreviousMonth;

    for(int i = 0; i < monthVector.size(); i++) {
        if(q <= 0) {
            break;
        }
        Month currentMonthStruct = monthVector[i];
        std::vector<std::vector<std::string>> currentMonth(currentMonthStruct.daysCount);
    
        if(i > 0) {
        currentMonth = next(savedPreviousMonth, currentMonth);
        }

        while(q > 0){
            std::cin >> OperationType;

            if (OperationType == "NEXT") {
                savedPreviousMonth = currentMonth;
                q--;
                break;
            } else if (OperationType == "ADD") {
                std::cin >> OperationDate;
                std::cin >> OperationDeal;
                currentMonth = add(currentMonth, OperationDate, OperationDeal);
            } else if (OperationType == "DUMP") {
                std::cin >> OperationDate;
                dump(dumpedString, currentMonth, OperationDate);
            }
            q--;
        }

        if(i == 11) i = 0;

        }

        for(auto s : dumpedString) {
            std::cout << s << std::endl;
        }

        return 0;
    }