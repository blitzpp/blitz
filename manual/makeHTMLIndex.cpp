#include <iostream>
#include <fstream>
#include <strings>

#include <string.h>
#include <stdio.h>

int tagnum = 1;

void makeEntry(char* entry, char* index)
{
    entry[0] = 0;

    char* bang = index;
    while ((bang = strstr(index, "!")) != 0) {
        strcat(entry, "<spacer size=10>");
        index = bang+1;
    }

    strcat(entry, index);
}

void process(const char* filename, std::istream& ifs, std::ostream& ofs, 
    std::ostream& indexfs)
{
    int n = 1024;
    char tmpbuf[1024];
    char tag[128];
    char entry[1024];

    while (!ifs.eof())
    {
        ifs.getline(tmpbuf,n);
        if (ifs.eof())
            break;
        ofs << tmpbuf;

        char* index;
        if ((index = strstr(tmpbuf, "BZINDEX")) != 0) {
            char* index2 = strstr(index, "-->");
            if (index2 != 0)
                index2[-1] = 0;
            index += 8;

            sprintf(tag, "index%05d", tagnum++);
            ofs << "<a name=\"" << tag << "\">";

            makeEntry(entry, index);
            indexfs << index << " |"
                    << entry << "|"
                    << filename << "#" << tag << std::endl;

//            std::cout << "Found tag: \"" << index << "\"" << std::endl;
        }

        ofs << std::endl;
    }
}

int main(const int argc,const char* argv[]) {
    std::cout << "Building HTML index:" << std::endl;

    std::ofstream indexfs("index.data");

    for (int i=1; i < argc; ++i) {
        std::cout << argv[i] << std::endl;
        std::cout.flush();

        std::ifstream ifs(argv[i]);
        std::ofstream ofs((std::string(argv[i])+".new").c_str());

        process(argv[i], ifs, ofs, indexfs);
    }
}
