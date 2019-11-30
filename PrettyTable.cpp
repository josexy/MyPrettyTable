
#ifdef WIN32
#pragma warning(disable:4996)
#endif
#include "PrettyTable.h"

PrettyTable::PrettyTable(){
    m_BorderStyle.Corner= static_cast<Sign>(Sign::PT_PLUS);
    m_BorderStyle.H= static_cast<Sign>(Sign::PT_H);
    m_BorderStyle.V= static_cast<Sign>(Sign::PT_V);
    this->m_Rows=0;
    this->m_Columns=0;
}
PrettyTable::~PrettyTable(){
    this->m_Rows=0;
    this->m_Columns=0;
    this->m_Header.clear();
    m_multiColumns.clear();
    m_multiRows.clear();
}
/**
 *  Set table border
 * @param _Corner suck as '+'
 * @param _Border_h such as '-'
 * @param _Border_v such as '|'
 */
void PrettyTable::SetBorderStyle(Sign _Corner, Sign _Border_h, Sign _Border_v){
    m_BorderStyle.Corner= _Corner;
    m_BorderStyle.H= _Border_h;
    m_BorderStyle.V= _Border_v;
}
/**
 * Return a string table
 * @return
 */
PrettyTable::String PrettyTable::to_String(){
    return m_innerOss.str();
}
/**
 * Add a header, it is necessary
 * @param _header
 */
void PrettyTable::AddHeader(const PrettyTable::StringArray& _header){
    this->m_Header=_header;
    this->m_Columns=this->m_Header.size();
    this->m_multiColumns.resize(this->m_Columns);
    for (int i = 0; i < this->m_Columns ; ++i) {
        this->m_multiColumns[i].push_back(_header[i]);
    }
}
/**
 * Add a row
 * @param _row
 */
void PrettyTable::AddRow(const PrettyTable::StringArray& _row){
    m_multiRows.push_back(_row);
    m_Rows++;
    if(this->m_Columns!=_row.size()){
        throw Exception("Header columns must be equal to Row columns!");
    }
    _RowConvertColumn(_row);
}
/**
 * Add multi rows
 * @param _rows
 */
void PrettyTable::AddRows(const PrettyTable::MultiStringArray & _rows){
    for (auto p : _rows){
        AddRow(p);
    }
}
/**
 * Start draw a table
 */
void PrettyTable::DrawTable(){
    _getMaximum_strLength();
    _draw_header();
    _draw_rows();
}
/**
 *  build header such as
 *  "+----------+------------------+----------+----------+---------------------+
 *  | xx        | xx              | xx       | xx       | xx                   |
 *  +----------+------------------+----------+----------+---------------------+
 */
void PrettyTable::_draw_header(){
    // draw top line
    // +----------+------------------+----------+----------+---------------------+
    _put_char(m_BorderStyle.Corner);
    for (int i = 0; i < this->m_Columns; ++i) {
        _put_chars(m_BorderStyle.H,this->m_ColumnsContent_max_len[i]+PADDING_LEFT_RIGHT);
        _put_char(m_BorderStyle.Corner);
    }
    _put_endline();
    // draw header data
    _put_char(m_BorderStyle.V);
    for (int i = 0; i < this->m_Columns; ++i) {
        m_innerOss<<' ';

        // Solve the Chinese characters problems
        // setw() = MaxSize + String.Size() - StringCapacity(String)
        // setw() = MaxSize + Length(Chinese hans)
        String str=m_Header[i];
#ifdef WIN32
        padding_left(this->m_ColumnsContent_max_len[i]);
#elif __linux__
        padding_left(this->m_ColumnsContent_max_len[i] + _get_Chinese_len(str));
#endif
        m_innerOss<<m_Header[i];

        m_innerOss<<' ';
        _put_char(m_BorderStyle.V);
    }
    _put_endline();

    // draw bottom line
    // +----------+------------------+----------+----------+---------------------+
    _put_char(m_BorderStyle.Corner);
    for (int i = 0; i < this->m_Columns; ++i) {
        _put_chars(m_BorderStyle.H,this->m_ColumnsContent_max_len[i]+PADDING_LEFT_RIGHT);
        _put_char(m_BorderStyle.Corner);
    }
    _put_endline();
}
/**
 *  draw alll rows
 */
