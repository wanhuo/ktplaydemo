//
//  IOSiAP_Bridge.h
//  ColorJump
//
//  Created by c++ on 14/8/21.
//
//
//
#ifndef __ColorJump__IOSiAP_Bridge__
#define __ColorJump__IOSiAP_Bridge__

#include "IOSiAP.h"
#include "ZRBMarketGold.h"


class IOSiAP_Bridge : public IOSiAPDelegate
{
public:
    IOSiAP_Bridge();
    ~IOSiAP_Bridge();
    
    IOSiAP * iap;
    BuyDelegate * delegate;
    
    std::vector<std::string> _identifiers;
    void setIdentifiers(std::string &identifiers);
    void setIdentifiers(std::vector<std::string> &identifiers);
    
    void requestProducts();
    void requestProducts(std::string &identifiers);
    void requestProducts(std::vector<std::string> &identifiers);
    
    virtual void onRequestProductsFinish(void);
    virtual void onRequestProductsError(int code);
    virtual void onPaymentEvent(std::string &identifier, IOSiAPPaymentEvent event, int quantity);
};

#endif /* defined(__ColorJump__IOSiAP_Bridge__) */
