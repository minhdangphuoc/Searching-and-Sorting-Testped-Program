#ifndef _KEY_H_
#define _KEY_H_

#include <iostream>
using namespace std;
class Key {
   int key;
public:
   static int comparisons;
   static int assignments;
   Key (int x = 0);
   int the_key() const;

   Key& operator = (const Key &original);

};

Key::Key (int x) 
{
    this -> key = x;
}

int Key::comparisons = 0;

int Key::the_key() const
{
    return key;
}

Key& Key::operator = (const Key &original){
   this -> key = original.key;
   return *this;
}

bool operator ==(const Key &x,const Key &y){
   Key::comparisons++; // Increase compare value
   return x.the_key() == y.the_key();
}

bool operator >(const Key &x,const Key &y){
    Key::comparisons++; // Increase compare value
   return x.the_key() > y.the_key();
}
bool operator <(const Key &x,const Key &y){
   Key::comparisons++; // Increase compare value
   return x.the_key() < y.the_key();
}
bool operator >=(const Key &x,const Key &y){
   Key::comparisons++; // Increase compare value
   return x.the_key() >= y.the_key();
}
bool operator <=(const Key &x,const Key &y){
   Key::comparisons++; // Increase compare value
   return x.the_key() <= y.the_key();
}
bool operator !=(const Key &x,const Key &y);
ostream& operator << (ostream& os, const Key& k);

#endif // !1