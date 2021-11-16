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

#include "dynBitset.h"

dynBitset::dynBitset(const size_t &size) {

    /** compute number of chars needed to fit the data **/
    size_t nChars = size / 8;
    if (size % 8) nChars++;

    /** allocate char array **/
    data = vector<bitset<8>>(nChars);

}

std::bitset<8>::reference dynBitset::operator[](const size_t &pos) {

    /** find bitset containing the pos **/
    size_t iChar = pos / 8;

    /** find position in bitset iChar **/
    size_t relPos = pos % 8;

    return data[iChar][relPos];

}