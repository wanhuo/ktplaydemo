//
//  IOSiAP.mm
//  ColorJump
//
//  Created by c++ on 14/8/20.
//
//

//#import <Foundation/Foundation.h>
#import <StoreKit/StoreKit.h>

#import "IOSiAP.h"

#import "CSGameKitHelper.h"


// 关于


@interface TratingReview : NSObject
+ (TratingReview *) getInstance;
- (void) reviewFor : (int)appleID;
@end

static TratingReview * _tratingReview = nil;


@implementation TratingReview

+ (TratingReview *)getInstance {
    
    @synchronized ([TratingReview class])
    {
        if (! _tratingReview) {
            _tratingReview = [[TratingReview alloc] init];
            return _tratingReview;
        }
    }
    return _tratingReview;
}

- (void)reviewFor:(int)appleID
{
    NSString * str = [NSString stringWithFormat:
                      @"itms-apps://ax.itunes.apple.com/WebObjects/MZStore.woa/wa/viewContentsUserReviews?type=Purple+Software&id=%d",
                      appleID];
    
    NSURL * url = [NSURL URLWithString:str];
    if ([[UIApplication sharedApplication] canOpenURL:url]) {
        [[UIApplication sharedApplication] openURL:url];
    }
}

@end


// 游戏内购买
static IOSRanking * iosranking;

@interface iAPProductsRequestDeleget : NSObject<SKProductsRequestDelegate>
@property (nonatomic, assign) IOSiAP * iosiap;
@end


@implementation iAPProductsRequestDeleget

- (void) productsRequest:(SKProductsRequest *)request
      didReceiveResponse:(SKProductsResponse *)response
{
    ///     release old
    if (_iosiap->skProducts) {
        [(NSArray *)(_iosiap->skProducts) release];
    }
    ///     record new product
    _iosiap->skProducts = [response.products retain];
    
    for (int index = 0; index < [response.products count]; index++) {
        SKProduct * skProduct = [response.products objectAtIndex:index];
        
        ///     check is valid
        bool isValid = true;
        for (NSString * invalidIdentifier in response.invalidProductIdentifiers) {
            if ([skProduct.productIdentifier isEqualToString:invalidIdentifier]) {
                isValid = false;
                break;
            }
        }

        IOSProduct * iosProduct = new IOSProduct;
        iosProduct->productIdentifier = std::string([skProduct.productIdentifier UTF8String]);
        iosProduct->localizedTiltle = std::string([skProduct.localizedTitle UTF8String]);
        iosProduct->localizedDescription = std::string([skProduct.localizedDescription UTF8String]);
        
        /// locale price to string
        NSNumberFormatter * formatter = [[NSNumberFormatter alloc] init];
        [formatter setFormatterBehavior:NSNumberFormatterBehavior10_4];
        [formatter setNumberStyle:NSNumberFormatterCurrencyStyle];
        [formatter setLocale:skProduct.priceLocale];
        NSString * priceStr = [formatter stringFromNumber:skProduct.price];
        [formatter release];
        iosProduct->localizedPrice = std::string([priceStr UTF8String]);
        
        iosProduct->index = index;
        iosProduct->isValid = isValid;
        _iosiap->iOSProducts.push_back(iosProduct);
    }
}

- (void)requestDidFinish:(SKRequest *)request
{
    _iosiap->delegate->onRequestProductsFinish();
    [request.delegate release];
    [request release];
}

- (void)request:(SKRequest *)request didFailWithError:(NSError *)error
{
    UIAlertView * alerView = [[UIAlertView alloc] initWithTitle:NSLocalizedString(@"Error", nil)
                                                        message:[error localizedDescription]
                                                       delegate:nil
                                              cancelButtonTitle:NSLocalizedString(@"close", nil)
                                              otherButtonTitles:nil];
    [alerView show];
    [alerView release];
    
    _iosiap->delegate->onRequestProductsError([error code]);
}

@end

@interface iAPTransactionObserver : NSObject<SKPaymentTransactionObserver>
@property (nonatomic, assign) IOSiAP * iosiap;
@end

@implementation iAPTransactionObserver

- (void)paymentQueue:(SKPaymentQueue *)queue updatedTransactions:(NSArray *)transactions
{
    for (SKPaymentTransaction * transaction in transactions) {
        std::string identifier([transaction.payment.productIdentifier UTF8String]);
        IOSiAPPaymentEvent event;
        
        switch (transaction.transactionState) {
            case SKPaymentTransactionStatePurchased:
                event = IOSIAP_PAYMENT_PURCHAED;
                break;
                
            case SKPaymentTransactionStatePurchasing:
                event = IOSIAP_PAYMENT_PURCHASING;
                break;
                
            case SKPaymentTransactionStateFailed:
                event = IOSIAP_PAYMENT_FAILED;
                break;
                
            case SKPaymentTransactionStateRestored:
                // NOTE :  consumble payment is NOT restorable
                event = IOSIAP_PAYMENT_RESTORED;
                break;
                
            default:
                break;
        }
        
        _iosiap->delegate->onPaymentEvent(identifier, event, transaction.payment.quantity);
        if (event != IOSIAP_PAYMENT_PURCHASING) {
            [[SKPaymentQueue defaultQueue] finishTransaction:transaction];
        }
    }
}

