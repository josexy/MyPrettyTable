
#ifndef PRETTYTABLE_PRETTYTABLE_H
#define PRETTYTABLE_PRETTYTABLE_H
#include <iostream>
#include <exception>
#include <iomanip>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include "Sign.h"

using namespace std;

// Default space takes two bytes
#define PADDING_LEFT_RIGHT 2

class Exception :public  exception {
private:
    string m_str_error;
public:
    Exception(const string& str_error) :exception{}, m_str_error{ str_error }{}
    const char* what() {
        return m_str_error.c_str();
    }
};

/**
 *  PrettyTable can format and print a table from data
 */
class PrettyTable {
public:

    // align type
    enum class Align {
        Left,
        Right,
        Internal
    };
    struct BorderStyle {
        Sign Corner;
        Sign H;
        Sign V;
    };
    typedef string String;
    typedef vector<string> StringArray;
    typedef vector<vector<string>> MultiStringArray;
    struct Header {
        Align _align;
        StringArray _header;
    };
private:
    stringstream m_innerOss;
    int m_Rows;
    int m_Columns;
    // header
    Header m_Header;
    // all rows
    MultiStringArray m_multiRows;
    // border style
    BorderStyle m_BorderStyle;
    // all columns
    MultiStringArray m_multiColumns;
    vector<int>m_ColumnsContent_max_len;
    bool is_DrawTable;
    ofstream m_FileOut;
public:
    friend ostream& operator<<(ostream& out, PrettyTable& pt) {
        out << pt.to_String();
        return out;
    }
    PrettyTable();
    ~PrettyTable();
    /**
     *  Set table border
     * @param _Corner suck as '+'
     * @param _Border_h such as '-'
     * @param _Border_v such as '|'
     */
    void SetBorderStyle(Sign _Corner = Sign::PT_PLUS, Sign _Border_h = Sign::PT_V, Sign _Border_v = Sign::PT_H);
    /**
     * Return a string table
     * @return
     */
    String to_String(int _start = 1, int _end = -1);
    /**
     * Add a header, it is necessary
     * @param _header
     */
    void AddHeader(const StringArray& _header, Align _align = Align::Left);
    /**
     * Add a row
     * @param _row
     */
    void AddRow(const StringArray& _row);
    /**
     * Add multi rows
     * @param _rows
     */
    void AddRows(const MultiStringArray& _rows);
    /**
     * Add a column
     * @param _column
     */
    void AddColumn(const String& _header_title, const StringArray& _column);
    /**
     * Start draw a table
     */
    void DrawTable();

    /**
     * Set table content aligning
     */
    void SetAlign(Align align = Align::Left);

    /**
     *  Save to file on disk
     * @param _file_path
     */
    void OutputFile(const string& _file_path = "output_table.txt");

private:
    /**
     *  build header such as
     */
    void _draw_header();
    /**
     *  draw alll rows
     */
    void _draw_rows(int, int);

    /**
     *  draw a complete table
     */
    void _draw_table(int, int);
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

    /**
     * ALIGNING
     * Align::Left  Align::Right
     * @param n
     * @param align
     */
    void padding(int n, Align align = Align::Left) {
        switch (align) {
            case Align::Left: {
                m_innerOss << left << setw(n);
            }break;
            case Align::Right: {
                m_innerOss << right << setw(n);
            }break;
        }
    }

    void _put_chars(const Sign c, int n) {
        for (int i = 0; i < n; ++i) {
            _put_char(c);
        }
    }
    void _put_char(const Sign c) {
        m_innerOss << (static_cast<char>(c));
    }
    void _put_endline() {
        m_innerOss << endl;
    }
    /**
     *  deal with Chinese characters
     * @param str
     * @return
     */
    wstring StringToWString(const string& str);
    /**
     *  In UTF-8,
     *  If string include Chinese characters, it will obtain obvious characters
     *  Such as string s="你好cpp", ouput 9-2=7
     * @param raw_str
     * @return
     */
    int StringCapacity(const string& raw_str);
    /**
     * Get number of Chinese characters from a string
     * @param str
     * @return
     */
    int _get_Chinese_len(const string& str);
};

#endif //PRETTYTABLE_PRETTYTABLE_H
