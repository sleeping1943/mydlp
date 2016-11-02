/************************************
*
*此头文件...
*filename : var.h
*author   : sleeping
*email    : csleeping@163.com
*date     : 2016年11月01日 星期二 10时50分39秒
*
************************************/
#ifndef _SLP_VAR_H
#define _SLP_VAR_H
#include <string>
#include <vector>
#include <map>
#include <exception>

#include "allocator.h"

namespace slp{namespace script{
    typedef enum {
        t_int,
        t_str,
        t_bin,
        t_array,
        t_map,
        t_unknow
    }LUA_TYPE;

    class var;
    /*
     *typedef std::vector<var,slp::allocator<var> > varray;
     *typedef std::map<var,var,slp::allocator<var> > vmap;
     */
    typedef std::vector<var> varray;
    typedef std::map<var,var> vmap;

    class var {
        public: 
            var();
            var(int i);
            var(const char* pstr);
            var(const std::string& str);
            var(const varray& arr);
            var(const vmap& m);

            ~var();
            var(const var& that);
            var& operator = (const var& that);
            bool operator < (const var& that) const;
            var& operator = (const int& i);
            var& operator = (const std::string& str);
            var& operator = (const varray& arr);
            var& operator = (const vmap& m);
            friend std::ostream& operator << (std::ostream& os, const var& that);

            inline LUA_TYPE type()const { return m_type; };
            void print_type() const;

            inline void init () {
                isinit = true;
                m_number = 0;
                m_content = NULL;
                m_array = NULL;
                m_map = NULL;
                m_type = t_unknow;
            }

            void clear();
            int get_number()const { return m_number; };
            std::string get_bin()const { return *m_content; };
            std::string get_str()const { return *m_content; };
            std::vector<var>& get_array() const { return *m_array; };
            std::map<var,var>& get_map() const { return *m_map; };

            /*
             *void push_back(const var& v);
             */
        private:
            bool isinit;
            int m_number;
            std::string *m_content;
            std::vector<var> *m_array;
            std::map<var,var> *m_map;
            LUA_TYPE m_type;
    };

    class invalid_exception:public std::exception {
        public: 
            invalid_exception() {};
            invalid_exception(std::string info):m_info(info) {};
            virtual const char* what()const throw() {
                std::string errinfo = m_info;
                errinfo += ":";
                errinfo += "invalid type[无效的类型，无法转换]"; 
                return errinfo.data();
            };  
        private:
            std::string m_info;
    };
}};
#endif /*_SLP_VAR_H*/
