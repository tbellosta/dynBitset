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
#ifndef DYNBITSET_DYNBITSET_HPP
#define DYNBITSET_DYNBITSET_HPP

#include "dynBitset.h"
#include <climits>

dynBitset::dynBitset(const size_t &size) {

    /** compute number of chars needed to fit the data **/
    size_t nChars = size / CHAR_BIT;
    if (size % CHAR_BIT) nChars++;

    /** allocate char array **/
    data = vector<char>(nChars,0);

}

dynBitset::reference dynBitset::operator[](size_t pos) {

    /** find bitset containing the pos **/
    size_t iChar = pos / 8;

    /** find position in bitset iChar **/
    size_t relPos = pos % 8;

    return {&data[iChar], relPos};

}

bool dynBitset::operator[](size_t pos) const {

    /** find bitset containing the pos **/
    size_t iChar = pos / 8;

    /** find position in bitset iChar **/
    size_t relPos = pos % 8;

    return getBit(data[iChar], relPos);
}


dynBitset::reference::reference(char* data, const size_t& pos) : buffer(data), relPos(pos) {}

template<class T>
dynBitset::reference &dynBitset::reference::operator=(const T &rhs) {
    setBit(*buffer, relPos, rhs);
    return *this;
}

/** helper functions **/

ostream &operator<<(ostream &os, const dynBitset::reference &bit) {
    os << getBit(*bit.buffer,bit.relPos);
    return os;
}

dynBitset::reference::operator bool() const {
    return getBit(*buffer,relPos);
}

#ifdef HAVE_MPI

void dynBitset::send(int dest, int tag, MPI_Comm comm) {

    /** send data **/
    MPI_Isend(data.data(), data.size(), MPI_CHAR, dest, tag, comm, &MPIRequest.data);

    /** send # of bits **/
    MPI_Isend(&nBits, 1, MPI_UNSIGNED_LONG, dest, tag, comm, &MPIRequest.nBits);

}

void dynBitset::receive(int dest, int tag, MPI_Comm comm) {

    /** send data **/
    MPI_Irecv(data.data(), data.size(), MPI_CHAR, dest, tag, comm, &MPIRequest.data);

    /** send # of bits **/
    MPI_Isend(&nBits, 1, MPI_UNSIGNED_LONG, dest, tag, comm, &MPIRequest.nBits);

}

void dynBitset::complete() {

    /** wait for data **/
    MPI_Wait(&MPIRequest.data, NULL);

    /** wait for # of bits **/
    MPI_Wait(&MPIRequest.nBits, NULL);

}

#endif //HAVE_MPI

#endif //DYNBITSET_DYNBITSET_HPP
