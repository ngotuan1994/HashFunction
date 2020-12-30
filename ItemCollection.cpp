#include <string>
#include <iostream>
#include <fstream>
#include <stdexcept>
#include <cmath>
#include <climits>
#include "ItemCollection.hpp"

using std::string;
using std::ifstream;
using std::cout;
using std::endl;

// function to return the hash value based on the first digit
unsigned int hashfct1(unsigned int barcode) {
  // TO BE COMPLETED
    unsigned int d;
    d = barcode / pow(10,6);
    d = d % 10;
    return d;
}

// function to return the hash value based on the second digit
unsigned int hashfct2(unsigned int barcode) {
  // TO BE COMPLETED
    unsigned int d;
    d = barcode / pow(10,5);
    d = d % 10;
    return d;
}

// function to return the hash value based on the third digit
unsigned int hashfct3(unsigned int barcode) {
  // TO BE COMPLETED
    unsigned int d;
    d = barcode / pow(10,4);
    d = d % 10;
    return d;
}

// function to return the hash value based on the fourth digit
unsigned int hashfct4(unsigned int barcode) {
  // TO BE COMPLETED
    unsigned int d;
    d = barcode / pow(10,3);
    d = d % 10;
    return d;
}

// function to return the hash value based on the fifth digit
unsigned int hashfct5(unsigned int barcode) {
    // TO BE COMPLETED
    unsigned int d;
    d = barcode / pow(10,2);
    d = d % 10;
    return d;
}

// function to return the hash value based on the fourth digit
unsigned int hashfct6(unsigned int barcode) {
    // TO BE COMPLETED
    unsigned int d;
    d = barcode / pow(10,1);
    d = d % 10;
    return d;
}

// function to return the hash value based on the fifth digit
unsigned int hashfct7(unsigned int barcode) {
    // TO BE COMPLETED
    unsigned int d;
    d = barcode / pow(10,0);
    d = d % 10;
    return d;
}


// Constructor for struct Item
Item::Item(string itemColor, string itemShape, string itemBrand,
		 unsigned int barcode):itemColor_(itemColor),itemShape_(itemShape), itemBrand_(itemBrand),
				       barcode_(barcode)
{};

// Load information from a text file with the given filename
// THIS FUNCTION IS COMPLETE
void ItemCollection::readTextfile(string filename) {
  ifstream myfile(filename);

  if (myfile.is_open()) {
    cout << "Successfully opened file " << filename << endl;
    string itemColor;
    string itemShape;
    string itemBrand;
    unsigned int barcode;
    while (myfile >> itemColor >> itemShape >> itemBrand >> barcode) {
			if (itemColor.size() > 0)
      	addItem(itemColor, itemShape, itemBrand, barcode);
    }
    myfile.close();
  }
  else
    throw std::invalid_argument("Could not open file " + filename);
}

void ItemCollection::addItem(string itemColor, string itemShape, string itemBrand, unsigned int barcode) {
  // TO BE COMPLETED
  // function that adds the specified pair of glasses to main display (i.e., to all hash tables)
  Item tmp(itemColor,itemShape,itemBrand,barcode);
  hT1[barcode] = tmp;
  hT2[barcode] = tmp;
  hT3[barcode] = tmp;
  hT4[barcode] = tmp;
  hT5[barcode] = tmp;
  hT6[barcode] = tmp;
  hT7[barcode] = tmp;

}

bool ItemCollection::removeItem(unsigned int barcode) {
  // TO BE COMPLETED
  // function that removes the pair of glasses specified by the barcode from the display
  // if pair is found, then it is removed and the function returns true
  // else returns false
  if( hT1.find(barcode) == hT1.end())
  {
    return false;
  }
  else
  {
    hT1.erase(barcode);
  }

  if( hT2.find(barcode) == hT2.end())
  {
    return false;
  }
  else
  {
    hT2.erase(barcode);
  }

  if( hT3.find(barcode) == hT3.end())
  {
    return false;
  }
  else
  {
    hT3.erase(barcode);
  }

  if( hT4.find(barcode) == hT4.end())
  {
    return false;
  }
  else
  {
    hT4.erase(barcode);
  }

  if( hT5.find(barcode) == hT5.end())
  {
    return false;
  }
  else
  {
    hT5.erase(barcode);
  }

  if( hT6.find(barcode) == hT6.end())
  {
    return false;
  }
  else
  {
    hT6.erase(barcode);

  }

  if( hT7.find(barcode) == hT7.end())
  {
    return false;
  }
  else
  {
    hT7.erase(barcode);
  }

    return true;
}

unsigned int ItemCollection::bestHashing() {
  // TO BE COMPLETED
  // function that decides the best has function, i.e. the ones among
  // fct1-fct7 that creates the most balanced hash table for the current
  // ItemCollection data member allItems

	// Hints:
	// Calculate the balance of each hashtable, one by one.
	/*
	 for (unsigned i=0; i<10; ++i) {
    cout << hT1.bucket_size(i); // Call bucket_size() to get the size of each bucket
  }
	*/
	// Then, calculate the lowest balance

    unsigned int balance[7];
    // Create a array contains hT1->hT7
    CustomHashTable tmp[] = {hT1,hT2,hT3,hT4,hT5,hT6,hT7};
    for(unsigned short k = 0 ; k < 7 ; k++)
    {

      unsigned int min_loc = UINT_MAX , max_loc = 0;
      for (unsigned int i = 0 ; i < 10 ; ++i)
      {
        if( min_loc > tmp[k].bucket_size(i))
        {
          min_loc = tmp[k].bucket_size(i);
        }
        if( max_loc < tmp[k].bucket_size(i))
        {
          max_loc = tmp[k].bucket_size(i);
        }
      }
      balance[k] = max_loc - min_loc;
    }
    unsigned int min = UINT_MAX;
    unsigned int result;
    for(unsigned short i = 0 ; i < 7 ; i++)
    {
      if( min > balance[i])
      {
        min = balance[i];
      }
    }
    for (unsigned short i = 0 ; i < 7; i++)
    {
      if (balance[i] == min )
      {
        result = i;
        break;
      }
    }
    // return result must + 1 because of ht1->ht7 not 0->6
    return result + 1;
}

// ALREADY COMPLETED
size_t ItemCollection::size() {
    if ((hT1.size() != hT2.size()) || (hT1.size() != hT3.size()) || (hT1.size() != hT4.size()) || (hT1.size() != hT5.size())|| (hT1.size() != hT6.size()) || (hT1.size() != hT7.size()))
    {
  	   throw std::length_error("Hash table sizes are not the same");
    }

	return hT1.size();
}
