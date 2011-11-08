//
// AbstractStrategy.h
//
// $Id: //poco/1.4/Foundation/include/Poco/AbstractStrategy.h#1 $
//
// Library: Foundation
// Package: Cache
// Module:  AbstractCache
//
// Definition of the AbstractStrategy class.
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


#ifndef Foundation_AbstractStrategy_INCLUDED
#define Foundation_AbstractStrategy_INCLUDED


#include "Poco/KeyValueArgs.h"
#include "Poco/ValidArgs.h"
#include "Poco/EventArgs.h"
#include <set>


namespace Poco {


template <class TKey, class TValue> 
class AbstractStrategy
	/// An AbstractStrategy is the interface for all strategies. 
{
public:
	AbstractStrategy()
	{
	}

	virtual ~AbstractStrategy()
	{
	}

	virtual void onUpdate(const void* pSender, const KeyValueArgs <TKey, TValue>& args)
		/// Updates an existing entry.
	{
		onRemove(pSender,args.key());
		onAdd(pSender, args);
	}
	
	virtual void onAdd(const void* pSender, const KeyValueArgs <TKey, TValue>& key) = 0;
		/// Adds the key to the strategy.
		/// If for the key already an entry exists, an exception will be thrown.

	virtual void onRemove(const void* pSender, const TKey& key) = 0;
		/// Removes an entry from the strategy. If the entry is not found
		/// the remove is ignored.

	virtual void onGet(const void* pSender, const TKey& key) = 0;
		/// Informs the strategy that a read-access happens to an element.

	virtual void onClear(const void* pSender, const EventArgs& args) = 0;
		/// Removes all elements from the cache.

	virtual void onIsValid(const void* pSender, ValidArgs<TKey>& key) = 0;
		/// Used to query if a key is still valid (i.e. cached).

	virtual void onReplace(const void* pSender, std::set<TKey>& elemsToRemove) = 0;
		/// Used by the Strategy to indicate which elements should be removed from
		/// the cache. Note that onReplace does not change the current list of keys.
		/// The cache object is reponsible to remove the elements.
};


} // namespace Poco


#endif // Foundation_AbstractStrategy_INCLUDED
