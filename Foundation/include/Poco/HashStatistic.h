//
// HashStatistic.h
//
// $Id: //poco/1.4/Foundation/include/Poco/HashStatistic.h#1 $
//
// Library: Foundation
// Package: Hashing
// Module:  HashStatistic
//
// Definition of the HashStatistic class.
//
// Copyright (c) 2006, Applied Informatics Software Engineering GmbH.
// and Contributors.
//
// Permission is hereby granted, free of charge, to any person or organization
// obtaining a copy of the software and accompanying documentation covered by
// this license (the "Software") to use, reproduce, display, distribute,
// execute, and transmit the Software, and to prepare derivative works of the
// Software, and to permit third-parties to whom the Software is furnished to
// do so, all subject to the following:
// 
// The copyright notices in the Software and this entire statement, including
// the above license grant, this restriction and the following disclaimer,
// must be included in all copies of the Software, in whole or in part, and
// all derivative works of the Software, unless such copies or derivative
// works are solely in the form of machine-executable object code generated by
// a source language processor.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT
// SHALL THE COPYRIGHT HOLDERS OR ANYONE DISTRIBUTING THE SOFTWARE BE LIABLE
// FOR ANY DAMAGES OR OTHER LIABILITY, WHETHER IN CONTRACT, TORT OR OTHERWISE,
// ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
// DEALINGS IN THE SOFTWARE.
//


#ifndef Foundation_HashStatistic_INCLUDED
#define Foundation_HashStatistic_INCLUDED


#include "Poco/Foundation.h"
#include <vector>


namespace Poco {


//@ deprecated
class Foundation_API HashStatistic
	/// HashStatistic class bundles statistical information on the current state of a HashTable
{
public:
	HashStatistic(
		UInt32 tableSize, 
		UInt32 numEntries, 
		UInt32 numZeroEntries, 
		UInt32 maxEntry, 
		std::vector<UInt32> details = std::vector<UInt32>());
		/// Creates the HashStatistic.

	virtual ~HashStatistic();
		/// Destroys the HashStatistic.

	UInt32 maxPositionsOfTable() const;
		/// Returns the maximum number of different hash values possible for the table

	UInt32 numberOfEntries() const;
		/// Returns the total number of entries currently stored in the HashTable

	UInt32 numberOfZeroPositions() const;
		/// Returns the number of hash positions that contain no entry.

	double avgEntriesPerHash() const;
		/// Returns the average number of entries per position in the Hashtable, the higher this value the less efficient
		/// performs hashing. If a large value is returned and getNumberOfZeroPositions also returns a large value, this
		/// indicates an inefficient hashing function. If the number of zero entries is low, resizing the HashTable, should
		/// be enough to improve performance

	double avgEntriesPerHashExclZeroEntries() const;
		/// Same as getAvgEntriesPerHash but hash values that contain no entry are ignored,
		/// getAvgEntriesPerHashExclZeroEntries >= getAvgEntriesPerHash will always be true.

	UInt32 maxEntriesPerHash() const;
		/// Returns the maximum number of entries per hash value found in the current table.

	const std::vector<UInt32> detailedEntriesPerHash() const;
		/// Will either be an empty vector or will contain for each possible hash value, the number of entries currently stored

	std::string toString() const;
		/// Converts the whole data structure into a string.

private:
	UInt32 _sizeOfTable;
	UInt32 _numberOfEntries;
	UInt32 _numZeroEntries;
	UInt32 _maxEntriesPerHash;
	std::vector<UInt32> _detailedEntriesPerHash;
};


inline UInt32 HashStatistic::maxPositionsOfTable() const
{
	return _sizeOfTable;
}


inline UInt32 HashStatistic::numberOfEntries() const
{
	return _numberOfEntries;
}


inline UInt32 HashStatistic::numberOfZeroPositions() const
{
	return _numZeroEntries;
}


inline double HashStatistic::avgEntriesPerHash() const
{
	return ((double) numberOfEntries()) / maxPositionsOfTable();
}


inline double HashStatistic::avgEntriesPerHashExclZeroEntries() const
{
	return ((double) numberOfEntries()) / (maxPositionsOfTable() - numberOfZeroPositions());
}


inline UInt32 HashStatistic::maxEntriesPerHash() const
{
	return _maxEntriesPerHash;
}


inline const std::vector<UInt32> HashStatistic::detailedEntriesPerHash() const
{
	return _detailedEntriesPerHash;
}


} // namespace Poco


#endif // Foundation_HashStatistic_INCLUDED
