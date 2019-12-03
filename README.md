# MyPrettyTable
Print Table with C++ like mysql.
It also supports Chinese characters.

Source file:
```
#include <iostream>
#include "PrettyTable.h"
using namespace std;

int main() {
	vector<string>header = { "姓名","学号","信息" };
	vector<string>row1 = { "张小飞","1111111111","你好、我爱C++" };
	vector<string>row2 = { "关小羽","22222222222","你好？我爱Python" };
	vector<string>row3 = { "刘小备","3333333333333","你好，我爱PHP" };
	vector<vector<string>>vecs{ row1,row2,row3 };
	PrettyTable pt;
	try {
		pt.AddHeader(header);
		pt.AddRows(vecs);
        pt.SetAlign(PrettyTable::Align::Internal);
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
    pt2.SetAlign(PrettyTable::Align::Internal);
	pt2.SetBorderStyle(Sign::PT_PLUS, Sign::PT_DOT, Sign::PT_SIG_1);
	pt2.DrawTable();
	cout << pt2.to_String() << endl;

	return 0;
} 

```

```
g++ test.cpp PrettyTable.cpp -o test
./test
```
Output:
```
+--------+---------------+------------------+
|  姓名  |      学号     |       信息       |
+--------+---------------+------------------+
| 张小飞 |   1111111111  |  你好、我爱C++   |
| 关小羽 |  22222222222  | 你好？我爱Python |
| 刘小备 | 3333333333333 |  你好，我爱PHP   |
+--------+---------------+------------------+

+......+............+..........+
@  id  @  username  @ password @
+......+............+..........+
@ 111  @ tony...... @  12345   @
@ 222  @    mike    @   123    @
@ 3333 @    john    @   000    @
+......+............+..........+

```

In Windows:

![image](https://github.com/josexy/MyPrettyTable/blob/master/photo_windows.png)

In Linux:

![image](https://github.com/josexy/MyPrettyTable/blob/master/photo_linux.png)

