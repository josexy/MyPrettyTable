
#ifdef WIN32
#pragma warning(disable:4996)
#endif
#include "PrettyTable.h"

PrettyTable::PrettyTable() {
    m_BorderStyle.Corner = static_cast<Sign>(Sign::PT_PLUS);
    m_BorderStyle.H = static_cast<Sign>(Sign::PT_H);
    m_BorderStyle.V = static_cast<Sign>(Sign::PT_V);
    this->m_Rows = 0;
    this->m_Columns = 0;
    this->is_cancelFrame= false;
    this->is_DrawTable = false;
    this->m_Header._align = Align::Left;
}
PrettyTable::~PrettyTable() {
    this->Cleanup();
}
/**
 *  Set table border
 * @param _Corner suck as '+'
 * @param _Border_h such as '-'
 * @param _Border_v such as '|'
 */
void PrettyTable::SetBorderStyle(Sign _Corner, Sign _Border_h, Sign _Border_v) {
    m_BorderStyle.Corner = _Corner;
    m_BorderStyle.H = _Border_h;
    m_BorderStyle.V = _Border_v;
}
/**
 * Return a string table
 * @return
 */
PrettyTable::String PrettyTable::to_String(int _start, int _end) {
    if (!this->is_DrawTable) {
        _draw_table(_start, _end);
    }
    return m_innerOss.str();
}
/**
 * Add a header, it is necessary
 * @param _header
 */
void PrettyTable::AddHeader(const PrettyTable::StringArray& _header, Align _align) {
    if(_header.empty())
        throw Exception("Not have a _header_");
    if(_align!=Align::Left)
        this->m_Header._align = _align;
    this->m_Header._header = _header;
    this->m_Columns = this->m_Header._header.size();
    // init resize the header columns
    this->m_multiColumns.resize(this->m_Columns);
    for (int i = 0; i < this->m_Columns; ++i) {
        this->m_multiColumns[i].push_back(_header[i]);
    }
}
/**
 * Add a row
 * @param _row
 */
void PrettyTable::AddRow(const PrettyTable::StringArray& _row) {
    if(_row.size()<=0)
        return;
    m_multiRows.push_back(_row);
    m_Rows++;
    if (this->m_Columns != _row.size()) {
        throw Exception("Header columns must be equal to Row columns!");
    }
    _RowConvertColumn(_row);
}
/**
 * Add multi rows
 * @param _rows
 */
void PrettyTable::AddRows(const PrettyTable::MultiStringArray& _rows) {
    for (auto p : _rows) {
        AddRow(p);
    }
}
/**
 * Add a column
 * @param _column
 */
void PrettyTable::AddColumn(const String& _header_title, const StringArray& _column) {
    if (this->m_Columns) {
        this->m_Columns++;
        // resize the header columns
        this->m_multiColumns.push_back(_column);
        this->m_Header._header.push_back(_header_title);
        // convert column to a row
        for (int i = 0; i < this->m_Rows; ++i) {
            this->m_multiRows[i].push_back(_column[i]);
        }
    }
}
/**
 * Start draw a table
 * Note that this function will draw all rows!
 * So after you call this method, you also call to_String(s,e) with two parameters, it is invalid
 */
void PrettyTable::DrawTable() {
    _draw_table(1, -1);
}
/**
 *  Draw a table from the _s row to _e row
 */
void PrettyTable::_draw_table(int s, int e) {
    _getMaximum_strLength();
    _draw_header();
    _draw_rows(s, e);
    this->is_DrawTable = true;
}
/**
 *  build header such as
 *  +----------+------------------+----------+----------+---------------------+
 *  | xx        | xx              | xx       | xx       | xx                   |
 *  +----------+------------------+----------+----------+---------------------+
 */
