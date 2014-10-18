//
//  CSGameKitHelper.m
//  UnexhaustibleMemory
//
//  Created by DonCheung on 4/14/14.
//  Copyright (c) 2014 zero.be. All rights reserved.
//

#import "CSGameKitHelper.h"


static CSGameKitHelper *sharedInstance = nil;

@interface CSGameKitHelper ()
@property (nonatomic,strong)UIViewController *viewController;
@end

@implementation CSGameKitHelper


@synthesize gameCenterAvailable;
// At top of file
@synthesize presentingViewController;
@synthesize match;
//@synthesize delegate;

- (UIViewController *)viewController {
    if (!_viewController) {
        _viewController = [[UIViewController alloc] init];
    }
    return _viewController;
}


+ (CSGameKitHelper *)sharedZBGameKitHelper {
    
    @synchronized (self) {
        
        if (nil == sharedInstance) {
            sharedInstance = [[CSGameKitHelper alloc] init];
            
            // initialize the first view controller
            // and keep it with the singleton
            
        }
    }
    return sharedInstance;
    
    
}

- (id)init {
    if ((self = [super init])) {
        gameCenterAvailable = [self isGameCenterAvailable];
        if (gameCenterAvailable) {
            NSNotificationCenter *nc =
            [NSNotificationCenter defaultCenter];
            [nc addObserver:self
                   selector:@selector(authenticationChanged)
                       name:GKPlayerAuthenticationDidChangeNotificationName
                     object:nil];
            
        }
    }
    return self;
}

- (void)authenticationChanged {
    
    if ([GKLocalPlayer localPlayer].isAuthenticated &&!userAuthenticated) {
//        log(@"Authentication changed: player authenticated.");
        userAuthenticated = TRUE;
        
        
    } else if (![GKLocalPlayer localPlayer].isAuthenticated && userAuthenticated) {
//        CSLog(@"Authentication changed: player not authenticated");
        userAuthenticated = FALSE;
    }
    
}



- (BOOL)isGameCenterAvailable {
    // check for presence of GKLocalPlayer API
    Class gcClass = (NSClassFromString(@"GKLocalPlayer"));
    
    // check if the device is running iOS 4.1 or later
    NSString *reqSysVer =@"4.1";
    NSString *currSysVer = [[UIDevice currentDevice] systemVersion];
    BOOL osVersionSupported = ([currSysVer compare:reqSysVer
                                           options:NSNumericSearch] != NSOrderedAscending);
    
    return (gcClass && osVersionSupported);
}

#pragma mark User functions
- (void)authenticateLocalUser {
    
    if (!gameCenterAvailable) return;
    
//    CSLog(@"Authenticating local user...");
    if ([GKLocalPlayer localPlayer].authenticated == NO) {
        [[GKLocalPlayer localPlayer] authenticateWithCompletionHandler:nil];
    } else {
//        CSLog(@"Already authenticated!");
    }
}


// Add new method, right after authenticateLocalUser
- (void)findMatchWithMinPlayers:(int)minPlayers
                     maxPlayers:(int)maxPlayers
                    playerGroup:(int)playerGroup
                 viewController:(UIViewController *)viewController
                       delegate:(id<CSGameKitHelperDelegate>)theDelegate {
    
    if (!gameCenterAvailable) return;
    
    matchStarted = NO;
    self.match = nil;
    self.presentingViewController = viewController;
//    delegate= theDelegate;
    
    if ([presentingViewController respondsToSelector:@selector(dismissModalViewControllerAnimated:)]) {
        [presentingViewController dismissModalViewControllerAnimated:YES];
    }else
        [presentingViewController dismissViewControllerAnimated:YES completion:nil];
    
    
    GKMatchmakerViewController *mmvc = nil;
    
    {
    
        
        
        
        GKMatchRequest *request = [[GKMatchRequest alloc] init];
        request.minPlayers = minPlayers;
        request.maxPlayers = maxPlayers;
        request.playerGroup = playerGroup;
        
        mmvc = [[GKMatchmakerViewController alloc] initWithMatchRequest:request] ;
        mmvc.matchmakerDelegate = self;
        
        if ([presentingViewController respondsToSelector:@selector(presentModalViewController:animated:)]) {
            
            [presentingViewController presentModalViewController:mmvc animated:YES];
        }else
            [presentingViewController presentViewController:mmvc animated:YES completion:nil];
        
    
    }
    
    
}

#pragma mark GKMatchDelegate

// The match received data sent from the player.
- (void)match:(GKMatch *)theMatch didReceiveData:(NSData *)data fromPlayer:(NSString *)playerID {
    if (match != theMatch) return;
    
    
    
//    CSLog(@"matchDidReceiveData");


}

// The player state changed (eg. connected or disconnected)
- (void)match:(GKMatch *)theMatch player:(NSString *)playerID didChangeState:(GKPlayerConnectionState)state {
    if (match != theMatch) return;
    
    switch (state) {
        case GKPlayerStateConnected:
            // handle a new player connection.
//            CSLog(@"Player connected!");
            
            if (!matchStarted && theMatch.expectedPlayerCount == 0) {
//                CSLog(@"Ready to start match!");
                
            }
            
            break;
        case GKPlayerStateDisconnected:
            // a player just disconnected.
//            CSLog(@"Player disconnected!");
            matchStarted = NO;
            
            [self matchEnded];
            
            break;
    }
}

