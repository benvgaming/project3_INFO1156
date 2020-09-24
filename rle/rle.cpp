/*
    File: rle.cpp
    Author: Manh Cuong Nguyen
    Date: July 16th 2020
    Purpose: Encoding files
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <fstream>
#include <filesystem>

using namespace std;
using namespace std::filesystem;

//Function to encode file (text)
void encodeDec(path inPath, string outPath)
{
    ifstream infile(inPath, ios::binary);
    ofstream outfile(outPath);
    vector<int> data;
    char ch;
    if (!infile)
    {
        cerr << "Could not open " << inPath << " for reading.\n";
        exit(EXIT_FAILURE);
    }
    while (infile.read(&ch, 1))
    {
        unsigned char temp = (int)ch;
        data.push_back((int)temp);
    }

    int count = 1;

    for (int i = 0; i < data.size(); i++)
    {
        if (i == data.size() - 1)
        {
            if (data[i] == data[i - 1])
            {
                outfile << count << " " << data[i] << endl;
                break;
            }
        }
        else if (data[i] == data[i + 1])
        {
            count++;
            continue;
        }
        else
        {
            outfile << count << " " << data[i] << endl;
            count = 1;
        }
    }
    outfile.close();
    infile.close();
}

//Function to encode file (Binary)
void encodeBin(path inPath, string outPath)
{
    ifstream infile(inPath, ios::binary);
    ofstream outfile(outPath, ios::binary);
    vector<int> data;
    char ch;
    long long count = 1;

    if (!infile)
    {
        cerr << "Could not open " << inPath << " for reading.\n";
        exit(EXIT_FAILURE);
    }

    while (infile.read(&ch, 1))
    {
        unsigned char temp = (int)ch;
        data.push_back((int)ch);
    }

    for (int i = 0; i < data.size(); i++)
    {
        if (i == data.size() - 1)
        {
            short n = data[i];
            outfile.write((char*)&count, 8);
            outfile.write((char*)&n, 1);
            break;
        }
        else if (data[i] == data[i + 1])
        {
            count++;
            continue;
        }
        else
        {
            short n = data[i];
            outfile.write((char*)&count, 8);
            outfile.write((char*)&n, 1);
            count = 1;
        }
    }
    outfile.close();
    infile.close();
}

int main(int argc, char* argv[])
{
    //Display help messages
    if ((argc == 2 && (argv[1] == "--help"sv || argv[1] == "-?"sv)) || argc == 1)
    {
        cout << "rle 2020, Manh Cuong Nguyen\n"
            "===========================================================\n"
            "Version 1.0.0\n\n"
            "A run-length encoder utility.\n\n"
            "Usage: rle [-(b|t)] [--help] [--version] infile [outfile]\n\n"
            "Examples:\n"
            "   rle myfile.doc\n"
            "       > encodes 'myfile.doc' to 'myfile.doc.rlet' (text mode)\n\n"
            "   rle -b ..\\myfile.doc\n"
            "       > encodes 'myfile.doc' from the parent folder to 'myfile.doc.rleb' (binary mode) in the current folder\n\n"
            "   rle -t myfile.doc ec.text\n"
            "       > encodes 'myfile.doc' from the parent folder to 'ec.text' in the local folder (text mode)\n\n"
            "   rle -b myfile.doc ec.bin\n"
            "       > encodes 'myfile.doc' from the parent folder to 'ec.bin' in the local folder (binary mode)\n\n"
            "   rle --help\n"
            "       > displays the help\n\n"
            "   rle --version\n"
            "       > displays version number in the format d.d.d" << endl;
        return EXIT_SUCCESS;
    }
    //Display the version
    else if (argc == 2 && argv[1] == "--version"sv)
    {
        cout << "Version: 1.0.0" << endl;
        return EXIT_SUCCESS;
    }
    else if (argc == 2 && (argv[1] == "-bt"sv || argv[1] == "-tb"sv))
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
        path filename = argv[1];
        string outfile = argv[1];
        outfile += ".rlet";
        if (!exists(filename))
        {
            cerr << "Error: file '" << filename.string() << "' cannot be found.\n";
            return EXIT_FAILURE;
        }
        else
            encodeDec(filename, outfile);
    }
    else if (argc == 3)
    {
        if (argv[1] == "-t"sv)
        {
            path filename = argv[2];
            string outfile = argv[2];
            outfile += ".rlet";
            if (!exists(filename))
            {
                cerr << "Error: file '" << filename.string() << "' cannot be found.\n";
                return EXIT_FAILURE;
            }
            else
                encodeDec(filename, outfile);
        }
        else if (argv[1] == "-b"sv)
        {
            path filename = argv[2];
            string outfile = argv[2];
            outfile += ".rleb";
            if (!exists(filename))
            {
                cerr << "Error: file '" << filename.string() << "' cannot be found.\n";
                return EXIT_FAILURE;
            }
            else
                encodeBin(filename, outfile);
        }
        else
        {
            path filename = argv[1];
            string outfile = argv[2];

            if (!exists(filename))
            {
                cerr << "Error: file '" << filename.string() << "' cannot be found.\n";
                return EXIT_FAILURE;
            }
            else
                encodeDec(filename, outfile);
        }
    }
    else if (argc == 4)
    {
        if (argv[1] == "-t"sv)
        {
            path filename = argv[2];
            string outfile = argv[3];
            if (!exists(filename))
            {
                cerr << "Error: file '" << filename.string() << "' cannot be found.\n";
                return EXIT_FAILURE;
            }
            else
                encodeDec(filename, outfile);
        }
        else if (argv[1] == "-b"sv)
        {
            path filename = argv[2];
            string outfile = argv[3];
            if (!exists(filename))
            {
                cerr << "Error: file '" << filename.string() << "' cannot be found.\n";
                return EXIT_FAILURE;
            }
            else
                encodeBin(filename, outfile);
        }
    }
    else
    {
        cout << "ERROR: command is invalid" << endl;
        return(EXIT_FAILURE);
    }
    exit(EXIT_SUCCESS);
}
