//============================================================
//
//      Type:        dynBitset include file
//
//      Author:      Tommaso Bellosta on 11/16/21.
//                   Dipartimento di Scienze e Tecnologie Aerospaziali
//                   Politecnico di Milano
//                   Via La Masa 34, 20156 Milano, ITALY
//                   e-mail: tommaso.bellosta@polimi.it
//
//      Copyright:   2021, above authors and the dynBitset contributors.
//                   This software is distributed under the MIT license, see LICENSE.txt
//
//============================================================

#ifndef DYNBITSET_DYNBITSET_H
#define DYNBITSET_DYNBITSET_H

#include <vector>
#include <cmath>
#include <iostream>
#include <mpi.h>



using namespace std;

class dynBitset {
private:
    vector<char> data;
    unsigned long nBits;

public:
    inline dynBitset(const size_t& size);

    class reference;

    inline dynBitset::reference operator[](size_t pos);
    inline bool operator[](size_t pos) const;
    inline vector<char>& getData() {return data;};

#ifdef HAVE_MPI
    struct request {
        MPI_Request data, nBits;
    };
    request MPIRequest;

    inline void send(int dest, int tag, MPI_Comm comm);
    inline void isend(int dest, int tag, MPI_Comm comm);
    inline void receive(int dest, int tag, MPI_Comm comm);
    inline void ireceive(int dest, int tag, MPI_Comm comm);
    inline void complete();
#endif

};

class dynBitset::reference {
private:
    char* buffer;
    size_t relPos;
    friend class dynBitset;
    inline reference(char* data, const size_t& pos);

public:

    template<class T> inline reference& operator=(const T& rhs);
    inline operator bool() const;

    inline friend ostream& operator<<(ostream& os, const reference& bit);

};


/** helper functions **/

template<class T, class B>
inline void setBit(T& buffer, const size_t& bit, const B& value) {

    unsigned long newbit = !!value;    // Also booleanize to force 0 or 1
    buffer ^= (-newbit ^ buffer) & (1UL << bit);

}

template<class T>
inline constexpr bool getBit(const T& number, const size_t& pos) {

    bool bit = (number >> pos) & 1U;
    return bit;

}




#include "dynBitset.hpp"

#endif //DYNBITSET_DYNBITSET_H
