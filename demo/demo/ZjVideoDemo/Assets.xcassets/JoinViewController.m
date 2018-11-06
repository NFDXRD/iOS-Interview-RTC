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
@property (weak, nonatomic) IBOutlet UITextField *displayNameTf;
@property (nonatomic, strong) ZjRCTManager *manager;

@end

@implementation JoinViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    self.manager = [ZjRCTManager sharedManager];
    self.manager.delegate = self;
    [self.manager setApiServer:@"cs.zijingcloud.com"];
}

- (IBAction)clickJoinDefult:(id)sender {
    NSMutableDictionary *conferenceModel = [NSMutableDictionary dictionary];
//    [conferenceModel ZJSDKVideoInterview:self.sipkeyTf.text
//                             displayName:self.displayNameTf.text];
    
    [conferenceModel ZJSDKVideoInterview:self.sipkeyTf.text
                             displayName:self.displayNameTf.text
                                password:@"123456" checkdup:@""];
    
    [self.manager selectReceiveVideoModel:ReceiveVideoModelSimulcast];
    
    //  或者按照 makedown中提示。
    [self.manager openAppTerminateListening];
    
    [self.manager connectWithModel:conferenceModel
                       andCapacity:ConncetCapacityModelHost];
    
    
    videoVC = [[VideoViewController alloc]init];
    self.manager.conferenceView.frame = CGRectMake(0, 0, [UIScreen mainScreen].bounds.size.width, [UIScreen mainScreen].bounds.size.width);
    [videoVC.view addSubview:self.manager.conferenceView];
    
    [self presentViewController:videoVC animated:NO completion:nil];
}

- (IBAction)clickJoinCostum:(id)sender {
    
    NSMutableDictionary *conferenceModel = [NSMutableDictionary dictionary];
    [conferenceModel ZJSDKVideoInterview:self.sipkeyTf.text
                             displayName:self.displayNameTf.text];
    
    [self.manager selectReceiveVideoModel:ReceiveVideoModelSimulcast];
    
    
    
    [self.manager connectWithModel:conferenceModel
                       andCapacity:ConncetCapacityModelGuest];
    
    videoVC = [[VideoViewController alloc]init];
    self.manager.conferenceView.frame = CGRectMake(0, 0, [UIScreen mainScreen].bounds.size.width, [UIScreen mainScreen].bounds.size.width);
    [videoVC.view addSubview:self.manager.conferenceView];
    
    [self presentViewController:videoVC animated:NO completion:nil];
}

- (void)receiveMessage:(NSDictionary *)message {
    NSLog(@"接收到发来的信息: %@",message);
}

- (void)changeParticipants:(NSArray *)participants {
    NSLog(@"当前与会者信息%@",participants);
}

- (void)videoChangeStatus:(BOOL)open {
    NSLog(@"语音状态%@", (open ? @"打开" : @"关闭") );
}

- (void)localParticipant:(NSDictionary *)localParticipant {
    NSLog(@"本地参会者改变 --- %@",localParticipant);
}


- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    
}


@end
