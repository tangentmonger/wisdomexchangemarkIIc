#include <Wisdom.h>
#include <cpptest.h>
#include <iostream>
#include <fstream>
#include <string>
#include <assert.h>
#include <boost/algorithm/string.hpp>

struct TestData{
    std::string imagePath;
    bool isBlank;
    int textAngle;
};

class WisdomTest : public Test::Suite { 
    public:
        WisdomTest(){
            loadTestData();
            TEST_ADD (WisdomTest::detect_blanks); 
        } 
    
    private:
        std::vector<TestData> m_testData;
        void loadTestData();
        void detect_blanks();
}; 

void WisdomTest::loadTestData()
{
    std::ifstream file("../test/testData.csv");
    std::string line;
    
    while(std::getline(file, line)){
        std::istringstream iss(line);
        std::vector<std::string> elements;
        std::string item;
        while (std::getline(iss, item, ','))
        {
            boost::trim(item);
            elements.push_back(item);
        }
        assert(elements.size() == 3);

        TestData data = {elements[0],
                         elements[1] == "true",
                         std::stoi(elements[2])};
        m_testData.push_back(data);
    }
}

void WisdomTest::detect_blanks()
{
    int correct = 0;
    for(int i=0; i<m_testData.size(); i++)
    {
        TestData data = m_testData[i];
        Wisdom wisdom(data.imagePath);
        bool blank = wisdom.isBlank();
        if(blank == data.isBlank)
        {
            correct++;
        }
        TEST_ASSERT_MSG(blank == data.isBlank, data.imagePath.c_str());
    }
    std::ostringstream result;
    result << correct << "/" << m_testData.size() << " blanks detected correctly";
    TEST_ASSERT_MSG(correct == m_testData.size(), result.str().c_str());
}

int main ( ) 
{ 
    WisdomTest tests; 
    Test::TextOutput output(Test::TextOutput::Verbose);
    return tests.run(output);
}
