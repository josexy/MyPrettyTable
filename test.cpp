#include <iostream>
#include "PrettyTable.h"
using namespace std;

int main() {
	vector<string>header = { "姓名","学号","信息" };
	vector<string>row1 = { "张小飞","1111111111","你好、我爱C++" };
	vector<string>row2 = { "关小羽","22222222222","你好？我爱ython" };
	vector<string>row3 = { "刘小备","3333333333333","你好，我爱PHP" };
	vector<vector<string>>vecs{ row1,row2,row3 };
	PrettyTable pt;
	try {
		pt.AddHeader(header);
		pt.AddRows(vecs);
		pt.DrawTable();
		cout << pt.to_String() << endl;
	}
	catch (Exception & e) {
		cout << e.what() << endl;
	}

	PrettyTable pt2;
	pt2.AddHeader({ "id","username","password" });
	pt2.AddRows({
		{"111","tony......","12345"},
		{"222","mike","123"},
		{"3333","john","000"}
		});
	pt2.SetBorderStyle(Sign::PT_PLUS, Sign::PT_DOT, Sign::PT_SIG_1);
	pt2.DrawTable();
	cout << pt2.to_String() << endl;

	return 0;
} 
