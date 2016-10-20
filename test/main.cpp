#include "Wisdom.h"
#include <cpptest.h>



class fooTest : public Test::Suite { 
    public:
        fooTest( ) { 
            TEST_ADD (fooTest::function1_to_test_some_code); 
            TEST_ADD (fooTest::function2_to_test_some_code); 
        } 
    
    private:
        void function1_to_test_some_code( );
        void function2_to_test_some_code( );
}; 

void fooTest::function1_to_test_some_code()
{
    TEST_ASSERT(1+1==2);
}

void fooTest::function2_to_test_some_code()
{
    TEST_ASSERT(1+1==3);
}

int main ( ) 
{ 
    fooTest tests; 
    Test::TextOutput output(Test::TextOutput::Verbose);
    return tests.run(output);
}
