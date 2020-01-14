/*
 * noncopyable.h
 *
 *  Created on: Jul 19, 2019
 *      Author: xuxing
 */

#ifndef BASE_NONCOPYABLE_H_
#define BASE_NONCOPYABLE_H_


namespace my_muduo {

class noncopyable {

public:
	noncopyable(const noncopyable&) = delete;
	void operator=(const noncopyable&) = delete;

protected:
	noncopyable() = default;
	~noncopyable() = default;
};

}  // namespace my_muduo


#endif /* BASE_NONCOPYABLE_H_ */
