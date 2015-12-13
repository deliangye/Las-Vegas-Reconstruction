//
// Created by eiseck on 11.12.15.
//

#include <vector>
#include <sstream>
#include "NodeData.h"



using namespace std;
namespace lvr
{


int NodeData::c_last_id = 0;
time_t NodeData::c_tstamp =  std::time(0);

NodeData::NodeData(string inputPoints, string nodePoints) : NodeData()
{
    create(inputPoints, nodePoints);
}

NodeData::NodeData()
{
    m_gotSize = false;
    m_id = ++c_last_id;
    m_dataPath = "node-";
    m_dataPath.append(to_string(c_tstamp));
    m_dataPath.append("-");
    m_dataPath.append(to_string(m_id));
    m_bufferSize = 400000;
    m_bufferIndex = 0;
}

void NodeData::fillBuffer(size_t start_id)
{
    m_readBuffer.clear();
    ifstream ifs(m_dataPath);
    m_bufferIndex=start_id;
    int i = 0;
    int j = 0;
    float x,y,z;
    string s;
    while( getline( ifs, s ) )
    {
        if(i>=size() || j>=m_bufferSize) break;
        else if(i>=start_id)
        {
            stringstream ss;
            ss.str(s);
            ss >> x >> y >> z;
            m_readBuffer.push_back(Vertexf(x,y,z));
            j++;
        }
        i++;

    }


}

void NodeData::create(string inputPoints, string nodePoints)
{
    //Todo: copy only x, y, z and ignore other values like intensity etc...
    ifstream ifs(inputPoints.c_str(), std::ios::binary);
    ofstream ofs(nodePoints.c_str(),  std::ios::binary);
    ofs << ifs.rdbuf();
    m_dataPath = nodePoints;
    ifs.close();
    ofs.close();


}

void NodeData::open(string path)
{
    m_dataPath = path;

}


void NodeData::remove()
{
    std::remove(m_dataPath.c_str());
    m_dataPath = "";
}

void NodeData::remove(unsigned int i)
{
//Todo: remove vertex at index
}

void NodeData::add(Vertex<float> input)
{
    ofstream ofs(m_dataPath, fstream::app);
    ofs << input.x << " " << input.y << " " <<  input.z << " " <<  std::endl;
    if(m_gotSize) m_size++;
    ofs.close();

}

Vertex<float> NodeData::get(int i)
{

    if(i>=m_bufferIndex && i < m_readBuffer.size())
    {
        return m_readBuffer[i - m_bufferIndex];
    }
    else
    {
        fillBuffer(i);
        return m_readBuffer[i - m_bufferIndex];
    }

    ifstream ifs;
    try
    {
        //cout << "opening: " << m_dataPath << endl;
       ifs.open(m_dataPath);
    }
    catch (exception& e)
    {
        cout << e.what() << endl;
    }

    int j = 0;
    float x,y,z;
    Vertex<float> res;
    //std::cout << "good: " << ifs.good() << "eof?: " << ifs.eof() << std::endl;

    while(ifs.good() && !ifs.eof())
    {
        ifs >> x >> y >> z;
        if(j==i && ifs.good() && !ifs.eof())
        {
            res.x = x;
            res.y = y;
            res.z = z;
            ifs.close();
            return res;
        }
        j++;
    }
    ifs.close();
    return Vertex<float>();
}

Vertex<float> NodeData::next()
{
    return Vertex<float>();
}

NodeData::Iterator NodeData::begin()
{
    return NodeData::Iterator(*this);
}

NodeData::Iterator NodeData::end()
{
    return NodeData::Iterator(*this, this->size());
}

NodeData::NodeData(NodeData &origin) : NodeData()
{
    copy(origin);
}
NodeData &lvr::NodeData::operator=(lvr::NodeData &origin)
{
    if(this != &origin)
    {
        copy(origin);
    }
    return *this;
}


lvr::Vertexf NodeData::operator[](unsigned int i)
{
    return get(i);
}

void NodeData::copy(NodeData &origin)
{
    this->m_dataPath = origin.m_dataPath;
    this->m_gotSize  = origin.m_gotSize;
    this->m_size     = origin.m_size;

}

size_t NodeData::size()
{
    if(m_gotSize) return m_size;
    else
    {

        ifstream ifs( m_dataPath );
        size_t size = 0;
        string s;
        while( getline( ifs, s ) ) size++;

        m_size = size;
        m_gotSize = true;
        ifs.close();
        return size;
    }
}

}


