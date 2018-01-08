//
// Created by goto1134 on 06.01.18.
//

#ifndef GRAPH_SCHEME_CPP_MPI_PROCDURE_H
#define GRAPH_SCHEME_CPP_MPI_PROCDURE_H

#include <Tag.h>
#include <functional>
#include <Module.h>
#include <map>
#include <Data.h>
#include <ResultBuffer.h>

class Procedure {
protected:
    const Tag tag;
    const std::map<int, Data> data;
    ResultBuffer *resultBuffer;
public:
    Procedure(Tag tag, std::map<int, Data> data, ResultBuffer *resultBuffer)
            : tag(tag), data(move(data)), resultBuffer(resultBuffer) {}

    virtual void run() = 0;

    template<typename T>
    static std::function<Procedure *(Tag,
                                     std::map<int, Data>, ResultBuffer *)> constructor() {
        return [](Tag tag, std::map<int, Data> data, ResultBuffer *resultBuffer) {
            return new T(tag, data, resultBuffer);
        };
    }
};

#endif //GRAPH_SCHEME_CPP_MPI_PROCDURE_H
