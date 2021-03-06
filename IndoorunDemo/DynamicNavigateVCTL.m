//
//  DynamicNavigateVCTL.m
//  IndoorunDemo
//
//  Created by ky on 10/12/16.
//  Copyright © 2016 yellfun. All rights reserved.
//

#import "DynamicNavigateVCTL.h"

@interface DynamicNavigateVCTL ()<IDRMapViewDelegate, IDRNavigationServerDelegate, IDRLocationServerDelegate>

@property (nonatomic, retain) IDRMapView *mapView;
@property (nonatomic, retain) IDRPosition *ep;
@property (nonatomic, retain) IDRCarMarker *carMarker;
@property (nonatomic, retain) IBOutlet UILabel *ibDebug;
@property (nonatomic, strong) IDRLocationServer *locator;
@property (nonatomic, strong) IDRNavigationServer *navigator;

@end

@implementation DynamicNavigateVCTL

- (void)viewDidLoad {
    
    [super viewDidLoad];
    
    [self loadMap];
    
    [self locate];
}

- (void)loadMap {
    
    _mapView = [[IDRMapView alloc] init];
    
    [_mapView loadMap:_region floor:_region.defaultFloor];
    
    _mapView.delegate = self;
    
    [self.view addSubview:_mapView];
    
    [self.view sendSubviewToBack:_mapView];
    
    [_mapView addDefaultFloorListView];
    
    [_mapView addDefaultMapModeBtn];
}

- (void)locate {
    
    if (!_locator) {
        
        _locator = [IDRLocationServer instance];
    }
    
    [_locator startServer:_region];
    
    [_locator setDelegate:self];
}

- (IBAction)onStopNavigation:(id)sender {
    
    [_navigator stopServer];
    
    [_mapView removeMarker:_carMarker];
    
    _carMarker = nil;
    
    [_mapView setNaviState:NO];
    
    [_ibDebug setText:@"导航结束"];
}

#pragma mark --MapView Delegate
- (void)mapview:(IDRMapView *)mapView onClickMap:(IDRPosition *)pos {
    
    if (!_ep) {
        
        _ep = pos;
        
        _carMarker = [[IDRCarMarker alloc] initWith:pos];
        
        [_mapView addMarker:_carMarker];
        
        if (!_navigator) {
            
            _navigator = [IDRNavigationServer instance];
        }
        
        [_navigator setDelegate:self];
        
        //设置地图，不然不会显示导航线
        [_navigator setMapView:_mapView];
        
        //动态导航需设置定位器
        [_navigator setLocater:_locator];
        //动态导航，起点设置为nil
        [_navigator startServer:_region navi:[IDRNaviParm createWith:nil end:_ep]];
    }
}

#pragma mark --LocationServer Delegate 
- (void)location:(IDRLocationServer *)locationServer didLocationSuccess:(IDRUserLocation *)userLocation {
    
    [_mapView setUserLocation:userLocation];
}

#pragma mark --NavigationServer Delegate
- (void)navigation:(IDRNavigationServer *)sender didStartSuccess:(NaviServerStartStatus)status naviParm:(IDRNaviParm *)naviParm {
    
    if (status == NaviServerStartStatus_Success) {
        
        [_ibDebug setText:@"导航启动成功"];
    }
    
    if (status == NaviServerStartStatus_LocationServerFailed) {
        
        [_ibDebug setText:@"定位失败，动态导航启动失败"];
    }
    
    if (status == NaviServerStartStatus_TooNear) {
        
        [_ibDebug setText:@"地点终点距离太近，动态导航启动失败"];
    }
    
    if (status == NaviServerStartStatus_PassNotFind) {
        
        [_ibDebug setText:@"楼层之间没有连通性，动态导航启动失败"];
    }
}

- (void)navigation:(IDRNavigationServer *)sender didUpdateSuggestion:(IDRNaviSuggestion *)naviSuggestion {
    
    [_ibDebug setAttributedText:naviSuggestion.getNaviStatusText];
}

- (void)navigationDidFinish:(IDRNavigationServer *)sender {
    
    [_ibDebug setText:@"导航完毕"];
}

@end