void PrettyTable::_draw_rows(){
    for (int j = 0; j < this->m_Rows ; ++j) {
        _put_char(m_BorderStyle.V);
        for (int i = 0; i < this->m_Columns; ++i) {
            m_innerOss<<' ';

            // Solve the Chinese characters problems
            // setw() = MaxSize + String.Size() - StringCapacity(String)
            // setw() = MaxSize + Length(Chinese hans)
            String str=m_multiRows[j][i];
#ifdef WIN32
            padding_left(this->m_ColumnsContent_max_len[i]);
#elif __linux__
            padding_left(this->m_ColumnsContent_max_len[i] + _get_Chinese_len(str));
#endif
            m_innerOss<<m_multiRows[j][i];
            m_innerOss<<' ';
            _put_char(m_BorderStyle.V);
        }
        _put_endline();
    }
    // draw bottom line
    // +----------+------------------+----------+----------+---------------------+
    _put_char(m_BorderStyle.Corner);
    for (int i = 0; i < this->m_Columns; ++i) {
        _put_chars(m_BorderStyle.H,this->m_ColumnsContent_max_len[i]+PADDING_LEFT_RIGHT);
        _put_char(m_BorderStyle.Corner);
    }
    _put_endline();
}
/**
 *  get max  size() in columns stringArray
 * @return
 */
vector<int> PrettyTable::_getMaximum_strLength(){
    for (const StringArray & p: m_multiColumns ) {
        int m=StringCapacity(p[0]);
        for (int i = 0; i < p.size(); ++i) {
            if(m <=StringCapacity(p[i])){
                // real size
                m=StringCapacity(p[i]);
            }
        }
        m_ColumnsContent_max_len.push_back(m);
    }
    return m_ColumnsContent_max_len;
}
/**
 *  convert one row to column
 * @param _row
 */
void PrettyTable::_RowConvertColumn(const StringArray& _row){
    for (int i = 0; i < this->m_Columns ; ++i) {
        this->m_multiColumns[i].push_back(_row[i]);
    }
}
/**
 *  convert all rows to a columns array
 */
void PrettyTable::_RowsConvertColumns(){
    for(auto x: this->m_multiRows){
        _RowConvertColumn(x);
    }
}
/**
 *  deal with Chinese characters
 * @param str
 * @return
 */
wstring PrettyTable::StringToWString(const string & str){
    size_t nLen=str.length()*2;
    setlocale(LC_CTYPE,"");
    wchar_t *wcs=new wchar_t[nLen];
    wmemset(wcs,0,nLen);
    size_t s;
    mbstowcs(wcs,str.c_str(),nLen);
    wstring w=wcs;
    delete[]wcs;
    return w;
}
/**
 *  In UTF-8,
 *  If string include Chinese characters, it will obtain obvious characters
 *  Such as string s="你好cpp" :ouput 9-2=7
 *  But in Windows, maybe is not that :output 7-2=5
 * @param raw_str
 * @return
 */
int PrettyTable::StringCapacity(const string & raw_str){
#ifdef WIN32
    return raw_str.size();
#elif __linux__
    return raw_str.size() - this->_get_Chinese_len(raw_str);
#endif
}
/**
 * Get number of Chinese characters and punctuation character from a string
 * @param str
 * @return
 */
int PrettyTable::_get_Chinese_len(const string& str){
    wstring ss=StringToWString(str);
    int sum=0;
    for (int i = 0; i <ss.length() ; ++i) {
        wchar_t wcs=ss.c_str()[i];
        if((wcs>=0x4E00u&&wcs<=0x9FFFu)
           ||wcs==PC1||wcs==PC2||wcs==PC3||wcs==PC4||wcs==PC5||wcs==PC6||wcs==PC7||wcs==PC8||wcs==PC9
           ||wcs==PC10||wcs==PC11||wcs==PC12||wcs==PC13||wcs==PC14||wcs==PC15||wcs==PC16||wcs==PC17
           ||wcs==PC18||wcs==PC19||wcs==PC20||wcs==PC21||wcs==PC22||wcs==PC23||wcs==PC24||wcs==PC25){
            sum++;
        }
    }
    return sum;
}
