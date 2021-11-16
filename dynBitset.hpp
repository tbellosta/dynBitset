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

#endif //DYNBITSET_DYNBITSET_HPP
