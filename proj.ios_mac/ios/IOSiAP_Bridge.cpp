//
//  IOSiAP_Bridge.cpp
//  ColorJump
//
//  Created by c++ on 14/8/21.
//
//

#include "IOSiAP_Bridge.h"

IOSiAP_Bridge::IOSiAP_Bridge() :delegate(nullptr)
{
    iap = new IOSiAP();
    iap->delegate = this;
    
}

IOSiAP_Bridge::~IOSiAP_Bridge()
{
    delete  iap;
}

void IOSiAP_Bridge::setIdentifiers(std::vector<std::string> &identifiers)
{
    if (identifiers.size() == 0)
    {
        delegate->buyFild( );
        return;
    }
    _identifiers.clear();
    _identifiers = identifiers;
}

void IOSiAP_Bridge::setIdentifiers(std::string &identifiers)
{
    if (identifiers.size() == 0)
    {
        delegate->buyFild( );
        return;
    }
    _identifiers.clear();
    _identifiers.push_back(identifiers);
}

void IOSiAP_Bridge::requestProducts(std::string &identifiers)
{
    setIdentifiers(identifiers);
    requestProducts();
}

void IOSiAP_Bridge::requestProducts(std::vector<std::string> &identifiers)
{
    setIdentifiers(identifiers);
    requestProducts();
}

void IOSiAP_Bridge::requestProducts()
{
    if (_identifiers.empty()) {
        return;
    }
    iap->requestProducts(_identifiers);
}

void IOSiAP_Bridge::onRequestProductsFinish(void)
{
    //必须在onRequestProductsFinish后才能去请求iAP产品数据。
    IOSProduct *product = iap->iOSProductByIdentitier(_identifiers.at(0));
    // 然后可以发起付款请求。
    iap->paymentWithProduct(product);
}

void IOSiAP_Bridge::onRequestProductsError(int code)
{
    //这里requestProducts出错了，不能进行后面的所有操作。
    printf("---IOSiAP_Bridge--Reauest---Error : %d", code);
    delegate->buyFild( );
}

void IOSiAP_Bridge::onPaymentEvent(std::string &identifier, IOSiAPPaymentEvent event, int quantity)
{
    switch (event)
    {
        case IOSIAP_PAYMENT_FAILED:
            delegate->buyFild( );
            break;
            
        case IOSIAP_PAYMENT_PURCHASING:
            break;
            
        case IOSIAP_PAYMENT_PURCHAED:
            delegate->buyFinish();
            break;
        
        case IOSIAP_PAYMENT_RESTORED:
            break;
            
        case IOSIAP_PAYMENT_REMOVED:
            delegate->changeLoad(false);
            break;
            
        default:
            break;
    }
}