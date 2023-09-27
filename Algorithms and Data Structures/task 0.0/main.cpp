#include <iostream>
#include <fstream>
#include <set>

#define int long long

int32_t main()
{
    std::set<int> addendums;
    int sum = 0;

    std::ifstream in("input.txt");
    
    int temp = 0;

    while (in >> temp)
    {
        addendums.insert(temp);
    }

    for (int numb : addendums)
    {
        sum += numb;
    }

    addendums.clear();
    in.close();
    in.clear();

    std::ofstream out("output.txt");

    out << sum << '\n';

    out.close();
    out.clear();
}