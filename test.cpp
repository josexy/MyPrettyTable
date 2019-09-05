#include <iostream>
#include "PrettyTable.h"

int main(){
    PrettyTable pp;

    vector<string> vec_header={"ID","USERNAME","PASSWORD"};
    pp.AddHeader(vec_header);

    vector<string> vec_data1={"001","root","root222ff99992"};
    vector<string> vec_data2={"002","ror3eefefot","3r3"};
    vector<string> vec_data3={"03","rrroot","root22"};

    pp.AddRow(vec_data1);
    pp.AddRow(vec_data2);
    pp.AddRow(vec_data3);

    cout<<pp.to_String()<<endl;


    return 0;
}

