//
//  VideoViewController.m
//  ZjVideoDemo
//
//  Created by 李志朋 on 2017/12/15.
//  Copyright © 2017年 李志朋. All rights reserved.
//

#import "VideoViewController.h"
#import "ZjRCTManager.h"

@interface VideoViewController () <UICollectionViewDelegate,UICollectionViewDataSource,ZJVideoManagerDelegate>

@property (nonatomic, strong) NSArray *btns ;
@property (nonatomic, strong) UICollectionView *collectionView;
@property (nonatomic, strong) ZjRCTManager *manager ;

@end

NSString *const JoinConferenceCellId = @"JoinConferenceCellId";
NSString *const JoinConferenceHeaderId = @"JoinConferenceHeaderId";
NSString *const JoinConferenceFooterId = @"JoinConferenceFooterId";

@implementation VideoViewController

- (NSArray *)btns{
    if (!_btns) {
        _btns = @[@"静音",@"静画",@"切换摄像头",@"离开",@"全部离开",@"邀请",@"发送消息",@"打开录制",@"关闭录制"];
    }
    return _btns;
}

- (ZjRCTManager *)manager {
    if (!_manager) {
        _manager = [[ZjRCTManager alloc]init];
    }
    return _manager ;
}

- (UICollectionView *)collectionView {
    if (!_collectionView) {
        
        UILabel *label = [[UILabel alloc]initWithFrame:CGRectMake(0, 20, self.view.frame.size.width, 0.5)];
        label.backgroundColor = [UIColor clearColor];
        [self.view addSubview:label];
        UICollectionViewFlowLayout *customLayout = [[UICollectionViewFlowLayout alloc] init];
        //自定义的布局对象
        
        //同一行相邻两个cell的最小间距
        customLayout.minimumInteritemSpacing = 5;
        //最小两行之间的间距
        customLayout.minimumLineSpacing = 5;
        _collectionView = [[UICollectionView alloc] initWithFrame:CGRectMake(0, self.view.frame.size.width, self.view.frame.size.width, self.view.frame.size.height - self.view.frame.size.width) collectionViewLayout:customLayout];
        _collectionView.backgroundColor = [UIColor whiteColor];
        _collectionView.contentInset = UIEdgeInsetsMake(0, 0, 0, 0);
        _collectionView.delegate = self;
        _collectionView.dataSource = self;
        [self.view addSubview:_collectionView];
        
        // 注册cell、sectionHeader、sectionFooter
        [_collectionView registerClass:[UICollectionViewCell class] forCellWithReuseIdentifier:JoinConferenceCellId];
        [_collectionView registerClass:[UICollectionReusableView class] forSupplementaryViewOfKind:UICollectionElementKindSectionHeader withReuseIdentifier:JoinConferenceHeaderId];
        [_collectionView registerClass:[UICollectionReusableView class] forSupplementaryViewOfKind:UICollectionElementKindSectionFooter withReuseIdentifier:JoinConferenceFooterId];
    }
    return _collectionView;
}

- (void)viewDidLoad {
    [super viewDidLoad];
    [self.view addSubview:self.collectionView];
}

-(void)viewWillAppear:(BOOL)animated{
    [super viewWillAppear:animated];
}

-(void)viewDidAppear:(BOOL)animated{
    [super viewDidAppear:animated];
    
}

#pragma mark - UICollectionDelegate && UICollectionDateSoure
- (NSInteger)numberOfSectionsInCollectionView:(UICollectionView *)collectionView {
    return 1;
}

- (NSInteger)collectionView:(UICollectionView *)collectionView numberOfItemsInSection:(NSInteger)section {
    return self.btns.count;
}

- (UICollectionViewCell *)collectionView:(UICollectionView *)collectionView cellForItemAtIndexPath:(NSIndexPath *)indexPath {
    
    UICollectionViewCell *cell = [collectionView dequeueReusableCellWithReuseIdentifier:JoinConferenceCellId forIndexPath:indexPath];
    UIButton *btn= [UIButton buttonWithType:UIButtonTypeRoundedRect];
    btn.frame = CGRectMake(0, 0, cell.frame.size.width, cell.frame.size.height) ;
    [btn setTitle:self.btns[indexPath.row] forState:UIControlStateNormal];
    [btn.layer setCornerRadius:5];
    [btn.layer setMasksToBounds:YES];
    btn.backgroundColor = [UIColor colorWithRed:239/255.0 green:239/255.0 blue:239/255.0 alpha:1];
    btn.titleLabel.textAlignment = NSTextAlignmentCenter ;
    btn.titleLabel.font = [UIFont systemFontOfSize:12];
    btn.tag = indexPath.row;
    [btn addTarget:self action:@selector(clickCellIndexPatchButton:) forControlEvents:UIControlEventTouchUpInside];
    [cell.contentView addSubview:btn];

    return cell;
}

