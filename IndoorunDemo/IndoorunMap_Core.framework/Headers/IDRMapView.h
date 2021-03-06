//
//  IDRMapView.h
//  YFMapKit
//
//  Created by yellfun on 16/2/3.
//  Copyright © 2016年 Sincere. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "IDRMapMarker.h"
#import "IDRMapKitConfig.h"


@class IDRRegion;
@class IDRFloor;
@class IDRPosition;
@class IDRMapModeBtn;
@class IDRMapView;
@class IDRUserLocation;
@class CLHeading;
@class IDRUnit;
@class IDRMap;
@class IDRUnit;
@class IDRNaviSuggestion;
@class IDRFloorView;

@protocol IDRMapViewDelegate <NSObject>

@optional

/**
 地图加载成功

 @param mapView 地图view
 @param region  加载的区域
 @param floor   加载的楼层
 */
- (void)mapViewDidFinishLoading:(IDRMapView *)mapView region:(IDRRegion*)region floor:(IDRFloor*)floor;

/**
 地图状态切换

 @param mapView    地图view
 @param oldMapMode 地图之前的状态
 @param newMode    地图之后的状态
 */
- (void)mapView:(IDRMapView*)mapView didMapModeChange:(IDRMapMode)oldMapMode newMode:(IDRMapMode)newMode;

/**
 地图进行旋转、平移、缩放操作回

 @param mapView 地图view
 */
- (void)mapDidTransform:(IDRMapView *)mapView;

/**
 单击一个marker的回调
 
 @param mapView 地图View
 @param marker 选中的marker

 @return 是否继续响应onClickUnit,onClickMap,为NO时响应继续传递
 */
- (BOOL)mapView:(IDRMapView *)mapView onClickMarker:(id<IDRMapMarkerProtocal>)marker;

/**
 长按marker的回调

 @param mapView 地图view
 @param marker 选中的marker

 @return 是否继续响应onLongPressUnit,onLongPressMap,为NO时响应继续传递
 */
- (BOOL)mapView:(IDRMapView *)mapView onLongPressMarker:(id<IDRMapMarkerProtocal>)marker;

/**
 选中地图上的Unit会回调此接口

 @param mapView 地图View
 @param unit    选中的unit

 @return 是否继续响应onClickMap,为NO时响应继续传递
 */
- (BOOL)mapview:(IDRMapView *)mapView onClickUnit:(IDRUnit*)unit;

/**
 长按unit时会回调此接口

 @param mapview 地图View
 @param unit  地图坐标

 @return 是否继续响应onLongPressMap,为NO时响应继续传递
 */
- (BOOL)mapview:(IDRMapView *)mapView onLongPressUnit:(IDRUnit*)unit;

/**
 *双击地图时会回调此接口
 *@param mapview 地图View
 *@param pos  地图坐标
 */
- (void)mapview:(IDRMapView *)mapView onDoubleClick:(IDRPosition*)pos;

/**
 *单击地图时会回调此接口
 *@param mapview 地图View
 *@param pos  地图坐标
 */
- (void)mapview:(IDRMapView *)mapView onClickMap:(IDRPosition*)pos;

/**
 *长按地图时会回调此接口
 *@param mapview 地图View
 *@param pos  地图坐标
 */
- (void)mapview:(IDRMapView *)mapView onLongPressMap:(IDRPosition*)pos;

@end

/**
 *  地图View类，使用此View可以显示地图窗口，并且对地图进行相关的操作
 */
@interface IDRMapView : UIView

/**
 *  地图当前mode(自由，定位，跟随)
 */
@property (nonatomic, assign) IDRMapMode mapMode;

@property (nonatomic, weak) id<IDRMapViewDelegate> delegate;

/**
 地图显示的区域
 */
@property (nonatomic, retain) IDRRegion *region;

/**
 当前显示的楼层
 */
@property (nonatomic, retain) IDRFloor *currentFloor;

/**
 是否支持旋转缩放平移手势
 */
@property (nonatomic, assign) BOOL enableTransform;

/**
 是否支持点击响应
 */
@property (nonatomic, assign) BOOL enableClick;

/**
 是否支持长按响应
 */
@property (nonatomic, assign) BOOL enableLongPress;

/**
 定位点位置
 */
@property (nonatomic, retain) IDRPosition *userPos;

/**
 opengles地图
 */
@property (nonatomic, retain) IDRMap *glesMap;

/**
 设置当前的位置与方向

 @param userLocation 位置与方位
 */
- (void)setUserLocation:(IDRUserLocation*)userLocation;

/**
 更新设备方向

 @param heading 设备方向
 */
- (void)updateHeading:(CLHeading*)heading;

/**
 加载地图view

 @param region 加载的region
 @param floor  加载的floor
 */
- (void)loadMap:(IDRRegion*)region floor:(IDRFloor*)floor;

