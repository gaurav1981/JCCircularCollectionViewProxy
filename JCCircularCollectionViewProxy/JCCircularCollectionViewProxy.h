//
//  JCCircularCollectionViewProxy.h
//
//  Created by Jonathan Crooke on 10/04/2014.
//  Copyright (c) 2014 Jonathan Crooke. All rights reserved.
//

#import <UIKit/UIKit.h>

/**
 Protocol wrapper.
 
 @note `-collectionView:cellForItemAtIndexPath:` must still be overridden in order to dequeue
 the appropriate cell. *Don't customise the cell here*; use
 `-collectionView:configureCell:forIndexPath:`

  - (UICollectionViewCell *) collectionView:(UICollectionView *)collectionView
                     cellForItemAtIndexPath:(NSIndexPath *)indexPath
  {
    return [collectionView dequeueReusableCellWithReuseIdentifier:@"MyIdentifier"
                                                     forIndexPath:indexPath];
  }

 */
@protocol JCCircularCollectionViewProxyDataSource <UICollectionViewDataSource>
@required
/**
 *  Required additional method for actually configuring the dequeud cell.
 *
 *  @param collectionView The collection view
 *  @param cell           A dequeued reusable cell for the collection view
 *  @note  #protip - cast the cell argument to the expected cell subclass.
 *  @param indexPath      "True" index path for the cell, based on the data source's
 *  real item count.
 */
- (void) collectionView:(UICollectionView*) collectionView
          configureCell:(id) cell
           forIndexPath:(NSIndexPath*) indexPath;
@end

/**
 *  Proxy object
 */
@interface JCCircularCollectionViewProxy : NSObject
  <UICollectionViewDataSource, UICollectionViewDelegateFlowLayout>

/**
 *  Designated initialiser
 *
 *  @param dataSource Object that conforms to the proxy data source
 *  @param delegate   Collection view delegate - can be `nil`.
 *
 *  @return Proxy
 */
+ (instancetype) proxyWithDataSource:(id <JCCircularCollectionViewProxyDataSource>) dataSource
                            delegate:(id <UICollectionViewDelegateFlowLayout>)delegate;

/**
 *  Required additional set up, once the collection view itself has been created
 *  and laid-out.
 *
 *  @param collectionView The collection view to use.
 */
- (void) configureForCollectionView:(UICollectionView*) collectionView;

/**
 *  I'm useless.
 */
- (id)init __attribute__((deprecated("Use initWithDataSource:delegate:")));

@end

/**
 *  Convenience initialiser category
 */
@interface UICollectionView (CircularProxy)
/**
 *  Instantiate a proxy object and configure the receiver for it in one fell swoop.
 *
 *  @param dataSource Data source
 *  @param delegate   Optional delegate
 *
 *  @return Instantiated proxy - store in a `strong` property!
 */
- (JCCircularCollectionViewProxy*) circularProxyWithDataSource:(id <JCCircularCollectionViewProxyDataSource>) dataSource
                                                      delegate:(id <UICollectionViewDelegateFlowLayout>)delegate;
@end