- (void)clickCellIndexPatchButton:(UIButton *)btn {
    NSInteger tag = btn.tag ;
    
    if ( tag == 0 ) {
        [self.manager toggleLocalAudio:!self.manager.openAudio];
        
        NSLog(@"------> %d", self.manager.openAudio);
    } else if ( tag == 1 ) {
        [self.manager toggleLocalVideo:!self.manager.openVideo];
    } else if ( tag == 2 ) {
        [self.manager toggleCamera:( self.manager.cameraStatus == ConferenceCameraStatusBack ? ConferenceCameraStatusFront : ConferenceCameraStatusBack )];
    } else if ( tag == 3 ) {
        [self.manager outOfCurrentMeeting];
        [[NSNotificationCenter defaultCenter]postNotificationName:@"aaaa" object:nil];

        
        [self dismissViewControllerAnimated:NO completion:nil];
    } else if ( tag == 4 ) {
        [self.manager endAllMeeting];
    } else if ( tag == 5 ) {
        [self.manager inviteUserAccount:@"lizhipeng@zijingcloud.com"
                               withRole:InviteParticipantRoleGuest
                           withProtocol:InviteParticipantProtocolAuto];
    } else if ( tag == 6 ) {
        [self.manager sendMessage:@"这是发送的消息"];
    } else if ( tag == 7 ) {
        [self.manager openRecorder];
    } else if ( tag == 8 ) {
        [self.manager closeRecorder];
    }
}

// 和UITableView类似，UICollectionView也可设置段头段尾
- (UICollectionReusableView *)collectionView:(UICollectionView *)collectionView viewForSupplementaryElementOfKind:(NSString *)kind atIndexPath:(NSIndexPath *)indexPath {
    if([kind isEqualToString:UICollectionElementKindSectionHeader]) {
        UICollectionReusableView *headerView = [collectionView dequeueReusableSupplementaryViewOfKind:kind withReuseIdentifier:JoinConferenceHeaderId forIndexPath:indexPath];
        if(headerView == nil) {
            headerView = [[UICollectionReusableView alloc] init];
        }
        return headerView;
    } else if([kind isEqualToString:UICollectionElementKindSectionFooter]){
        UICollectionReusableView *footerView = [collectionView dequeueReusableSupplementaryViewOfKind:kind withReuseIdentifier:JoinConferenceFooterId forIndexPath:indexPath];
        if(footerView == nil) {
            footerView = [[UICollectionReusableView alloc] init];
        }
        return footerView;
    }
    return nil;
}

- (CGSize)collectionView:(UICollectionView *)collectionView layout:(UICollectionViewLayout*)collectionViewLayout sizeForItemAtIndexPath:(NSIndexPath *)indexPath {
   return (CGSize){(self.view.frame.size.width/5.0 - 1),44};
}

- (UIEdgeInsets)collectionView:(UICollectionView *)collectionView layout:(UICollectionViewLayout*)collectionViewLayout insetForSectionAtIndex:(NSInteger)section {
    return UIEdgeInsetsMake(10, 10, 10, 10);
}

- (CGFloat)collectionView:(UICollectionView *)collectionView layout:(UICollectionViewLayout*)collectionViewLayout minimumLineSpacingForSectionAtIndex:(NSInteger)section {
    return 10;
}

- (CGFloat)collectionView:(UICollectionView *)collectionView layout:(UICollectionViewLayout*)collectionViewLayout minimumInteritemSpacingForSectionAtIndex:(NSInteger)section {
    return 10;
}

- (CGSize)collectionView:(UICollectionView *)collectionView layout:(UICollectionViewLayout*)collectionViewLayout referenceSizeForHeaderInSection:(NSInteger)section {
    return (CGSize){375,0.1};
}

- (CGSize)collectionView:(UICollectionView *)collectionView layout:(UICollectionViewLayout*)collectionViewLayout referenceSizeForFooterInSection:(NSInteger)section {
    return (CGSize){375,0.1};
}

// 选中某item
- (void)collectionView:(UICollectionView *)collectionView didSelectItemAtIndexPath:(NSIndexPath *)indexPath {
    
}

@end
