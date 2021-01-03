#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "../lib/doctest.h"

#include "../include/interpreter/interpreter.h"
#include <fstream>

std::ofstream out;
std::ifstream in;

inline void check(std::string input, std::string exprected)
{
    out.open("test.iml");
    out << input;
    out.close();
    iml::interpreter i;
    i.interpret_file("test.iml");
    std::string result = "", temp;
    in.open("iml_result.imlr");
    while (std::getline(in, temp))
    {
        result += temp;
    }
    CHECK(result == exprected);
    in.close();
}

TEST_CASE("empty")
{
    check(" ", "Result: ");   
}

TEST_CASE("map-inc")
{
    check("<MAP-INC \"1\"> 1 2 3 </MAP-INC>", "Result: 2 3 4");
    check("<MAP-INC \"1.29\"> 1 2 3 </MAP-INC>", "Result: 2.29 3.29 4.29");
    check("<MAP-INC \"-1\"> 1 2 3 </MAP-INC>", "Result: 0 1 2");
    check("<MAP-INC \"1\">  </MAP-INC>", "Result: ");
    check("<MAP-INC> 1 2 3 </MAP-INC>", "Result: 1 2 3");
}

TEST_CASE("map-mlt")
{
    check("<MAP-MLT \"2\"> 1 2 3 </MAP-MLT>", "Result: 2 4 6");
    check("<MAP-MLT \"2.5\"> 1 2 3 </MAP-MLT>", "Result: 2.5 5 7.5");
    check("<MAP-MLT \"-2\"> 1 2 3 </MAP-MLT>", "Result: -2 -4 -6");
    check("<MAP-MLT \"2\">  </MAP-MLT>", "Result: ");
    check("<MAP-MLT> 1 2 3 </MAP-MLT>", "Result: 1 2 3");
}

TEST_CASE("agg-sum")
{
    check("<AGG-SUM> 1 2 3 </AGG-SUM>", "Result: 6");
    check("<AGG-SUM> 1.2 2.93 3 </AGG-SUM>", "Result: 7.13");
    check("<AGG-SUM> -1 2 -3.1 </AGG-SUM>", "Result: -2.1");
    check("<AGG-SUM>  </AGG-SUM>", "Result: ");
}

TEST_CASE("agg-pro")
{
    check("<AGG-PRO> 2 3 4 </AGG-PRO>", "Result: 24");
    check("<AGG-PRO> 2.3 3.4 4.5 </AGG-PRO>", "Result: 35.19");
    check("<AGG-PRO> -2 -3 -4 -1 </AGG-PRO>", "Result: 24");
    check("<AGG-PRO> -2 -3 -4 1 </AGG-PRO>", "Result: -24");
    check("<AGG-PRO>  </AGG-PRO>", "Result: ");
}

TEST_CASE("agg-avg")
{
    check("<AGG-AVG> 1 2 3 </AGG-AVG>", "Result: 2");
    check("<AGG-AVG> 1 2.5 3 </AGG-AVG>", "Result: 2.16667");
    check("<AGG-AVG> 1 2 -3 </AGG-AVG>", "Result: 0");
    check("<AGG-AVG>  </AGG-AVG>", "Result: ");
}

TEST_CASE("agg-fst")
{
    check("<AGG-FST> 1 2 3 </AGG-FST>", "Result: 1");
    check("<AGG-FST> 1 </AGG-FST>", "Result: 1");
    check("<AGG-FST> </AGG-FST>", "Result: ");
}

TEST_CASE("agg-lst")
{
    check("<AGG-LST> 1 2 3 </AGG-LST>", "Result: 3");
    check("<AGG-LST> 3 </AGG-LST>", "Result: 3");
    check("<AGG-LST> </AGG-LST>", "Result: ");
}

TEST_CASE("srt-ord")
{
    check("<SRT-ORD \"DSC\"> 1 2 3 </SRT-ORD>", "Result: 3 2 1");
    check("<SRT-ORD \"ASC\"> 3 2 1 </SRT-ORD>", "Result: 1 2 3");
    check("<SRT-ORD \"ASC\">  </SRT-ORD>", "Result: ");
    check("<SRT-ORD> 3 2 1 </SRT-ORD>", "Result: 1 2 3");
}

TEST_CASE("srt-slc")
{
    check("<SRT-SLC \"3\"> 1 2 3 4 5 6 </SRT-SLC>", "Result: 4 5 6");
    check("<SRT-SLC \"0\"> 1 2 3 4 5 6 </SRT-SLC>", "Result: 1 2 3 4 5 6");
    check("<SRT-SLC \"-1\"> 1 2 3 4 5 6 </SRT-SLC>", "Result: 1 2 3 4 5 6");
    check("<SRT-SLC> 1 2 3 4 5 6 </SRT-SLC>", "Result: 1 2 3 4 5 6");
    check("<SRT-SLC \"1\">  </SRT-SLC>", "Result: ");
}

TEST_CASE("srt-dst")
{
    check("<SRT-DST> 1 1 1 2 3 2 1 2 3 3 </SRT-DST>", "Result: 1 2 3");
    check("<SRT-DST> 1 2 3 </SRT-DST>", "Result: 1 2 3");
    check("<SRT-DST>  </SRT-DST>", "Result: ");
}

TEST_CASE("srt-rev")
{
    check("<SRT-REV> 1 2 3 </SRT-REV>", "Result: 3 2 1");
    check("<SRT-REV> 3 2 1 </SRT-REV>", "Result: 1 2 3");
    check("<SRT-REV>  </SRT-REV>", "Result: ");
}

TEST_CASE("let")
{
    check ("<LET \"X\"> 1 2 3 <BODY/> X 4 5 6 </LET>", "Result: 1 2 3 4 5 6");
    check ("<LET \"X\">  <LET \"X\"> 12 123 <BODY/> X 19 </LET> 1 2 3 <BODY/> X 4 5 6 </LET>", "Result: 12 123 19 1 2 3 4 5 6");
    check ("<LET \"X\"> 1 2 3 <BODY/> X 4 5 6 <LET \"X\"> 12 123 <BODY/> X 19 </LET> X </LET>", "Result: 1 2 3 4 5 6 12 123 19 1 2 3");
    check ("<LET \"X\">  <BODY/> </LET>", "Result: ");
    check ("<LET> 1 2 3 <BODY/> X </LET>", "Result: 1 2 3");
    check ("<LET> 1 2 3 <BODY/> </LET>", "Result: ");
}

TEST_CASE("nested")
{
    check ("200 <SRT-ORD \"DSC\"> 1 2 3 4 <MAP-INC \"1\"> 1 2 3 <MAP-MLT \"2\"> 1 2 3 <LET \"X\"> <MAP-INC \"3\"> 1 2 </MAP-INC> 3 <BODY/> <AGG-SUM> X 20 </AGG-SUM> </LET> 12 </MAP-MLT> 12 19 </MAP-INC> 19 </SRT-ORD> 201", "Result: 200 65 25 20 19 13 7 5 4 4 3 3 3 2 2 1 201");
}