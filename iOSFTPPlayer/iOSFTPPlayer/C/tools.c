//
//  tools.c
//  sipclient
//
//  Created by Marcin Kielesiński on 09.10.2017.
//

#include "tools.h"

long _max(long a, long b) {
    return (((a)<(b))?(a):(b));
}

long _min(long a, long b) {
    return (((a)>(b))?(a):(b));
}

/*
 * Returns the difference between gmt and local time in seconds.
 */
int gmt2local(time_t t) {
    register int dt, dir;
    register struct tm *gmt, *loc;
    struct tm sgmt;
    
    if (t == 0)
        t = time(NULL);
    gmt = &sgmt;
    *gmt = *gmtime(&t);
    loc = localtime(&t);
    dt = (loc->tm_hour - gmt->tm_hour) * 60 * 60 +
    (loc->tm_min - gmt->tm_min) * 60;
    
    /*
     * If the year or julian day is different, we span 00:00 GMT
     * and must add or subtract a day. Check the year first to
     * avoid problems when the julian day wraps.
     */
    dir = loc->tm_year - gmt->tm_year;
    if (dir == 0)
        dir = loc->tm_yday - gmt->tm_yday;
    dt += dir * 24 * 60 * 60;
    
    return (dt);
}

NSString * plus(id first, ...){
    NSString * result = @"";
    id eachArg;
    va_list alist;
    if(first) {
        result = [result stringByAppendingString:[[NSString alloc] initWithFormat: @"%@", first]];
        va_start(alist, first);
        while ((eachArg = va_arg(alist, id)))
            result = [result stringByAppendingString:[[NSString alloc] initWithFormat: @"%@", eachArg]];
        va_end(alist);
    }
    return result;
}

UIAlertController *createAlertWith(NSString *title, NSString *message){
    return [UIAlertController alertControllerWithTitle:title message:message preferredStyle:(UIAlertControllerStyleAlert)];
}

UIAlertAction* getCancelButtonForAlert(UIAlertController *alert) {
    return [UIAlertAction
            actionWithTitle:NSLocalizedString(@"cancel", nil)
            style:UIAlertActionStyleDefault
            handler:^(UIAlertAction * action) {
            [alert dismissViewControllerAnimated:true completion:nil];
            }];
}

void presentAlertOnRoot(UIAlertController *alert) {
    UIViewController *vc = [[[[UIApplication sharedApplication] delegate] window] rootViewController];
    [vc presentViewController:alert animated:YES completion:nil];
}

void showSimpleAlert(NSString *title, NSString *message) {
    UIAlertController *alert = createAlertWith(title, message);
    [alert addAction:getCancelButtonForAlert(alert)];
    presentAlertOnRoot(alert);
}

static NSString *replaceAll(NSString *s, NSDictionary *replacements) {
    
    for (NSString *key in replacements) {
        NSString *replacement = [replacements objectForKey:key];
        s = [s stringByReplacingOccurrencesOfString:key withString:replacement];
    }
    return s;
}

static NSDictionary *htmlEscapes = nil;
static NSDictionary *htmlUnescapes = nil;

NSString *htmlEscapedString(NSString *string) {
    if (!htmlEscapes) {
        htmlEscapes = [[NSDictionary alloc] initWithObjectsAndKeys:
                       @"&amp;", @"&",
                       @"&lt;", @"<",
                       @"&gt;", @">",
                       @"&quot;", @"\"",
                       nil
                       ];
    }
    return replaceAll(string, htmlEscapes);
}

NSString *htmlUnescapedString(NSString *string) {
    if (!htmlUnescapes) {
        htmlUnescapes = [[NSDictionary alloc] initWithObjectsAndKeys:
                         @"&", @"&amp;",
                         @"<", @"&lt;",
                         @">", @"&gt;",
                         @"\"", @"&quot;",
                         nil
                         ];
    }
    
    return replaceAll(string, htmlUnescapes);
}

const char *toCString(NSString *string){
    return string.UTF8String;
}

void toLowerString(char *p){
    for ( ; *p; ++p) *p = tolower(*p);
}

void removeSpaces(char *p){
    char *s = strdup(p);
    if(s){
        
        char *np = p, *op = s;
        do {
            if (*op != ' ')
                *np++ = *op;
        } while (*op++);
        
        free(s);
    }
}

NSString *fromCString(const char *string){
    if(string != nil){
        return [NSString stringWithUTF8String:string];
    }
    return @"";
}

NSString *toStringFromChar(const char letter){
    char string[2];
    memset(string, 0, sizeof(string));
    string[0] = letter;
    return fromCString(string);
}

bool isEmpty(NSObject *o) {
    if(o == nil) {
        return true;
    }
    if([o isKindOfClass: [NSString class]]) {
        return !(((NSString*)o).length > 0);
    }
    if([o isKindOfClass: [NSArray class]]) {
        return !(((NSArray*)o).count > 0);
    }
    if([o isKindOfClass: [NSDictionary class]]) {
        return !(((NSDictionary*)o).count > 0);
    }
    if([o isKindOfClass: [NSData class]]) {
        return !(((NSData*)o).length > 0);
    }
    return true;
}

