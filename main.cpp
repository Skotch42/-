#include <iostream>
#include <chrono>
#include <fstream>
#include "Parser.h"
#include "Interpreter.h"
#include "Tokenizer.h"
using namespace std;

string open_file(string fileName)
{
  ifstream in(fileName.data(), ios::in | ios::binary);

  if (in)
  {
    return string((istreambuf_iterator<char>(in)), istreambuf_iterator<char>());
  }

  throw runtime_error("Can't open file!");
}

int main() 
{
    cout << "Enter test number: ";
    string aa;
    string fileName = "test";
    cin >> aa;
    fileName = fileName + aa + ".txt";
    cout << endl;

    try 
    {
        //забираем все символы из файла
        string text = open_file(fileName);

        //
        Tokenizer tokenizer(text);

        //
        Parser parser(tokenizer);

        //генерация ОПС
        auto ops = parser.make_ops();

        //интерпретация ОПС
        Interpreter interpreter(ops);

        //вывод ОПС на экран
        for (const auto &item : ops.items)
        {
            if (item.type == ITEM_TYPE::CONST)
            {
                cout << item.value << " ";
            }
            else
            {
                cout << item.word << " ";
            }
        }

        cout << endl;

        //выполнение команд из ОПС, а так же их вывод
        interpreter.generate_commands();

        cout << endl;
    }
    catch(exception& e) 
    {
        cout << e.what() << endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