/**
 切换楼层

 @param floor 对应楼层数据,可以从IDRRegion中取得

 @return 是否进行切换，切换成功后的回调为- (void)mapViewDidFinishLoading:(IDRMapView *)mapView region:(IDRRegion*)region floor:(IDRFloor*)floor;
 */
- (BOOL)changeFloor:(IDRFloor *)floor;

/**
 缩放

 @param targetScale 目标scale
 @param anchor      设置的锚点
 @param anim        是否渐进动画
 */
- (void)zoom:(CGFloat)targetScale anchor:(CGPoint)anchor anim:(BOOL)anim;

/**
 放大一级比例尺
 */
- (void)zoomIn;

/**
 缩小一级比例尺
 */
- (void)zoomOut;

/**
 平移

 @param x x平移量(屏幕坐标)
 @param y y平移量(屏幕坐标)
 */
- (void)scroll:(CGFloat)x y:(CGFloat)y;

/**
 重置地图(地图的位置、旋转、缩放、倾斜等都重置为加载的默认状态)
 */
- (void)resetMap;

/**
 鸟瞰地图（缩放地图以至能完全显示导航线）
 */
- (void)birdLook;

/**
 居中pos，同时进行缩放

 @param pos 居中的位置（如果pos不在当前显示楼层，会自动切换楼层然后居中）
 */
- (void)centerPos:(IDRPosition*)pos;

/**
 获取导航状态

 @return 当前导航状态，详情参见IDRNaviSuggestion类
 */
- (IDRNaviSuggestion*)getNavStatus;

/**
 显示路径

 @param naviPaths 导航路点
 */
- (void)showPaths:(NSArray*)naviPaths;

/**
 是否显示定位罗盘

 @param show 是否显示
 */
- (void)showComposs:(BOOL)show;

/**
 *  罗盘是否显示偏转圆弧
 */
- (void)showCompossRoute:(BOOL)show;

/**
 添加默认地图状态控件

 @return 地图状态控件
 */
- (IDRMapModeBtn *)addDefaultMapModeBtn;

/**
 添加默认楼层列表控件

 @return 楼层控件
 */
- (IDRFloorView *)addDefaultFloorListView;

/**
 在地图上加上一条字符串

 @param text 字符串内容
 @param p    位置

 @return 返回字符串的ID，需要移除时，调用Removelabel
 */
- (NSInteger)addLabel:(NSString*)text pos:(CGPoint)p;

/**
 移除地图上的字符串

 @param Id 字符串ID
 */
- (void)removeLabel:(NSInteger)Id;

/**
 左上角的指南针按钮
 */
@property (nonatomic, retain) UIButton *compassBtn;

/**
 左下角的地图状态按钮(默认不添加，需要用户主动调用addDefaultMapModeBtn)
 */
@property (nonatomic, retain) IDRMapModeBtn *mapModeBtn;

/**
 地图右上角楼层列表控件(默认不添加，需要用户主动调用addDefaultFloorListView)
 */
@property (nonatomic, retain) IDRFloorView *floorListView;

/**
  是否能切换楼层
 */
@property (nonatomic, assign) BOOL enableChangeFloor;

/**
 根据地图坐标，获取屏幕坐标

 @param mapPos 地图坐标

 @return 屏幕坐标
 */
- (CGPoint)getScreenPos:(IDRPosition*)mapPos;

/**
 根据地图view的坐标，获取地图坐标

 @param screenPoint 地图view上的坐标

 @return 地图坐标
 */
- (IDRPosition*)getMapPos:(CGPoint)screenPoint;

/**
 是否自动切换到定位点所在楼层
 */
@property (nonatomic, assign) BOOL autoChangeToUserFloor;

/**
 当前mapView中所有的marker
 */
@property (nonatomic, retain) NSMutableArray *markers;

/**
 NavState:地图的导航状态（普通状态、导航状态）
 NO   默认为普通状态
 YES  导航状态
 */
@property (nonatomic, assign) BOOL naviState;

@end

/**
 地图View类(和Marker操作相关的接口)
 */
@interface IDRMapView (MarkerAPI)

/**
 向地图view添加Marker

 @param marker 要添加的marker
 */
- (void)addMarker:(id<IDRMapMarkerProtocal>)marker;

/**
 向地图view添加一组marker

 @param markers 要添加的marker数组
 */
- (void)addMarkers:(NSArray*)markers;

/**
 移除marker

 @param marker 要移除的marker
 */
- (void)removeMarker:(id<IDRMapMarkerProtocal>)marker;

/**
 移除一组marker

 @param markers 要移除的marker数组
 */
- (void)removeMarkers:(NSArray*)markers;

/**
 重新设置marker的位置

 @param newPos 新位置
 @param marker 需要设置的marker
 */
- (void)setMarkerPos:(IDRPosition*)newPos marker:(id<IDRMapMarkerProtocal>)marker;

/**
 重新设置marker的图标

 @param newIcon 新icon
 @param marker 需要设置的marker
 */
- (void)setMarkerImage:(NSString*)newIcon marker:(id<IDRMapMarkerProtocal>)marker;

@end


