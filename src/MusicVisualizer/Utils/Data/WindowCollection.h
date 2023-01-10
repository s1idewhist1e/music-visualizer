//
// Created by sekibanki on 12/28/22.
//

#ifndef MUSICVISUALIZER_WINDOWCOLLECTION_H
#define MUSICVISUALIZER_WINDOWCOLLECTION_H


#include <unordered_set>
#include <atomic>
#include <memory>
#include <shared_mutex>
#include "Utils/Rendering/ContextCreation/Context.h"

namespace mvlizer {
    class ContextCollection {
    public:
        void insert(std::atomic<std::shared_ptr<Context>>);
        std::atomic<std::shared_ptr<Context>> erase(std::atomic<std::shared_ptr<Context>>);

        size_t size();

        using iterator = std::unordered_set<std::atomic<std::shared_ptr<Context>>>::iterator;
        using set_citerator = std::unordered_set<std::atomic<std::shared_ptr<Context>>>::const_iterator;
        iterator begin();
        iterator end();
        set_citerator cbegin();
        set_citerator cend();

        std::shared_mutex shared_lock;

    protected:
        std::unordered_set<std::atomic<std::shared_ptr<Context>>> _set;
    };
};

#endif //MUSICVISUALIZER_WINDOWCOLLECTION_H
