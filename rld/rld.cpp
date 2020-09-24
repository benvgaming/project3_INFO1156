// rld.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <vector>
#include <fstream>
#include <filesystem>
#include <sstream>

using namespace std;
using namespace std::filesystem;

//function to decode text file
void decodeDec(path inPath, path outPath)
{
    ifstream infile(inPath, ios::binary);
    ofstream outfile(outPath, ios::binary);
    string str;
    if (!infile)
    {
        cerr << "Could not open " << inPath << " for reading.\n";
        exit(EXIT_FAILURE);
    }
    while (getline(infile, str))
    {
        int a, b, c = str.find(" ");
        a = stoi(str.substr(0, c));
        b = stoi(str.substr(c + 1));

        for (int j = 0; j < a; j++)
            outfile << (unsigned char)b;
    }
}

//function to decode binary file
void decodeBin(path inPath, path outPath)
{
    ifstream infile(inPath, ios::binary);
    ofstream outfile(outPath, ios::binary);
    short n;
    vector<short> count;
    vector<char> character;
    if (!infile)
    {
        cerr << "Could not open " << inPath << " for reading.\n";
        exit(EXIT_FAILURE);
    }
    while (true)
    {
        infile.read((char*)&n, 8);
        if (infile.eof()) break;
        short m = n;
        count.push_back(m);
        infile.read((char*)&n, 1);
        if (infile.eof()) break;
        character.push_back((char)n);
    }
    for (int i = 0; i < count.size(); i++)
        for (int j = 0; j < count[i]; j++)
            outfile << character[i];
    exit(EXIT_SUCCESS);
}



int main(int argc, char* argv[])
{
    //Display the help message
    if ((argc == 2 && (argv[1] == "--help"sv || argv[1] == "-?"sv)) || argc == 1)
    {
        std::cout << "rld (c) 2020, Manh Cuong Nguyen\n" <<
            "===========================================================\n" <<
            "Version 1.0.0\n\n" <<
            "A run-length decoder utility.\n\n" <<
            "Usage: rld [-(b|t)] [--help] [--version] infile [outfile]\n\n" <<
            "Examples:\n" <<
            "rld myfile.doc.rlet\n" <<
            "> decodes 'myfile.doc.rlet' to 'myfile.doc' (text mode)\n\n" <<
            "rld myfile.doc.rleb\n" <<
            "> decodes 'myfile.doc.rleb' to 'myfile.doc' (binary mode)\n\n" <<
            "rld -t myfile.rle myfile.doc\n" <<
            "> decodes 'myfile.rle' to 'myfile.doc' (text mode)\n\n" <<
            "rld -b myfile.rle ec.exe\n" <<
            "> decodes 'myfile.rle' to 'ec.exe' (binary mode)\n\n" <<
            "rld --help\n" <<
            "> displays the help\n\n" <<
            "rld --version\n" <<
            "> displays version number in the format d.d.d" << endl;
        return EXIT_SUCCESS;
    }
    //Display the version
    else if (argc == 2 && argv[1] == "--version"sv)
    {
        cout << "Version: 1.0.0" << endl;
        return EXIT_SUCCESS;
    }
    else if (argc == 2 && argv[1] == "-bt"sv)
    {
        cout << "Error: cannot use both -b and -t" << endl;
        return EXIT_FAILURE;
    }
    else if (argc == 2 && (argv[1] == "-bb"sv || argv[1] == "-tt"sv))
    {
        if (argv[1] == "-bb"sv)
            cout << "Error: duplicate switches: <b>" << endl;
        else if (argv[1] == "-tt"sv)
            cout << "Error: duplicate switches: <t>" << endl;
        return EXIT_FAILURE;
    }
    else if (argc == 2)
    {
        path inPath = argv[1];
        if (inPath.extension().string() != ".rleb")
        {
            if (inPath.extension().string() != ".rlet")
            {
                cout << "Error: you must provide an output filename when there is no '.rle(b|t)' extension on the input file" << endl;
                return EXIT_FAILURE;
            }
            if (!exists(inPath))
            {
                cerr << "Error: file '" << inPath.string() << "' cannot be found.\n";
                return EXIT_FAILURE;
            }
            else
            {
                string tempPath = argv[1];
                tempPath.erase(tempPath.find(".rlet"));
                path outPath = tempPath;
                decodeDec(inPath, outPath);
            }
        }
        else
        {
            path inPath = argv[1];
            if (inPath.extension().string() != ".rleb")
            {
                cout << "Error: you must provide an output filename when there is no '.rle(b|t)' extension on the input file" << endl;
                return EXIT_FAILURE;
            }
            if (!exists(inPath))
            {
                cerr << "Error: file '" << inPath.string() << "' cannot be found.\n";
                return EXIT_FAILURE;
            }
            else
            {
                string tempPath = argv[1];
                tempPath.erase(tempPath.find(".rleb"));
                path outPath = tempPath;
                decodeBin(inPath, outPath);
            }
        }
    }
    else if (argc == 3)
    {
        path inPath = argv[2];

        if (!exists(inPath))
        {
            cerr << "Error: file '" << inPath.string() << "' cannot be found.\n";
            return EXIT_FAILURE;
        }
        if (argv[1] == "-t"sv)
        {
            string tempOutfile = argv[2];
            if (inPath.extension().string() != ".rlet")
            {
                cout << "ERROR: you must provide an output filename when there is no '.rle(b|t)' extension on the input file" << endl;
                return EXIT_FAILURE;
            }
            else if (inPath.extension().string() == ".rlet")
            {
                string tempPath = argv[2];
                tempPath.erase(tempPath.find(".rlet"));
                path outPath = tempPath;
                decodeDec(inPath, outPath);
            }
            else
            {
                cout << "ERROR" << endl;
                return EXIT_FAILURE;
            }
        }
        else if (argv[1] == "-b"sv)
        {
            string tempOutfile = argv[2];
            if (inPath.extension().string() != ".rleb")
            {
                cout << "Error: you must provide an output filename when there is no '.rle(b|t)' extension on the input file" << endl;
                return EXIT_FAILURE;
            }
            else if (inPath.extension().string() == ".rleb")
            {
                string tempPath = argv[2];
                tempPath.erase(tempPath.find(".rleb"));
                path outPath = tempPath;
                decodeBin(inPath, outPath);
            }
            else
            {
                cout << "ERROR" << endl;
                return EXIT_FAILURE;
            }
        }
    }
    else if (argc == 4)
    {
        path inPath = argv[2];
        path outPath = argv[3];

        if (!exists(inPath))
        {
            cerr << "Error: file '" << inPath.string() << "' cannot be found.\n";
            return EXIT_FAILURE;
        }
        if (argv[1] == "-t"sv)
        {
            decodeDec(inPath, outPath);
        }
        else if (argv[1] == "-b"sv)
        {
            decodeBin(inPath, outPath);
        }
        else
        {
            cout << "ERROR" << endl;
            return EXIT_FAILURE;
        }
    }
    else
    {
        cout << "ERROR: command is invalid" << endl;
        return EXIT_FAILURE;
    }
    exit(EXIT_SUCCESS);
}

