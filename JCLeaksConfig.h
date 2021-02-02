//
//  JCLeaksConfig.h
//  FBRetainCycleDetector
//
//  Created by JerryChu on 2021/1/11.
//  Copyright © 2020 JerryChu. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

typedef void (^JCLeaksFinderCallback)(NSObject *leakedObject, NSSet *retainInfo, NSArray<NSString *> *viewStack);

@interface JCLeaksConfig : NSObject

+ (JCLeaksConfig *)sharedInstance;

/// 内存泄漏检测结果回调
/// leakedObject -> 泄漏对象
/// retainInfo -> 引用链信息，可能包含多个。不用关心`retainInfo`的具体数据，直接调用`[retainInfo description]`输出结果即可。
/// viewStack -> 泄漏对象层级信息
@property(nonatomic, copy) JCLeaksFinderCallback callback;

/// 检测阈值，默认为5s。退出页面`detectThresholdInSeconds`秒后开始检测是否有内存泄漏。
@property(nonatomic, assign) NSUInteger detectThresholdInSeconds;

/// 检测循环引用的最大引用链长度，默认为`10`。
@property(nonatomic, assign) NSUInteger retainCycleMaxLength;

/// 检测全局对象引用的最大引用链长度，默认为`15`。
@property(nonatomic, assign) NSUInteger globalRetainMaxLength;

/// 是否检测全局对象引用，默认为`YES`。检测全局对象引用耗时较高（约2-3s），在子线程进行
@property(nonatomic, assign) BOOL checkGlobalRetain;

/// 添加自定义的全局对象，默认为`nil`。
/// 有些对象并不是全局对象，但是会在APP生命周期内一直存活，如APP的rootNavigationController、rootTabBarController等
/// 在检测进行全局对象时，会将 `extraGlobalObjects` 也作为全局对象进行引用检测
@property(nonatomic, copy) NSArray<NSObject *> *extraGlobalObjects;

/// 添加白名单类名
- (void)addClassNamesToWhiteList:(NSArray<NSString *> *)classNames;

/// 添加白名单对象。该对象不会被内部持有。
- (void)addObjectToWhiteList:(NSObject *)object;

@end

NS_ASSUME_NONNULL_END
