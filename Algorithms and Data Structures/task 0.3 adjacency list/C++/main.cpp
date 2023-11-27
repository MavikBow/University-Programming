#include <fstream>
#include <vector>

int main()
{
    std::vector<int>* table;

    int size, amount, x, y;

    std::ifstream fin("input.txt");
    std::ofstream fout("output.txt");

    fin >> size >> amount;
    table = new std::vector<int>[size];

    for(int i = 0; i < amount; i++)
    {
	fin >> x >> y;
	table[x - 1].push_back(y);
	table[y - 1].push_back(x);
    }

    for(int i = 0; i < size; i++)
    {
	fout << table[i].size() << ' ';
	for(auto a : table[i])
	{
	    fout << a << ' ';
	}	
	fout << std::endl;
    }

    delete[]table;
    fin.close();
    fout.close();

    return 0;
}