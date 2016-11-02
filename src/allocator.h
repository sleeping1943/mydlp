/************************************
*
*此头文件定义空间分配器
*filename : src/allocator.h
*author   : sleeping
*email    : csleeping@163.com
*date     : 2016年11月01日 星期二 18时22分30秒
*
************************************/
#ifndef _SLP_SRC_ALLOCATOR_H
#define _SLP_SRC_ALLOCATOR_H
#include <new>
#include <stddef.h>
#include <stdlib.h>
#include <limits.h>
#include <iostream>

namespace slp{

    using std::cout;
    using std::cerr;
    using std::endl;


    template <class T>
    inline T* _allocate (ptrdiff_t size,T*) {
        std::set_new_handler(0); 
        T* tmp = (T*)(::operator new ((size_t)(size*sizeof(T))));
        if (0 == tmp) {
            cerr << "out of memory" << endl;
            exit(1);
        }
        return tmp;
    }


    template <class T>
    inline void _deallocate(T* buffer) {
        ::operator delete(buffer); 
    }

    template <class T1,class T2>
    inline void _construct (T1* p,const T2& value) {
        new (p) T1(value); 
    }

    template <class T>
    inline void _destory (T* ptr) {
        ptr->~T(); 
    }

    template <class T>
    class allocator {
    public:
        typedef T   value_type;
        typedef T*  pointer;
        typedef T&  reference;
        typedef size_t  size_type;
        typedef const T&    const_reference;
        typedef const T*    const_pointer;
        typedef ptrdiff_t   difference_type;

        template <class U>
        struct rebind {
            typedef allocator<U> other;
        };

        pointer allocate (size_type n,const void* hint = 0) {
            return _allocate((difference_type)n,(pointer)0);
        }

        void deallocate (pointer p,size_type n) {
            _deallocate(p); 
        }

        void construct (pointer p,const T& value) {
            _construct(p,value); 
        }

        void destroy (pointer p) {
            _destory(p); 
        }
        
        pointer address(reference x) {
            return (pointer)&x; 
        }

        const_pointer const_address (const_reference x) {
            return (const_reference)&x; 
        }

        size_type max_size () const {
            return size_type(UINT_MAX/sizeof(T)); 
        }
    };

};
#endif /*_SLP_SRC_ALLOCATOR_H*/
