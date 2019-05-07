#include "PointCloud.hpp"

using namespace std;

PointCloud::PointCloud(const string &path)
{
    read(path);
}

void PointCloud::read(const string &path)
{
    ifstream inLAS(path, ios::binary);

    if (inLAS.is_open())
    {
        Header header;
        inLAS.read((char *)&header, sizeof(header));
        cout << (int)header.versionMaj << "." << (int)header.versionMin << endl;
        cout << header.headerSize << " == " << sizeof(header);
    }
    else
    {
        throw runtime_error("LAS not found");
    }
}