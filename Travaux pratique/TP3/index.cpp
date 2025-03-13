#include <cstdio>
#include <iostream>
#include "SVGstream.h"

int main() {
    SVGstream s("full_page.html");
    s.open("full_page.html");
    
    s << "<circle cx=\"600\" cy=\"200\" r=\"100\" fill=\"cyan\" />";

    s.close();
    return 0;
}