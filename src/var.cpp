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
            print_info("调用构造函数!",false);
            init(); 
        }


        var::var(int i) {
            print_info("调用构造函数var(int i)!",false);
            init(); 
            m_type = t_int;
            this->m_number = i;
        } 


        var::var(bool b) {
            print_info("调用构造函数var(bool b)!",false);
            init(); 
            m_type = t_bool;
            this->m_bool = b;
        }

        var::var(const char* pstr) {
            print_info("调用构造函数var(const char* pstr)!",false);
            init(); 
            m_type = t_str;
            m_content = new std::string;
            m_content->append(pstr);
        }

        var::var(const std::string& str) {
            print_info("调用构造函数var(const string& str)!",false);
            init(); 
            m_type = t_str;
            m_content = new std::string;
            *m_content = str;
        }


        var::var(const varray& arr) {
            print_info("调用构造函数var(const varray& arr)!",false);
            init();
            m_type = t_array;
            if (isinit && m_array) {
                delete m_array;
                m_array = NULL;
            }

            m_array = new varray;
            for (const auto& t : arr) {
                m_array->push_back(t);
            }
        }

        var::var(const vmap& m) {
            print_info("调用构造函数var(const vmap& m)!",false);
            init(); 
            m_type = t_map;
            if (isinit && m_map) {
                delete m_map;
                m_map = NULL;
            }

            m_map = new vmap;
            for (const auto& t : m) {
                m_map->insert(std::pair<var,var>(t.first,t.second)); 
            }
        }

        var::~var() {
            print_info("~var()调用析构函数！",false);
            clear();
        }

        var::var(const var& that) {
            print_info("调用拷贝构造函数!",false);
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
                case t_bool:
                    this->m_bool = that.m_bool;
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
            print_info("operator=()调用拷贝赋值函数！",false);
            var tmp(that);
            std::swap(*this,tmp);
            return *this;
        }


        var& var::operator = (const int& i) {
            print_info("调用operator=(int)函数！",false);
            clear();
            this->m_type = t_int; 
            this->m_number = i;
            return *this;
        }


        var& var::operator = (const bool& b) {
            print_info("调用operator=(bool)函数！",false);
            clear();
            this->m_type = t_bool; 
            this->m_bool = b;
            return *this; 
        }

        var& var::operator = (const std::string& str) {
            print_info("调用operator=(string)函数！",false);
            clear();
            this->m_type = t_str;
            if (m_content) {
                delete m_content; 
                m_content = NULL;
            }

            m_content = new std::string;
            *m_content = str;
            return *this;
        }

        
        var& var::operator = (const varray& arr) {
            if (t_array != m_type && t_unknow != m_type) {
                throw invalid_exception("此对象不是array类型，也不是unknow类型!"); 
            }

            if (isinit && m_array) {
                delete m_array;
                m_array = NULL;
            }

            clear();
            m_array = new varray;
            for (const auto& t : arr) {
                m_array->push_back(t); 
            }
            return *this; 
        }

        var& var::operator = (const vmap& m) {
            if (t_map != m_type && t_unknow != m_type) {
                throw invalid_exception("此对象不是map类型，也不是unknow类型!"); 
            }

            if (isinit && m_map) {
                delete m_map;
                m_map = NULL;
            }

            clear();
            m_map = new vmap;
            for (const auto& t : m) {
                m_map->insert(std::pair<var,var>(t.first,t.second)); 
            }
            return *this;
        }


        bool var::operator != (const var& that) {
            return this != &that;
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
                case t_bool:
                    os << that.m_bool;
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
                case t_bool:
                    m_bool = false;
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
            cout << get_type_str();
        }


        std::string var::get_type_str()const {
            switch (m_type) {
                case t_int:     
                    return "{int}";
                    break;
                case t_str:     
                    return "{string}";
                    break;
                case t_bin:     
                    return "{binary}";
                    break;
                case t_bool:
                    return "{bool}";
                    break;
                case t_array:     
                    return "{array}";
                    break;
                case t_map:     
                    return "{map}";
                    break;
                case t_unknow:     
                default:
                    return "{unknow}";
                    break;
            }

            return "invalid type";
        }

}};
