/*
 * atomic.h
 *
 *  Created on: Jul 19, 2019
 *      Author: xuxing
 */

#ifndef BASE_ATOMIC_H_
#define BASE_ATOMIC_H_

#include <stdint.h>
#include "noncopyable.h"

namespace my_muduo {

namespace detail {

template<typename T>
class AtomicIntergetT : noncopyable
{
public:
	AtomicIntergetT() :value_(0)
	{
	}

	// uncomment if you need copying and assignment
	/*
	 AtomicIntegerT(const AtomicIntegerT& that)
	   : value_(that.get())
	 {}

	 AtomicIntegerT& operator=(const AtomicIntegerT& that)
	 {
	   getAndSet(that.get());
	   return *this;
	 }
	*/

	/*
	 * Atomic operation and ACI mechanism
	 * 原子操作与ACI机制
	 */
	T get()
	{
		//gcc >= 4.7 __atomic_load_n(&value_, __ATOMIC_SEQ_CST);
		return __sync_val_compare_and_swap(&value_, 0, 0);
	}

	T getAndAdd(T x)
	{
		// gcc >= 4.7 __automic_fetch_add(&value_, x, __ATOMIC_SEQ_CST);
		return __sync_fetch_and_add(&value_, x);
	}

	T addAndGet(T x)
	{
		return getAndAdd(x) + x;
	}

	T incrementAndGet()
	{
		return addAndGet(1);
	}

	T decrementAndGet()
	{
		return addAndGet(-1);
	}

	void increment()
	{
		incrementAndGet();
	}

	void decrement()
	{
		decrementAndGet();
	}

	T getAndSet(T newValue)
	{
		// gcc >= 4.7 __atomic_exchange_n(&value, newvalue, __ATOMIC_SET_CST);
	}
private:
	volatile T value_;
};

typedef detail::AtomicIntergetT<int32_t> AtomicInt32;
typedef detail::AtomicIntergetT<int64_t> AtomicInt64;

}  // namespace detail


}  // namespace my_muduo

#endif /* BASE_ATOMIC_H_ */
