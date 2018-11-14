//
//  tools.h
//  sipclient
//
//  Created by Marcin Kielesiński on 09.10.2017.
//

#ifndef tools_h
#define tools_h

#include <stdio.h>

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#import <SystemConfiguration/SystemConfiguration.h>
#import <SystemConfiguration/CaptiveNetwork.h>
#import <execinfo.h>
#include <sys/types.h>
#include <sys/utsname.h>
#include <sys/time.h>   // gettimeofday

#if DEBUG
#define Debug_ENABLED  true
#else
#define Debug_ENABLED  false
#endif

#ifndef null
#define null nil
#endif

#define EXCEPTIONS_ENABLED false

void lj_deb(NSString *format);
void lj_err(NSString *format);

#define debf(format, ...) {if(Debug_ENABLED){dbg_n(@"%@", [NSString stringWithFormat:format, ## __VA_ARGS__]);}}
#define deb(format, ...) {if(Debug_ENABLED){NSString *__oo = [NSString stringWithFormat: @"%s:%@", __PRETTY_FUNCTION__, [NSString stringWithFormat:format, ## __VA_ARGS__]]; NSLog(@"%@", __oo); lj_deb(__oo); }}
#define networkdeb(format, ...) {if(Debug_ENABLED){NSString *__oo = [NSString stringWithFormat:format, ## __VA_ARGS__]; NSLog(@"%@\n", _oo); lj_deb(__oo); }
#define err(format, ...) {if(Debug_ENABLED){NSString *__oo = [NSString stringWithFormat: @"💩⛔️%s:%@", __PRETTY_FUNCTION__, [NSString stringWithFormat:format, ## __VA_ARGS__]]; NSLog(@"%@", __oo); lj_err(__oo); }}
#define debN(format, ...) {if(Debug_ENABLED){NSString *__oo = [NSString stringWithFormat: @"%s:%@", __PRETTY_FUNCTION__, [NSString stringWithFormat:format, ## __VA_ARGS__]]; IFPrint(@"%@", __oo); lj_deb(__oo);  }}

#define safeputc(c)    debf(@"%c", c);

#define sleepF(s) usleep((useconds_t)(s * 1000000))

long _max(long a, long b);
long _min(long a, long b);
int gmt2local(time_t t);
NSString * plus(id first, ...);
void presentAlertOnRoot(UIAlertController *alert);
UIAlertController *createAlertWith(NSString *title, NSString *message);
UIAlertAction* getCancelButtonForAlert(UIAlertController *alert);
void showSimpleAlert(NSString *title, NSString *message);
const char *toCString(NSString *string);
bool isEmpty(NSObject *o);
bool startsWith(const char *pre, const char *str);
NSString *htmlEscapedString(NSString *string);
NSString *htmlUnescapedString(NSString *string);
NSString *fromCString(const char *string);
NSString *toStringFromChar(const char letter);
NSString* getDeviceArchitecture(void);
NSString *getDeviceModel(void);
NSString *getDeviceName(void);
NSString *deviceUDID(void);
NSString *appVersion(void);
NSString *builVersion(void);
NSString *appVersionNumber(void);
NSString *getUserAgent(void);
void toLowerString(char *p);
void removeSpaces(char *p);
int random_number(int min_num, int max_num);
long GetTickCount(void);

CGFloat getWidth(void);
CGFloat getHeight(void);
CGFloat percentOf(CGFloat currentval, CGFloat maxval);

void printStackTrace(void);
void dbg_n(NSString *format, ...);
void dbg(NSString *format);
void dbge(NSString *format);
void thr(NSString *format);

void showLastNetworkError(char *function);

#endif /* tools_h */
