#include "function.h"

void error(const string &s)
{
    cout << "Error: " << s << " Retype, please..." << endl;
}

void uppercase(string &str)
{
    for (char &i : str) i = toupper(i);
}

void array_filling(char *array[], const int size, const string &work_str)
{
    for (int j = 0; j < size; ++j) array[0][j] = work_str[j];
    for (int i = 1; i < size; ++i)
    {
        for (int j = 0; j < size; ++j) array[i][j] = work_str[j+(size*i)];
    }
}

void word_found(char *array[], const int size_array, const string &work_str, const int size_word)
{
    string bad_result = "The entered word is not in the entered string.";
    vector <vector <int>> cells(1, vector <int> (2*size_word));

    for (int i = 0; i < size_array; ++i)
    {
        for (int j = 0; j < size_array; ++j)
        {
            if (array[i][j] == work_str[0])
            {
                vector <int> temp (2*size_word);
                temp[0] = i; temp[1] = j;
                cells.push_back(temp);
            }
        }
    }

    if (cells.size() == 1) { cout << bad_result << endl; return; }
    cells.erase(cells.begin());

    for (int n = 1; n < size_word; ++n)
    {
        int size = cells.size();
        for (int m = 0; m < size; ++m)
        {
            vector<int> temp = cells[m];
            int i = temp[0 + 2*(n-1)], j = temp[1 + 2*(n-1)];

            if ((i != 0) && array[i-1][j] == work_str[n])
            {
                temp[0 + 2 * n] = i - 1;
                temp[1 + 2 * n] = j;
                cells.push_back(temp);
            }
            if ((i != size_array-1) && array[i+1][j] == work_str[n])
            {
                temp[0 + 2 * n] = i + 1;
                temp[1 + 2 * n] = j;
                cells.push_back(temp);
            }
            if ((j != 0) && array[i][j-1] == work_str[n])
            {
                temp[0 + 2 * n] = i;
                temp[1 + 2 * n] = j - 1;
                cells.push_back(temp);
            }
            if ((j != size_array-1) && array[i][j+1] == work_str[n])
            {
                temp[0 + 2 * n] = i;
                temp[1 + 2 * n] = j + 1;
                cells.push_back(temp);
            }
        }
        cells.erase(cells.begin(), cells.begin()+size);
    }

    for (int i = 0; i < cells.size(); ++i) //cell intersection check
    {
        bool flag = false;
        for (int n = 0; n < size_word; ++n)
        {
            for (int m = 1; m < (size_word-n); ++m)
            {
                if ((cells[i][0 + 2*n] == cells[i][0 + 2*(n+m)]) && (cells[i][1 + 2*n] == cells[i][1 + 2*(n+m)]))
                {
                    cells.erase(cells.begin()+i--);
                    flag = true;
                    break;
                }
            }
            if (flag) break;
        }
    }

    if (cells.empty()) cout << bad_result << endl;
    else
    {
        cout << "Great! The entered word is in the entered string in the following cells: [" << cells[0][0] << ", " << cells[0][1] << "]";
        for (int i = 1; i < size_word; ++i)
        {
            cout << " -> [" << cells[0][0 + 2 * i] << ", " << cells[0][1 + 2 * i] << "]";
        }
        cout << endl;
    }
}
