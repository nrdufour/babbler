//
// babbler.cpp
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

#include "babbler.h"
#include "dictreader.h"
#include <iostream>

void Babbler::addFile(int proportion, string filename) {
  //cout << "add theme " << filename << " with weight " << proportion << endl;
  _base.addDict(proportion, DictReader(filename));
}

string Babbler::babble() {
  string result      = "";
  int    nbDict      = _base.getNbDict();

  if(nbDict == 0) {
    cout << "Empty base ! I stop now" << endl;
    exit(1);
  }

  //long   choice      = random() % nbTerm;
  string word        = nextTerm();
  int    position    = 0;
  char   currentChar = word[position];

  //cout << "next : '" << currentChar << "'" << endl;

  result += currentChar;

  for(;;) {
    position++;
    char nextChar = nextCharAt(currentChar,position);

    if(nextChar == '@') break;

    //cout << "next : '" << nextChar << "'" << endl;

    result += nextChar;
    currentChar = nextChar;
  }

  return result;
}

char Babbler::nextCharAt(char c, int pos) {
  vector<string> termList = _base.getRandomTermList();
  vector<string> choices;

  for(int index = 0; index < termList.size(); index++) {
    string word = termList[index];
    if(pos >= word.length()) continue;
    if(word[pos-1] == c) {
      choices.push_back(word);
    }
  }

  if(choices.size() == 0) return '@';

  int finalChoice = random()%choices.size();
  string last = choices[finalChoice];
  return last[pos];
}

string Babbler::nextTerm() {
  vector<string> choices = _base.getRandomTermList();
  //cout << "plopp = " << choices.size() << endl;
  int finalChoice = random() % choices.size();
  return choices[finalChoice];
}
