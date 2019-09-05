
#include "PrettyTable.h"

PrettyTable::PrettyTable(){
    this->SetBorderStyle();
}

PrettyTable::PrettyTable(const vector<string> &__header) {
    this->SetBorderStyle();
    for (int i = 0; i <__header.size() ; ++i) {
        this->m_Header.push_back(__header[i]);
    }
}

PrettyTable::PrettyTable(string *__header) {
    this->SetBorderStyle();
    if(__header&&__header->size()>0){
        for (int i = 0; i <__header->size() ; ++i) {
            this->m_Header.push_back(__header[i]);
        }
    }
}
PrettyTable::~PrettyTable(){
}

/// Add header
/// \param __header
void PrettyTable::AddHeader(const vector<string>& __header){
    if(__header.size()>0&&this->m_Header.size()<=0) {
        for (int i = 0; i < __header.size(); ++i) {
            this->m_Header.push_back(__header[i]);
        }
    }
}
/// Add rows
/// \param __rows
void PrettyTable::AddRows(const vector<vector<string> >& __rows){
    for (int i = 0; i < __rows.size(); ++i) {
        m_Rows.push_back(__rows[i]);
    }
}

/// Add one row
/// \param __row
void PrettyTable::AddRow(const vector<string>& __row){
    m_Rows.push_back(__row);
}

/// Add column(include header name)
/// \param __column
void PrettyTable::AddColumn(const vector<string>& __column){
    for (int i = 0; i < __column.size(); ++i) {
        this->m_column.push_back(__column.at(i));
    }
}
/// Add columns
/// \param __columns
void PrettyTable::AddColumns(const vector<vector<string>> & __columns){
    for (int i = 0; i <__columns.size() ; ++i) {
        this->m_Columns.push_back(__columns[i]);
    }
}

/// 取最大长度
/// \param __vec
/// \return
int PrettyTable::_data_max_len_(const vector<string> &__vec){
    int n=0;
    if(__vec.size()<=0){ return 0;}
    for (int i = 0; i <__vec.size(); ++i) {
        int t=__vec[i].size();
        if(t>n) n=t;
    }
    return n;
}

/// 从指定索引获取列
/// \param index
/// \return
vector<string> PrettyTable::_get_column(int index){
    this->m_column.clear();
    this->m_column.push_back(m_Header[index]);
    for (int i = 0; i <this->m_Rows.size() ; ++i) {
        this->m_column.push_back(m_Rows[i][index]);
    }
    return this->m_column;
}

void PrettyTable::_put_NewLine(){
    m_ss<<endl;
}

/// 输出表格头
void PrettyTable::_draw_header(){
    _draw_lineBorder(m_Borders[1]);
    _put_NewLine();

    m_ss<<m_Borders[2];
    for (int j = 0; j <this->m_Header.size() ; ++j) {
        this->m_Max_Length=_data_max_len_(this->_get_column(j));
        m_ss<<' '<<left<<setw(this->m_Max_Length)<<this->m_Header.at(j)<<' ';
        m_ss<<m_Borders[2];
    }
    _put_NewLine();
    _draw_lineBorder(m_Borders[1]);
    _put_NewLine();

}
///输出表格数据
void PrettyTable::_draw_row(){
    for (int i = 0; i < this->m_Rows.size(); ++i) {
        m_ss<<m_Borders[2];
        for (int j = 0; j < this->m_Rows[0].size(); ++j) {
            this->m_Max_Length=_data_max_len_(this->_get_column(j));
            m_ss<<' '<<left<<setw(this->m_Max_Length)<<this->m_Rows[i][j]<<' ' ;
            m_ss<<m_Borders[2];
        }
        _put_NewLine();
    }
    _draw_lineBorder(m_Borders[1]);
    _put_NewLine();
}
///输出表格边框
void PrettyTable::_draw_lineBorder(char ch){
    for (int j = 0; j <this->m_Header.size() ; ++j) {
        this->m_Max_Length=_data_max_len_(this->_get_column(j));
        m_ss<<m_Borders[0];
        for (int i = 0; i < this->m_Max_Length+PT_PADDING*2; ++i) {
            m_ss<<ch;
        }
    }
    m_ss<<m_Borders[0];
}
/// 转换为字符串格式
/// \return
const string PrettyTable::to_String(){
    _draw_header();
    _draw_row();

    return this->m_ss.str();
}

/// 设置边框样式
/// \param _Corner
/// \param _Border_h
/// \param _Border_v
void PrettyTable::SetBorderStyle(char _Corner,char _Border_h,char _Border_v) {
    m_Borders[0]=_Corner;
    m_Borders[1]=_Border_h;
    m_Borders[2]=_Border_v;
}


