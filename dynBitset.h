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
#include <bitset>
#include <cmath>


using namespace std;

class dynBitset {
private:
    vector<bitset<8>> data;
    size_t nBits;

public:
    dynBitset(const size_t& size);
    std::bitset<8>::reference operator[](const size_t& pos);

};


#include "dynBitset.hpp"

#endif //DYNBITSET_DYNBITSET_H
