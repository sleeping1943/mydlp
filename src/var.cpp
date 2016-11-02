/************************************
*
*此源文件
*filename : var.cpp
*author   : sleeping
*email    : csleeping@163.com
*date     : 2016年11月01日 星期二 11时50分46秒
*
************************************/
#include "var.h"
#include <algorithm>
#include <utility>
#include <iostream>

namespace slp{namespace script{

        using std::cout;
        using std::endl;

        var::var() { 
            cout << "\033[31m调用构造函数!\033[m" << endl;
            init(); 
        }

        var::~var() {
            cout << "\033[31m~var()调用析构函数！\033[m" << endl;
            clear();
        }

        var::var(const var& that) {
            cout << "\033[31m调用拷贝构造函数!\033[m" << endl;
            init(); 
            switch (that.type()) {
                case t_int: 
                    this->m_number = that.get_number();
                    break;
                case t_str: 
                    if (isinit && m_content) {
                        cout << __func__ << *m_content << endl;
                        delete m_content;
                    }
                    m_content = new std::string;
                    *m_content = that.get_str();
                    break;
                case t_bin: 
                    if (isinit && m_content) {
                        delete m_content; 
                    }
                    m_content = new std::string;
                    *m_content = that.get_bin();
                    break;
                case t_array: 
                    if (isinit && m_array) {
                        delete m_array; 
                    }
                    m_array = new std::vector<var>;
                    for (const var& tmp : that.get_array()) {
                        m_array->push_back(tmp);
                    }
                    break;
                case t_map: 
                    if (isinit && m_map) {
                        delete m_map; 
                    }
                    m_map = new std::map<var,var>;
                    for (const auto& it : that.get_map()) {
                        m_map->insert(std::pair<var,var>(it.first,it.second));
                    }
                    break;
                case t_unknow:
                default:
                    throw invalid_exception();
                    break;
            }
            this->m_type = that.type();
        }

        var& var::operator = (const var& that) {
            cout << "\033[31m~var()调用拷贝赋值函数！\033[m" << endl;
            var tmp(that);
            std::swap(*this,tmp);
            return *this;
        }


        var& var::operator = (const int& i) {
            cout << "\033[31m调用operator=(int)函数！\033[m" << endl;
            this->m_type = t_int; 
            this->m_number = i;
            return *this;
        }

        var& var::operator = (const std::string& str) {
            cout << "\033[31m调用operator=(string)函数！\033[m" << endl;
            this->m_type = t_str;
            if (m_content) {
                delete m_content; 
                m_content = NULL;
            }

            m_content = new std::string;
            *m_content = str;
            return *this;
        }


        std::ostream& operator << (std::ostream& os, const var& that) {
            switch (that.m_type) {
                case t_int:
                    os << that.m_number;
                    break;
                case t_str:
                    if (that.m_content) {
                        os << *(that.m_content);
                    } else {
                        os << "{null}"; 
                    }
                    break;
                case t_bin:
                    if (that.m_content) {
                        os.write(that.m_content->data(),that.m_content->size());
                    } else {
                        os << "{null}";
                    }
                    break;
                case t_array:
                    /*
                     *TODO
                     */
                    break;
                case t_map:
                    /*
                     *TODO
                     */
                    break;
                case t_unknow:
                default:
                    os << "\033[31minvalid value~\033[m" << endl;
                    break;
            } 

            return os;
        }
        bool var::operator < (const var& that) const {
            /*
             *TODO 各种数据的比较大小
             */
            return true; 
        }
        
        void var::clear() {
            switch (this->type()) {
                case t_int: 
                    this->m_number = 0;
                    break;
                case t_str: 
                case t_bin: 
                    if (isinit && m_content) {
                        delete m_content;
                        m_content = NULL;
                    }
                    break;
                case t_array: 
                    if (isinit && m_array) {
                        delete m_array;
                        m_array = NULL;
                    }
                    break;
                case t_map: 
                    if (isinit && m_map) {
                        delete m_map;
                        m_map = NULL;
                    }
                    break;
                case t_unknow:
                default:
                    /*
                     *throw invalid_exception();
                     */
                    break;
            } 
            m_type = t_unknow;
            isinit = true;
        }


        void var::print_type() const {
            switch (m_type) {
                case t_int:     
                    cout << "{int}" << endl;
                    break;
                case t_str:     
                    cout << "{string}" << endl;
                    break;
                case t_bin:     
                    cout << "{binary}" << endl;
                    break;
                case t_array:     
                    cout << "{array}" << endl;
                    break;
                case t_map:     
                    cout << "{map}" << endl;
                    break;
                case t_unknow:     
                default:
                    cout << "{unknow}" << endl;
                    break;
            }
        }

        /*
         *void var::push_back(const var& v) {
         *    if (t_unknow != m_type && t_array != m_type) {
         *        throw invalid_exception("neither t_unknow nor t_array");
         *    } else {
         *        m_type = t_array;
         *        if (!m_array) {
         *            m_array = new std::vector<var>; 
         *        }
         *    }
         *    m_array->push_back(v);
         *}
         */
}};
