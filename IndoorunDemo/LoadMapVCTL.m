//
//  LoadMapVCTL.m
//  IndoorunDemo
//
//  Created by ky on 10/11/16.
//  Copyright © 2016 yellfun. All rights reserved.
//

#import "LoadMapVCTL.h"

@interface LoadMapVCTL ()<IDRMapViewDelegate>

@property (nonatomic) IDRMapView *mapView;

@end

@implementation LoadMapVCTL

- (void)viewDidLoad {
    
    [super viewDidLoad];
    
    [self loadMap];
}

- (void)loadMap {
    
    _mapView = [[IDRMapView alloc] initWithFrame:self.view.bounds];
    
    _mapView.delegate = self;
    
    [_mapView loadMap:_region floor:_region.defaultFloor];
    
    [self.view addSubview:_mapView];
    
    [_mapView addDefaultFloorListView];
}

#pragma mark --mapviewdelegate

- (void)mapViewDidFinishLoading:(IDRMapView *)mapView region:(IDRRegion *)region floor:(IDRFloor *)floor {
    
    NSLog(@"加载地图%@:%@成功", region.name, floor.title);
}

@end
