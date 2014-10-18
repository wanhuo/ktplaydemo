//
//  IOSiAP.h
//  ColorJump
//
//  Created by c++ on 14/8/20.
//
//

#ifndef __ColorJump__IOSiAP__
#define __ColorJump__IOSiAP__

#include <iostream>
#include <vector>

class IOSProduct
{
public:
    std::string productIdentifier;
    std::string localizedTiltle;
    std::string localizedDescription;
    std::string localizedPrice;    ///<  has be localed, just display  it on UI
    bool isValid;
    int index;    ///<  internal use : index of skProducts
};

typedef enum {
    IOSIAP_PAYMENT_PURCHASING,  ///<  just notify, UI do nothing
    IOSIAP_PAYMENT_PURCHAED,    ///< need unlock App Functionality
    IOSIAP_PAYMENT_FAILED,      ///< remove waitting on UI, tall user payment was failed
    IOSIAP_PAYMENT_RESTORED,    ///< need unlock App Functionality, consumble payment No need to care about this
    IOSIAP_PAYMENT_REMOVED,     ///< remove waiting on UI
} IOSiAPPaymentEvent;

class IOSiAPDelegate
{
public:
    virtual ~IOSiAPDelegate(){}
    /// for requestProduct
    virtual void onRequestProductsFinish(void) = 0;
    virtual void onRequestProductsError(int code) = 0;
    /// for payment
    virtual void onPaymentEvent(std::string &identifier, IOSiAPPaymentEvent event, int quantity) = 0;
};

class IOSiAP
{
public:
    IOSiAP();
    ~IOSiAP();
    void requestProducts(std::vector<std::string> &productIdentifiers);
    IOSProduct * iOSProductByIdentitier(std::string &identitier);
    void paymentWithProduct(IOSProduct * iosProduct, int quantity = 1);
    
    IOSiAPDelegate * delegate;
    //      ===     internal use for object-c class        ===
    void * skProducts;              ///<  object-c SKProduct
    void * skTransactionObserver;   ///<  object-c TransactionObserver
    std::vector<IOSProduct *> iOSProducts;
};


class IOSRanking
{
public:
    
    static IOSRanking * getInstance();
    
    void showLeaderboard();
    void submitScore(int score);
    void authenticateLocalUser();
    
    void showAbout();
    
};

#endif /* defined(__ColorJump__IOSiAP__) */
