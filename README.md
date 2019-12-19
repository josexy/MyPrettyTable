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
	vector<string>row1 = { "小明","1111111111","你好、我爱C++" };
	vector<string>row2 = { "小红","22222222222","你好？我爱Python" };
	vector<string>row3 = { "小光","3333333333333","你好，我爱PHP" };
	vector<vector<string>>vecs{ row1,row2,row3 };
	PrettyTable pt;
	try {
		pt.AddHeader(header);
		pt.AddRows(vecs);
        pt.SetAlign(PrettyTable::Align::Left);
		cout << pt << endl;
	}
	catch (Exception & e) {
		cout << e.what() << endl;
	}

	PrettyTable pt2;
	pt2.AddHeader({ "id","username","password" });
	pt2.AddRows({
		{"111","tony......","12345"},
		{"2222","mike","123"},
		{"33333","john","000"}
		});
    pt2.CancelFrameStyle();
    pt2.SetAlign(PrettyTable::Align::Internal);
	pt2.SetBorderStyle(Sign::PT_PLUS, Sign::PT_DOT, Sign::PT_SIG_1);
	pt2.DrawTable();
	cout << pt2.to_String() << endl;

	return 0;
} 
```

```
mkdir build&&cd build
cmake .. && make && ./PrettyTable
```
Output:
```
+------+---------------+------------------+
| 姓名 | 学号          | 信息             |
+------+---------------+------------------+
| 小明 | 1111111111    | 你好、我爱C++    |
| 小红 | 22222222222   | 你好？我爱Python |
| 小光 | 3333333333333 | 你好，我爱PHP    |
+------+---------------+------------------+

   id    username   password
  111   tony......   12345
  2222     mike       123
 33333     john       000
 
```

In Windows:

![image](https://github.com/josexy/MyPrettyTable/blob/master/photo_windows.png)

In Linux:

![image](https://github.com/josexy/MyPrettyTable/blob/master/photo_linux.png)

