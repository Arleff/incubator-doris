// Licensed to the Apache Software Foundation (ASF) under one
// or more contributor license agreements.  See the NOTICE file
// distributed with this work for additional information
// regarding copyright ownership.  The ASF licenses this file
// to you under the Apache License, Version 2.0 (the
// "License"); you may not use this file except in compliance
// with the License.  You may obtain a copy of the License at
//
//   http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing,
// software distributed under the License is distributed on an
// "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
// KIND, either express or implied.  See the License for the
// specific language governing permissions and limitations
// under the License.

#ifndef BDG_PALO_BE_SRC_COMMON_COMMON_OBJECT_POOL_H
#define BDG_PALO_BE_SRC_COMMON_COMMON_OBJECT_POOL_H

#include <vector>
#include <boost/thread/mutex.hpp>
#include <boost/thread/locks.hpp>

#include "util/spinlock.h"

namespace palo {

// An ObjectPool maintains a list of C++ objects which are deallocated
// by destroying the pool.
// Thread-safe.
class ObjectPool {
public:
    ObjectPool(): _objects() {}

    ~ObjectPool() {
        clear();
    }

    template <class T>
    T* add(T* t) {
        // Create the object to be pushed to the shared vector outside the critical section.
        // TODO: Consider using a lock-free structure.
        SpecificElement<T>* obj = new SpecificElement<T>(t);
        DCHECK(obj != NULL);
        boost::lock_guard<SpinLock> l(_lock);
        _objects.push_back(obj);
        return t;
    }

    void clear() {
        boost::lock_guard<SpinLock> l(_lock);
        for (auto i = _objects.rbegin(); i != _objects.rend(); ++i) {
            delete *i;
        }
        _objects.clear();
    }

private:
    struct GenericElement {
        virtual ~GenericElement() {}
    };

    template <class T>
    struct SpecificElement : GenericElement {
        SpecificElement(T* t): t(t) {}
        ~SpecificElement() {
            delete t;
        }

        T* t;
    };

    typedef std::vector<GenericElement*> ElementVector;
    ElementVector _objects;
    SpinLock _lock;
};

}

#endif