bool startsWith(const char *pre, const char *str) {
    size_t lenpre = strlen(pre),
    lenstr = strlen(str);
    return lenstr < lenpre ? false : strncmp(pre, str, lenpre) == 0;
}

NSString* getDeviceArchitecture(void){
    struct utsname systemInfo;
    uname(&systemInfo);
    return fromCString(systemInfo.machine);
}

NSString *getDeviceModel(void){
    return UIDevice.currentDevice.model;
}

NSString *getDeviceName(void){
    return UIDevice.currentDevice.name;
}

NSString *getUserAgent(void){
    NSString *ua = [[NSMutableString alloc]
                        initWithString:[NSString
                                        stringWithFormat:@"%@_%@(%@)_iOS%@",
                                        [NSBundle.mainBundle objectForInfoDictionaryKey:@"CFBundleDisplayName"],
                                        getDeviceModel(), getDeviceArchitecture(),
                                        UIDevice.currentDevice.systemVersion]];
    ua = [ua stringByReplacingOccurrencesOfString:@"," withString:@"."];
    ua = [ua stringByReplacingOccurrencesOfString:@" " withString:@"."];
    return ua;
}

NSString *deviceUDID(void){
    return UIDevice.currentDevice.identifierForVendor.UUIDString;
}

NSString *appVersion(void) {
    return [[[NSBundle mainBundle] infoDictionary] objectForKey:@"CFBundleShortVersionString"];
}

NSString *builVersion(void) {
    return [[[NSBundle mainBundle] infoDictionary] objectForKey:@"CFBundleVersion"];
}

NSString *appVersionNumber(void){
	return plus(appVersion(), @".", builVersion(), nil);
}

CGFloat getWidth(void) {
    CGRect screenRect = [[UIScreen mainScreen] bounds];
    return screenRect.size.width;
}

CGFloat getHeight(void) {
    CGRect screenRect = [[UIScreen mainScreen] bounds];
    return screenRect.size.height;
}

CGFloat percentOf(CGFloat percent, CGFloat ofValue){
    return percent * ofValue / 100.f;
}

int random_number(int min_num, int max_num) {
    int result = 0, low_num = 0, hi_num = 0;
    
    if (min_num < max_num) {
        low_num = min_num;
        hi_num = max_num + 1; // include max_num in output
    } else {
        low_num = max_num + 1; // include max_num in output
        hi_num = min_num;
    }
    
    srand((unsigned int)time(NULL));
    result = (rand() % (hi_num - low_num)) + low_num;
    return result;
}

long GetTickCount(void) {
    struct timeval t;
    gettimeofday(&t, NULL);
    
    return t.tv_sec * 1000 + t.tv_usec / 1000;
}

void printStackTrace(void) {
    if(Debug_ENABLED){
        deb(@"---------START STACK----------");
        void *stackAdresses[32];
        int stackSize = backtrace(stackAdresses, 32);
        backtrace_symbols_fd(stackAdresses, stackSize, STDOUT_FILENO);
        deb(@"----------END STACK-----------");
    }
}

void dbg_n(NSString *format, ...) {
    if(Debug_ENABLED){
        va_list args;
        va_start (args, format);
        NSString *string;
        string = [[NSString alloc] initWithFormat: format  arguments: args];
        va_end (args);
        printf ("%s", toCString(string));
        lj_deb(string);
    }
}

void dbg(NSString *format) {
    if(Debug_ENABLED){
        NSLog(@"%@", format);
        lj_deb(format);
    }
}

void dbge(NSString *format) {
    if(Debug_ENABLED){
        NSLog(@"💩⛔️ %@", format);
        if(EXCEPTIONS_ENABLED){
            printStackTrace();
        }
        lj_err(format);
    }
}

void showLastNetworkError(char *function) {
    if(Debug_ENABLED){
        dbge([[NSString alloc] initWithFormat: @"%s error : %d", function, errno]);
        perror(function);
    }
}

void thr(NSString *format) {
    [NSException raise:@"Exception" format:@"body:%@", format];
}


void lj_deb(NSString *format){
//    #if DEBUG_TESTFLIGHT
//    dispatch_async(dispatch_get_main_queue(), ^{
//        DDLogMessage *msg = [[DDLogMessage alloc] initWithMessage:format
//                                                            level:DDLogLevelInfo
//                                                             flag:DDLogFlagDebug
//                                                          context:0
//                                                             file:@""
//                                                         function:@""
//                                                             line:0
//                                                              tag:nil
//                                                          options:DDLogMessageCopyFunction
//                                                        timestamp:nil];
//
//        [[UIForLumberjack sharedInstance] logMessage:msg];
//    });
//    #endif
}

void lj_err(NSString *format){
//    #if DEBUG_TESTFLIGHT
//    dispatch_async(dispatch_get_main_queue(), ^{
//        DDLogMessage *msg = [[DDLogMessage alloc] initWithMessage:format
//                                                            level:DDLogLevelInfo
//                                                             flag:DDLogFlagError
//                                                          context:0
//                                                             file:@""
//                                                         function:@""
//                                                             line:0
//                                                              tag:nil
//                                                          options:DDLogMessageCopyFunction
//                                                        timestamp:nil];
//
//
//        [[UIForLumberjack sharedInstance] logMessage:msg];
//    });
//    #endif
}
