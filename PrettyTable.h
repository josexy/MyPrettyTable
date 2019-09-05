
#ifndef MYSQLITE_PRETTYTABLE_H
#define MYSQLITE_PRETTYTABLE_H

#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <sstream>

#define PT_PLUS '+'
#define PT_H '-'
#define PT_V '|'
#define PT_DOT '.'
#define PT_EQUAL '='
#define PT_PADDING 1
#define PT_SIG_1 '@'
#define PT_SIG_2 '#'
#define PT_SIG_3 '$'
#define PT_SIG_4 '%'
#define PT_SIG_5 '\'
#define PT_SIG_6 '*'

using namespace std;

class PrettyTable {
private:
    stringstream m_ss;
    vector<string> m_Header;
    vector<vector<string> > m_Rows;
    int m_Max_Length;
    vector<vector<string> >m_Columns;
    vector<string>m_column;
    char m_Borders[3];
public:
    PrettyTable();
    PrettyTable(const vector<string>& __header);
    PrettyTable(string *__header);
    ~PrettyTable();

    void AddHeader(const vector<string>& __header);
    void AddRows(const vector<vector<string> >& __rows);
    void AddRow(const vector<string>& __row);
    void AddColumn(const vector<string>& __column);
    void AddColumns(const vector<vector<string>> & __columns);

    const string to_String();
    void SetBorderStyle(char _Corner='+', char _Border_h='-', char _Border_v='|');

protected:

    int _data_max_len_(const vector<string> &__vec);
    vector<string> _get_column(int index);
    void _put_NewLine();
    void _draw_header();
    void _draw_row();
    void _draw_lineBorder(char ch);
};

#endif //MYSQLITE_PRETTYTABLE_H
