#include <iostream.h>
#include <fstream.h>
#include <strings.h>
#include <string.h>
#include <stdio.h>

int tagnum = 1;

void makeEntry(char* entry, char* index)
{
    entry[0] = 0;

    char* bang = index;
    while ((bang = strstr(index, "!")) != 0)
    {
        strcat(entry, "<spacer size=10>");
        index = bang+1;
    }

    strcat(entry, index);
}

void process(const char* filename, istream& ifs, ostream& ofs, 
    ostream& indexfs)
{
    int n = 1024;
    char tmpbuf[1024];
    char tag[128];
    char entry[1024];

    while (!ifs.eof())
    {
        ifs.getline(tmpbuf, n);
        if (ifs.eof())
            break;
        ofs << tmpbuf;

        char* index;
        if ((index = strstr(tmpbuf, "BZINDEX")) != 0)
        {
            char* index2 = strstr(index, "-->");
            if (index2 != 0)
                index2[-1] = 0;
            index += 8;

            sprintf(tag, "index%05d", tagnum++);
            ofs << "<a name=\"" << tag << "\">";

            makeEntry(entry, index);
            indexfs << index << " |"
                    << entry << "|"
                    << filename << "#" << tag << endl;

//            cout << "Found tag: \"" << index << "\"" << endl;
        }

        ofs << endl;
    }
}

int main(int argc, char* argv[])
{
    cout << "Building HTML index:" << endl;

    ofstream indexfs("index.data");

    for (int i=1; i < argc; ++i)
    {
        cout << argv[i] << endl;
        cout.flush();

        ifstream ifs(argv[i]);
        char tmpbuf[128];
        sprintf(tmpbuf, "%s.new", argv[i]);
        ofstream ofs(tmpbuf);

        process(argv[i], ifs, ofs, indexfs);
    }
}

