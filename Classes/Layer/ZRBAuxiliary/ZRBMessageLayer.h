
#ifndef __ZRBMessageLayer_H__
#define __ZRBMessageLayer_H__

#include "Layer/ZRBMenu/ZRBMenuBase.h"

class ZRBMessageLayer : public ZRBMenuBase
{
private:

	CC_SYNTHESIZE_RETAIN( Label * , messageLabel , MessageLabel );
	CC_SYNTHESIZE_RETAIN( Menu * , menu , Menu );
	CC_SYNTHESIZE( float , width , Width );

public:
	virtual bool init( );

	void callback( );

	/**
	*  ������Ϣ
	*
	*  @param mes ��Ϣ����, ��Ϣ����ʱ���ʵ�λ�ò��� '\n'
	*/
	void setMessageLabel( std::string mes );

	void setMessageLabel( std::string mes , std::string item , const std::function<void( )> &func );

	CREATE_FUNC( ZRBMessageLayer );
};


#endif