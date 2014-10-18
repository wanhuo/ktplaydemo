/*
 * ZRBThreadLoading.h
 *
 *  Created on: 2014年9月19日
 *      Author: 帅锋
 */

#ifndef ZRBTHREADLOADING_H_
#define ZRBTHREADLOADING_H_

#include <thread>

#include "cocos2d.h"

USING_NS_CC;

class ZRBThreadLoading: public Layer
{
public:
	ZRBThreadLoading();
	virtual ~ZRBThreadLoading();

	bool init( );

	static Scene * createScene();

	CREATE_FUNC(ZRBThreadLoading);

public:

	void update( float );
	void thread1( );

private:

	std::vector<Image *> image;

	std::vector<std::string> name;

private:

	bool isLoad;
	std::mutex _mutex;
};

#endif /* ZRBTHREADLOADING_H_ */