void PrettyTable::_draw_header() {
    if (this->m_Columns <= 0)return;
    // draw top line
    // +----------+------------------+----------+----------+---------------------+
    if(!this->is_cancelFrame){
        _put_char(m_BorderStyle.Corner);
        for (int i = 0; i < this->m_Columns; ++i) {
            _put_chars(m_BorderStyle.H, this->m_ColumnsContent_max_len[i] + PADDING_LEFT_RIGHT);
            _put_char(m_BorderStyle.Corner);
        }
        _put_endline();
    }
    // draw header data
    if(!this->is_cancelFrame)
        _put_char(m_BorderStyle.V);

    for (int i = 0; i < this->m_Columns; ++i) {
        int _PADDING = 0;
        // Solve the Chinese characters problems
        // setw() = MaxSize + String.Size() - StringCapacity(String)
        // setw() = MaxSize + Length(Chinese hans)
        String str = m_Header._header[i];
#ifdef WIN32
        _PADDING = this->m_ColumnsContent_max_len[i];
#elif __linux__
        _PADDING = this->m_ColumnsContent_max_len[i] + _get_Chinese_len(str);
#endif
        m_innerOss << ' ';
        if(!this->is_cancelFrame){
            padding(_PADDING, m_Header._align);
        }
        if (m_Header._align == Align::Internal) {
#ifdef WIN32
            int s1 = (PADDING_LEFT_RIGHT / 2 + this->m_ColumnsContent_max_len[i]) / 2 + (StringCapacity(str)) / 2;
			int s2 = this->m_ColumnsContent_max_len[i] - s1;
#elif __linux__
            int s1 = (PADDING_LEFT_RIGHT / 2 + this->m_ColumnsContent_max_len[i]) / 2 + (StringCapacity(str)) / 2 + _get_Chinese_len(str);
            int s2 = this->m_ColumnsContent_max_len[i] - s1 + _get_Chinese_len(str);
#endif
            m_innerOss << right << setw(s1)
                       << str
                       << left << setw(s2)
                       << "";
        }
        else {
            m_innerOss << str;
        }
        m_innerOss << ' ';
        if(!this->is_cancelFrame)
            _put_char(m_BorderStyle.V);
    }
    _put_endline();

    // draw bottom line
    // +----------+------------------+----------+----------+---------------------+
    if(!this->is_cancelFrame){
        _put_char(m_BorderStyle.Corner);
        for (int i = 0; i < this->m_Columns; ++i) {
            _put_chars(m_BorderStyle.H, this->m_ColumnsContent_max_len[i] + PADDING_LEFT_RIGHT);
            _put_char(m_BorderStyle.Corner);
        }
        _put_endline();
    }
}
/**
 *  draw alll rows
 */
void PrettyTable::_draw_rows(int s, int e) {
    if (this->m_Rows <= 0 || s < 0)return;
    if (s == 1 && e == -1) {
        s = 1;
        e = this->m_Rows;
    }
    if (s > e)return;
    // deal with index overflow
    if (e >= this->m_Rows) {
        e = this->m_Rows;
    }
    for (int j = 0; j < this->m_Rows; ++j) {
        if ((j + 1) < s || (j + 1) > e)continue;
        if(!this->is_cancelFrame)
            _put_char(m_BorderStyle.V);
        for (int i = 0; i < this->m_Columns; ++i) {
            int _PADDING = 0;
            // Solve the Chinese characters problems
            // setw() = MaxSize + String.Size() - StringCapacity(String)
            // setw() = MaxSize + Length(Chinese hans)
            String str = m_multiRows[j][i];
#ifdef WIN32
            _PADDING = this->m_ColumnsContent_max_len[i];
#elif __linux__
            _PADDING = this->m_ColumnsContent_max_len[i] + _get_Chinese_len(str);
#endif
            m_innerOss << ' ';
            if(!this->is_cancelFrame)
                padding(_PADDING, m_Header._align);
            // do with the internal aligning condition
            if (m_Header._align == Align::Internal) {
#ifdef WIN32
                int s1 = (PADDING_LEFT_RIGHT / 2 + this->m_ColumnsContent_max_len[i]) / 2 + (StringCapacity(str)) / 2;
				int s2 = this->m_ColumnsContent_max_len[i] - s1;
#elif __linux__
                int s1 = (PADDING_LEFT_RIGHT / 2 + this->m_ColumnsContent_max_len[i]) / 2 + (StringCapacity(str)) / 2 + _get_Chinese_len(str);
                int s2 = this->m_ColumnsContent_max_len[i] - s1 + _get_Chinese_len(str);
#endif
                m_innerOss << right << setw(s1)
                           << str
                           << left << setw(s2)
                           << "";
            }else {
                m_innerOss << str;
            }
            m_innerOss << ' ';
            if(!this->is_cancelFrame)
                _put_char(m_BorderStyle.V);
        }
        _put_endline();
    }
    // draw bottom line
    // +----------+------------------+----------+----------+---------------------+
    if(!this->is_cancelFrame){
        _put_char(m_BorderStyle.Corner);
        for (int i = 0; i < this->m_Columns; ++i) {
            _put_chars(m_BorderStyle.H, this->m_ColumnsContent_max_len[i] + PADDING_LEFT_RIGHT);
            _put_char(m_BorderStyle.Corner);
        }
        _put_endline();
    }
}
/**
 *  get max  size() in columns stringArray
 * @return
 */
