
#ifndef PRETTYTABLE_PRETTYTABLE_H
#define PRETTYTABLE_PRETTYTABLE_H

#include <string>
#include <iomanip>
#include <vector>
#include <sstream>
#include <fstream>
#include <exception>
#include "Sign.h"

using std::string;
using std::exception;
using std::vector;
using std::stringstream;
using std::wstring;
using std::ostream;
using std::ofstream;
using std::endl;
using std::setw;
using std::left;
using std::right;

// Default space takes two bytes
#define PADDING_LEFT_RIGHT 2

#ifdef WIN32
#define PTF_WINDOWS WIN32
#endif
#ifdef __linux__
#define PTF_LINUX __linux__
#endif
#if __unix__
#define PTF_UNIX __unix__
#endif
#if __APPLE__
#define PTF_MAC __APPLE__
#endif

#ifdef PTF_WINDOWS
#pragma warning(disable:4996)
#endif

class Exception :public exception {
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
public:
    explicit PrettyTable();
    ~PrettyTable();
    /**
     * Cancel the border frame style
     */
    void CancelFrameStyle(){is_cancelFrame=true;}
    /**
     *  Set table border
     * @param _Corner suck as '+'
     * @param _Border_h such as '-'
     * @param _Border_v such as '|'
     */
    void SetBorderStyle(Sign _Corner = Sign::PT_PLUS, Sign _Border_h = Sign::PT_V, Sign _Border_v = Sign::PT_H);
    /**
     *  Return a string table
     * @param _start
     * @param _end
     * @return
     */
    String to_String(int _start = 1, int _end = -1);
    /**
     * Add a header, it is necessary
     * @param _header
     * @param _align
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
     * @param _header_title
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
    friend ostream& operator<<(ostream& out, PrettyTable& pt) {out << pt.to_String();return out;}
protected:
    void _draw_header();
    void _draw_rows(int, int);
    void _draw_table(int, int);
    const vector<int>& _getMaximum_strLength();

    void _RowConvertColumn(const StringArray& _row);
    void _RowsConvertColumns();
    void padding(int n, Align align = Align::Left) {
        switch (align) {
            case Align::Left: {
                m_innerOss << left << setw(n);
            }break;
            case Align::Right: {
                m_innerOss << right << setw(n);
            }break;
            default: {
                m_innerOss << left << setw(n);
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
    void _put_endline(){m_innerOss << endl;}
    void _cleanup();

    /**
     *  Deal with Chinese characters
     * @param str
     * @return
     */
    wstring StringToWString(const string& str);
    /**
     *  In UTF-8,
     *  If string include Chinese characters, it will obtain obvious characters
     *  Such as string s="你好cpp" :ouput 9-2=7
     *  But in Windows, this is will output: 7
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
private:
    stringstream m_innerOss;
    int m_Rows;
    int m_Columns;
    Header m_Header;
    MultiStringArray m_multiRows;
    BorderStyle m_BorderStyle;
    MultiStringArray m_multiColumns;
    vector<int>m_ColumnsContent_max_len;
    ofstream m_FileOut;
    bool is_DrawTable;
    bool is_cancelFrame;
};

#endif
