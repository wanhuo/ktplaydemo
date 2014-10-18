//
//  CSGameKitHelper.h
//  UnexhaustibleMemory
//
//  Created by DonCheung on 4/14/14.
//  Copyright (c) 2014 zero.be. All rights reserved.
//

#import <Foundation/Foundation.h>

#import<GameKit/GameKit.h>

#define CS_HIGHSCORE_LEADERBOARD_CATEGORY @"com.zero.colorjump.HighScores"

// Add to top of file
@protocol CSGameKitHelperDelegate<NSObject>

//- (void)matchStarted;
- (void)matchEnded;
- (void)match:(GKMatch *)match didReceiveData:(NSData *)data
   fromPlayer:(NSString *)playerID;

-(void) onScoresSubmitted:(bool)success;

-(void) onScoresOfPlayerScopeGlobalListReceived:
(NSArray*) scores;
-(void) onPlayerInfoReceived:
(NSArray*)players;



@end

@interface CSGameKitHelper : NSObject<GKMatchmakerViewControllerDelegate, GKMatchDelegate,GKLeaderboardViewControllerDelegate> {
    
    
    
    BOOL userAuthenticated;
    BOOL gameCenterAvailable;    
    // Add inside @interface
    UIViewController *presentingViewController;
    
    GKMatch *match;
    BOOL matchStarted;
    
//    BOOL _gameCenterFeaturesEnabled;

}
@property (strong) NSMutableDictionary *playersDict;

@property (assign, readonly) BOOL gameCenterAvailable;

// Add after @interface
@property (strong) UIViewController *presentingViewController;
@property (strong) GKMatch *match;
//@property (weak) id<CSGameKitHelperDelegate>delegate;
// This property holds the last known error
// that occured while using the Game Center API's
@property (nonatomic, readonly) NSError* lastError;
@property (nonatomic, readwrite)BOOL includeLocalPlayerScore;

+ (CSGameKitHelper *)sharedZBGameKitHelper;
- (void)authenticateLocalUser;

- (void)findMatchWithMinPlayers:(int)minPlayers
                     maxPlayers:(int)maxPlayers
                    playerGroup:(int)playerGroup
                 viewController:(UIViewController *)viewController
                       delegate:(id<CSGameKitHelperDelegate>)theDelegate;
//top Scores
-(void) submitScore:(int64_t)score
           category:(NSString*)category;


-(void) findScoresOfPlayerScopeGlobal;
-(void) getPlayerInfo:(NSArray*)playerList;

- (void) showLeaderboard;

@end