// The match was unable to connect with the player due to an error.
- (void)match:(GKMatch *)theMatch connectionWithPlayerFailed:(NSString *)playerID withError:(NSError *)error {
    
    if (match != theMatch) return;
    
//    CSLog(@"Failed to connect to player with error: %@", error.localizedDescription);
    matchStarted = NO;
    [self matchEnded];

}

// The match was unable to be established with any players due to an error.
- (void)match:(GKMatch *)theMatch didFailWithError:(NSError *)error {
    
    if (match != theMatch) return;
    
//    CSLog(@"Match failed with error: %@", error.localizedDescription);
    matchStarted = NO;
    [self matchEnded];

}


#pragma mark Property setters

-(void) setLastError:(NSError*)error {
    _lastError = [error copy];
    if (_lastError) {
//        CSLog(@"GameKitHelper ERROR: %@", [[_lastError userInfo]
//                                           description]);
    }
}

-(void) submitScore:(int64_t)score
           category:(NSString*)category {
    //1: Check if Game Center
    //   features are enabled
    if (!userAuthenticated) {
//        CSLog(@"Player not authenticated");
        return;
    }
    
    //2: Create a GKScore object
    GKScore* gkScore =
    [[GKScore alloc]
     initWithCategory:category];
    
    //3: Set the score value
    gkScore.value = score;
    
    //4: Send the score to Game Center
    [gkScore reportScoreWithCompletionHandler:
     ^(NSError* error) {
         
         [self setLastError:error];
         
         BOOL success = (error == nil);
         if (success) {
             NSLog(@"submit success.");
         }else
             NSLog(@"submit error.");
//         if ([delegate respondsToSelector:@selector(onScoresSubmitted:)])
//         {
//             
//             [delegate onScoresSubmitted:success];
//         }
     }];
}


#pragma mark UIViewController stuff

-(UIViewController*) getRootViewController {
    return [UIApplication
            sharedApplication].keyWindow.rootViewController;
}

-(void)presentViewController:(UIViewController*)vc {
    UIViewController* rootVC = [self getRootViewController];
    [rootVC presentViewController:vc animated:YES
                       completion:nil];
}



-(void) findScoresOfPlayerScopeGlobal {
    //1
    GKLeaderboard *leaderboard =
    [[GKLeaderboard alloc] init];
    
    //2
    leaderboard.category =
    CS_HIGHSCORE_LEADERBOARD_CATEGORY;
    
    //3
    leaderboard.playerScope =
    GKLeaderboardPlayerScopeGlobal;
    
    //4
    leaderboard.range = NSMakeRange(1, 100);
    
    //5
    [leaderboard
     loadScoresWithCompletionHandler:
     ^(NSArray *scores, NSError *error) {
         
         [self setLastError:error];
         
         BOOL success = (error == nil);
         
         if (success) {
             if (!_includeLocalPlayerScore) {
                 NSMutableArray *friendsScores =
                 [NSMutableArray array];
                 
                 for (GKScore *score in scores) {
                     if (![score.playerID isEqualToString:[GKLocalPlayer localPlayer].playerID]) {
                         [friendsScores addObject:score];
                     }
                 }
                 scores = friendsScores;
             }
//             if ([delegate respondsToSelector:@selector(onScoresOfPlayerScopeGlobalListReceived:)])
//             {
//             
//                 [self.delegate onScoresOfPlayerScopeGlobalListReceived:scores];
//             }
         }
     }];
}

-(void) getPlayerInfo:(NSArray*)playerList {
    //1
    if (userAuthenticated == NO)
        return;
    
    //2
    if ([playerList count] > 0) {
        [GKPlayer
         loadPlayersForIdentifiers:
         playerList
         withCompletionHandler:
         ^(NSArray* players, NSError* error) {
             
             [self setLastError:error];
             {
                 
//                 if (delegate && [delegate respondsToSelector:@selector(onPlayerInfoReceived:)]) {
//                     [self.delegate onPlayerInfoReceived:players];
//                 }
                 
             }
         }];
    }
}



- (void) showLeaderboard
{
    
    //统计
//    [MobClick event:CS_ANALYTICS_EVENT_TOP_BUTTON label :@"排行榜"];
//    if (!userAuthenticated) {
//        //        CSLog(@"Player not authenticated");
//        return;
//    }
    
    GKLeaderboardViewController *leaderboardController = [[GKLeaderboardViewController alloc] init];
    if (leaderboardController != nil) {
        leaderboardController.leaderboardDelegate = self;
        leaderboardController.category = CS_HIGHSCORE_LEADERBOARD_CATEGORY;
        leaderboardController.timeScope = GKLeaderboardTimeScopeAllTime;
        
        UIWindow *window = [UIApplication sharedApplication].keyWindow;
        [window addSubview:self.viewController.view];
        
        
        if ([self.viewController respondsToSelector:@selector(presentModalViewController:animated:)]) {
            [self.viewController presentModalViewController:leaderboardController animated:YES];
        }else
            [self.viewController presentViewController:leaderboardController animated:YES completion:nil];
    }
}

-(void)leaderboardViewControllerDidFinish:(GKLeaderboardViewController *)viewController
{
    
    if ([self.viewController respondsToSelector:@selector(dismissModalViewControllerAnimated:)]) {
        [self.viewController dismissModalViewControllerAnimated:YES];
    }else
        [self.viewController dismissViewControllerAnimated:YES completion:nil];
    
    [self.viewController.view removeFromSuperview];
}



- (void)matchEnded {

    [self.match disconnect];
    self.match = nil;
    
//    if (delegate && [delegate respondsToSelector:@selector(matchEnded)]) {
//        [delegate matchEnded];
//    }
}



@end