vector<int> PrettyTable::_getMaximum_strLength() {
    for (const StringArray& p : m_multiColumns) {
        int m = StringCapacity(p[0]);
        for (int i = 0; i < p.size(); ++i) {
            if (m <= StringCapacity(p[i])) {
                // real size
                m = StringCapacity(p[i]);
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
void PrettyTable::_RowConvertColumn(const StringArray& _row) {
    for (int i = 0; i < this->m_Columns; ++i) {
        this->m_multiColumns[i].push_back(_row[i]);
    }
}
/**
 *  convert all rows to a columns array
 */
void PrettyTable::_RowsConvertColumns() {
    for (auto x : this->m_multiRows) {
        _RowConvertColumn(x);
    }
}
/**
 *  deal with Chinese characters
 * @param str
 * @return
 */
wstring PrettyTable::StringToWString(const string& str) {
    size_t nLen = str.length() * 2;
    setlocale(LC_CTYPE, "");
    wchar_t* wcs = new wchar_t[nLen];
    wmemset(wcs, 0, nLen);
    size_t s;
    mbstowcs(wcs, str.c_str(), nLen);
    wstring w = wcs;
    delete[]wcs;
    return w;
}
/**
 *  In UTF-8,
 *  If string include Chinese characters, it will obtain obvious characters
 *  Such as string s="你好cpp" :ouput 9-2=7
 *  But in Windows, this is will output: 7
 * @param raw_str
 * @return
 */
int PrettyTable::StringCapacity(const string& raw_str) {
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
int PrettyTable::_get_Chinese_len(const string& str) {
    wstring ss = StringToWString(str);
    int sum = 0;
    for (int i = 0; i < ss.length(); ++i) {
        wchar_t wcs = ss.c_str()[i];
        if ((wcs >= 0x4E00u && wcs <= 0x9FFFu)
            || wcs == PC1 || wcs == PC2 || wcs == PC3 || wcs == PC4 || wcs == PC5 || wcs == PC6 || wcs == PC7 || wcs == PC8 || wcs == PC9
            || wcs == PC10 || wcs == PC11 || wcs == PC12 || wcs == PC13 || wcs == PC14 || wcs == PC15 || wcs == PC16 || wcs == PC17
            || wcs == PC18 || wcs == PC19 || wcs == PC20 || wcs == PC21 || wcs == PC22 || wcs == PC23 || wcs == PC24 || wcs == PC25) {
            sum++;
        }
    }
    return sum;
}

/**
 * Set the table aligning
 * @param align
 */
void PrettyTable::SetAlign(Align align) {
    this->m_Header._align = align;
}

/**
 * Save file
 * @param _file_path
 */
void PrettyTable::OutputFile(const string& _file_path) {
    m_FileOut.open(_file_path);
    if (!m_FileOut.is_open())return;
    if (!this->is_DrawTable)this->DrawTable();
    m_FileOut << m_innerOss.str();
    m_FileOut.close();
}

/**
 * Finally clean all data and end up...
 */
void PrettyTable::Cleanup() {
    this->is_cancelFrame=false;
    this->m_Rows = 0;
    this->m_Columns = 0;
    this->m_Header._header.clear();
    for (int i = 0; i < m_multiColumns.size(); ++i)
        this->m_multiColumns[i].clear();
    this->m_multiColumns.clear();
    for (int j = 0; j <m_multiRows.size() ; ++j)
        this->m_multiRows[j].clear();
    this->m_multiRows.clear();
    this->m_ColumnsContent_max_len.clear();
    this->m_innerOss.clear();
    this->m_innerOss.ignore();
    this->m_FileOut.clear();
}
