//
// base.cpp
//

/*
Babbler 0.1
Copyright (C) 2003 Nicolas Dufour

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
*/

#include <iostream>
#include "base.h"

Base::Base() : _total(0) {

}

void Base::addDict(int proportion, DictReader dict) {
  string name = dict.getName();
  _dicts.push_back(dict);
  _proportions.push_back(proportion);

  computeRanges();
}

vector<string> Base::getRandomTermList() {
  int dictChoice = random() % _total;
  int indexDict = -1;

  for(int index = 0; index < _dicts.size(); index++) {
    int lowerRange = _ranges[index];
    int upperRange = _total;
    if(index != _dicts.size()-1) {
      upperRange = _ranges[index+1];
    }
    if(dictChoice >= lowerRange && dictChoice < upperRange) {
      indexDict = index;
      break;
    }
  }

  if(indexDict == -1) {
    cout << "euh .... indexDict = " << indexDict << endl;
    exit(1);
  }

  return _dicts[indexDict].getTerms();
}

void Base::computeRanges() {
  _ranges.clear();
  int currentRange = 0;
  for(int index = 0; index < _proportions.size(); index++) {
    int currentProportion = _proportions[index];
    _ranges.push_back(currentRange);
    currentRange += currentProportion;
  }

  _total = currentRange;
}

