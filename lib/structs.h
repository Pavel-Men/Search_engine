#ifndef STRUCTS_H
#define STRUCTS_H

#include <cstddef>

struct RelativeIndex{
    size_t doc_id = 0;
    float rank = 0.f;

    bool operator ==(const RelativeIndex& other) const
    {
        return (doc_id == other.doc_id && rank == other.rank);
    }
};

struct Entry {
    size_t docId = 0, count = 0;

    bool operator ==(const Entry& other) const
    {
        return (docId == other.docId && count == other.count);
    }
};

#endif // STRUCTS_H
