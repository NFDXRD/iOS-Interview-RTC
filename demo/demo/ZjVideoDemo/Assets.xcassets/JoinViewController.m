//
//  JoinViewController.m
//  ZjVideoDemo
//
//  Created by 李志朋 on 2018/1/30.
//  Copyright © 2018年 李志朋. All rights reserved.
//

#import "JoinViewController.h"
#import "ZjRCTManager.h"
#import "VideoViewController.h"


@interface JoinViewController ()<ZJVideoManagerDelegate>{
    VideoViewController *videoVC;
}
@property (weak, nonatomic) IBOutlet UITextField *sipkeyTf;
@property (weak, nonatomic) IBOutlet UITextField *passwordTf;
@property (weak, nonatomic) IBOutlet UITextField *apiServerTf;
@property (weak, nonatomic) IBOutlet UITextField *displayNameTf;
@property (weak, nonatomic) IBOutlet UITextField *inBandTf;
@property (weak, nonatomic) IBOutlet UITextField *outBandtf;
@property (weak, nonatomic) IBOutlet UITextField *minWidth;
@property (weak, nonatomic) IBOutlet UITextField *minHeightTf;
@property (weak, nonatomic) IBOutlet UITextField *expectedWidth;
@property (weak, nonatomic) IBOutlet UITextField *expectedHeight;
@property (nonatomic, strong) ZjRCTManager *manager;

@end

@implementation JoinViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    self.manager = [ZjRCTManager sharedManager];
    self.manager.delegate = self;
    [self.manager setApiServer:self.apiServerTf.text];
}

- (IBAction)clickJoinCostum:(id)sender {
    
    NSMutableDictionary *conferenceModel = [NSMutableDictionary dictionary];
    [conferenceModel ZJSDKVideoInterview:self.sipkeyTf.text
                             displayName:self.displayNameTf.text];
    NSLog(@"入会参数： -- %@",conferenceModel);

    [self.manager selectReceiveVideoModel:ReceiveVideoModelSimulcast];
    
    [self.manager connectWithModel:conferenceModel andCapacity:ConncetCapacityModelHost];
    
    videoVC = [[VideoViewController alloc]init];
    self.manager.conferenceView.frame = CGRectMake(0, 0, [UIScreen mainScreen].bounds.size.width, [UIScreen mainScreen].bounds.size.width);
    [videoVC.view addSubview:self.manager.conferenceView];
    
    [self presentViewController:videoVC animated:NO completion:nil];
}

- (void)click{
    
}

-(void)zjOutofConference{
    
}

-(void)zjCallFalidMessage:(NSString *)reason{
    
}

-(void)zjLogPercentageLost:(NSDictionary *)packet{
    
}

-(void)zjCallBackWithState:(ZJSDKCallState)state
                withReason:(NSString *)reason
                  withUUID:(NSString *)uuid{
    
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    
}


@end
