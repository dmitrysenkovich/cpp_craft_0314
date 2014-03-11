#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <xutility>
#include <xlocale>

using namespace std;

namespace Constants
{
    namespace Paths
    {
        const string input_file = BINARY_DIR "/input.txt";
        const string output_file = BINARY_DIR "/output.txt";
    }

    const string ignore_simbols = " -\\";

    namespace Results
    {
        const string good = "YES";
        const string bad  = "NO";
    }
}


void removeIgnoreSimbols(string& _str)
{
    for (string::const_iterator it = Constants::ignore_simbols.cbegin(); it != Constants::ignore_simbols.cend(); ++it)
    {
        _str.erase(remove(_str.begin(), _str.end(), (*it)), _str.end());
    }
}


bool isValidKeyForText(const string& _key, const string& _text)
{
    string revert_key(_key);

	std::reverse(revert_key.begin(), revert_key.end());

    const size_t pos_revert_key = _text.find(revert_key);
    if (pos_revert_key != _text.npos)
    {
        return true;
    }

    return false;
}


void upperCase(string& _text) 
{
    for(string::iterator it = _text.begin(); it != _text.end(); ++it)
    {
        (*it) = toupper(*it);
    }
}


int main( int argc, char* argv[] )
{
    locale loc("Russian_Russia");

    ifstream input_file( Constants::Paths::input_file );

    if ( !input_file.eof() )
    {
        string first_line;
        getline( input_file, first_line );

        removeIgnoreSimbols(first_line);
        upperCase(first_line);

        ofstream output_file(Constants::Paths::output_file);

        while (!input_file.eof())
        {
            string key_value;
            std::getline( input_file, key_value );

            removeIgnoreSimbols(key_value);
            upperCase(key_value);

            const string& valid_key = isValidKeyForText(key_value, first_line)  ? Constants::Results::good
                                                                                : Constants::Results::bad;
            output_file << valid_key << endl;
            cout << valid_key << endl;
        }
        output_file.close();
    }

    input_file.close();
}