- (void)paymentQueue:(SKPaymentQueue *)queue removedTransactions:(NSArray *)transactions
{
    for (SKPaymentTransaction * transaction in transactions) {
        std::string identifier([transaction.payment.productIdentifier UTF8String]);
        _iosiap->delegate->onPaymentEvent(identifier, IOSIAP_PAYMENT_REMOVED, transaction.payment.quantity);
    }
}

@end

IOSiAP::IOSiAP() : skProducts(nullptr), delegate(nullptr)
{
    skTransactionObserver = [[iAPTransactionObserver alloc] init];
    ((iAPTransactionObserver *)skTransactionObserver).iosiap = this;
    [[SKPaymentQueue defaultQueue] addTransactionObserver:(iAPTransactionObserver *)skTransactionObserver];
}

IOSiAP::~IOSiAP()
{
    if (skProducts) {
        [(NSArray *)(skProducts) release];
    }
    
    std::vector<IOSProduct *>::iterator iterator;
    for (iterator = iOSProducts.begin(); iterator != iOSProducts.end(); iterator++) {
        IOSProduct * iosProduct = *iterator;
        delete iosProduct;
    }
    
    [[SKPaymentQueue defaultQueue] removeTransactionObserver:(iAPTransactionObserver *)skTransactionObserver];
    [(iAPTransactionObserver *)skTransactionObserver release];
}

IOSProduct * IOSiAP::iOSProductByIdentitier(std::string &identitier)
{
    std::vector<IOSProduct *>::iterator iterator;
    for (iterator = iOSProducts.begin(); iterator != iOSProducts.end(); iterator++) {
        IOSProduct * iosProduct = *iterator;
        if (iosProduct->productIdentifier == identitier) {
            return iosProduct;
        }
    }
    
    return nullptr;
}

void IOSiAP::requestProducts(std::vector<std::string> &productIdentifiers)
{
    if (![SKPaymentQueue canMakePayments]) {
        UIAlertView * alerView = [[UIAlertView alloc] initWithTitle:@"Alert"
                                                           message:@"You can't purchase app store"
                                                          delegate:nil
                                                 cancelButtonTitle:NSLocalizedString(@"close", nil)
                                                 otherButtonTitles:nil];
        [alerView show];
        [alerView release];
        return;
    }

    
    NSMutableSet * set = [NSMutableSet setWithCapacity:productIdentifiers.size()];
    std::vector<std::string>::iterator iterator;
    for (iterator = productIdentifiers.begin(); iterator != productIdentifiers.end(); iterator++) {
        [set addObject:[NSString stringWithUTF8String:(*iterator).c_str()]];
    }
    
    SKProductsRequest * productsRequest = [[SKProductsRequest alloc] initWithProductIdentifiers:set];
    iAPProductsRequestDeleget * delegate = [[iAPProductsRequestDeleget alloc] init];
    delegate.iosiap = this;
    productsRequest.delegate = delegate;
    [productsRequest start];
}

void IOSiAP::paymentWithProduct(IOSProduct *iosProduct, int quantity)
{
    if (iosProduct == nullptr)
    {
        UIAlertView * alerView = [[UIAlertView alloc] initWithTitle:@"Alert"
                                                            message:@"iosProduct is nullptr"
                                                           delegate:nil
                                                  cancelButtonTitle:NSLocalizedString(@"Close", nil)
                                                  otherButtonTitles:nil];
        [alerView show];
        [alerView release];
        return;
    }
    SKProduct *skProduct = [(NSArray *)(skProducts) objectAtIndex:iosProduct->index];
    SKMutablePayment * payment = [SKMutablePayment paymentWithProduct:skProduct];
    payment.quantity = quantity;
    
    [[SKPaymentQueue defaultQueue] addPayment:payment];
}

IOSRanking * IOSRanking::getInstance()
{
    if (iosranking == nullptr)
    {
        iosranking = new IOSRanking();
    }
    
    return  iosranking;
}

void IOSRanking::showLeaderboard()
{
    [[CSGameKitHelper sharedZBGameKitHelper] showLeaderboard];
}


void IOSRanking::submitScore(int score)
{
    [[CSGameKitHelper sharedZBGameKitHelper] submitScore:score category:CS_HIGHSCORE_LEADERBOARD_CATEGORY];
}

void IOSRanking::authenticateLocalUser() {
    [[CSGameKitHelper sharedZBGameKitHelper] authenticateLocalUser];
}

void IOSRanking::showAbout()
{
    [[TratingReview getInstance] reviewFor:917503239];
}