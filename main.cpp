#include "function.h"

int main()
{
    string input_str, input_word;
    int sqrt_length_str = 0, length_word = 0;

    cout << "Please, input string size N^2 (N - integer): ";
    while (cin >> input_str)
    {
        if (sqrt(input_str.length()) != int(sqrt(input_str.length())))
        {
            error("You entered a string with length != N^2.");
        }
        else
        {
            sqrt_length_str = sqrt(input_str.length());
            break;
        }
    }

    cout << "Ok, now enter a search word: ";
    while (cin >> input_word)
    {
        if (input_word.length() > pow(sqrt_length_str, 2))
        {
            error("You entered too long a word.");
        }
        else
        {
            length_word = input_word.length();
            break;
        }
    }

    clock_t time = clock();

    uppercase(input_str); uppercase(input_word);

    char** character_matrix = new char*[sqrt_length_str];
    for (int i = 0; i < sqrt_length_str; ++i)
        character_matrix[i] = new char[sqrt_length_str];

    array_filling(character_matrix, sqrt_length_str, input_str);
    word_found(character_matrix, sqrt_length_str, input_word, length_word);

    for (int i = 0; i < sqrt_length_str; ++i)
        delete [] character_matrix[i];
    delete [] character_matrix;

    time = clock() - time;
    cout << "runtime = " << double(time)*1000/CLOCKS_PER_SEC << " ms" << endl;
    system("pause");

    return 0;
}