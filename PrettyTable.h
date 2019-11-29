
#ifndef PRETTYTABLE_PRETTYTABLE_H
#define PRETTYTABLE_PRETTYTABLE_H
#include <iostream>
#include <exception>
#include <iomanip>
#include <vector>
#include <string>
#include <sstream>
#include "Sign.h"
#include "myTermColor.h"

using namespace std;

// Default space takes two bytes
#define PADDING_LEFT_RIGHT 2

class Exception:public  exception{
private:
    string m_str_error;
public:
    Exception(const string& str_error):exception{},m_str_error{str_error}{}
    const char* what(){
        return m_str_error.c_str();
    }
};

/**
 *  PrettyTable can format and print a table from data
 */
class PrettyTable {
public:
    struct BorderStyle{
        Sign Corner;
        Sign H;
        Sign V;
    };
    typedef string String;
    typedef vector<string> StringArray;
    typedef vector<vector<string>> MultiStringArray;

private:
    stringstream m_innerOss;
    int m_Rows;
    int m_Columns;
    // header
    StringArray m_Header;
    // all rows
    MultiStringArray m_multiRows;
    // border style
    BorderStyle m_BorderStyle;
    // all columns
    MultiStringArray m_multiColumns;
    vector<int>m_ColumnsContent_max_len;

public:
    PrettyTable();
    ~PrettyTable();
    /**
     *  Set table border
     * @param _Corner suck as '+'
     * @param _Border_h such as '-'
     * @param _Border_v such as '|'
     */
    void SetBorderStyle(Sign _Corner=Sign::PT_PLUS, Sign _Border_h=Sign::PT_V, Sign _Border_v=Sign::PT_H);
    /**
     * Return a string table
     * @return
     */
    String to_String();
    /**
     * Add a header, it is necessary
     * @param _header
     */
    void AddHeader(const StringArray& _header);
    /**
     * Add a row
     * @param _row
     */
    void AddRow(const StringArray& _row);
    /**
     * Add multi rows
     * @param _rows
     */
    void AddRows(const MultiStringArray & _rows);
    /**
     * Start draw a table
     */
    void DrawTable();
private:
    /**
     *  build header such as
     */
    void _draw_header();

    /**
     *  draw alll rows
     */
    void _draw_rows();

    /**
     *  get max  size() in columns stringArray
     * @return
     */
    vector<int> _getMaximum_strLength();
    /**
     *  convert one row to column
     * @param _row
     */
    void _RowConvertColumn(const StringArray& _row);
    /**
     *  convert all rows to a columns array
     */
    void _RowsConvertColumns();

    void padding_left(int n){m_innerOss<<left<<setw(n);}
    void padding_right(int n){m_innerOss<<right<<setw(n);}
    void padding_internal(int n){m_innerOss<<internal<<setw(n);}

    void _put_chars(const Sign c ,int n){
        for (int i = 0; i < n ; ++i) {
            _put_char(c);
        }
    }
    void _put_char(const Sign c){
        m_innerOss<<(static_cast<char>(c));
    }
    void _put_endline(){
        m_innerOss<<endl;
    }
    /**
     *  deal with Chinese characters
     * @param str
     * @return
     */
    wstring StringToWString(const string & str);
    /**
     *  In UTF-8,
     *  If string include Chinese characters, it will obtain obvious characters
     *  Such as string s="你好cpp", ouput 9-2=7
     * @param raw_str
     * @return
     */
    int StringCapacity(const string & raw_str);
    /**
     * Get number of Chinese characters from a string
     * @param str
     * @return
     */
    int _get_Chinese_len(const string& str);
};

#endif //PRETTYTABLE_PRETTYTABLE_H
