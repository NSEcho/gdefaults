#import <Foundation/Foundation.h>

CFDictionaryRef _CFPreferencesCopyMultipleWithContainer(CFArrayRef keysToFetch, CFStringRef applicationID, CFStringRef userName, CFStringRef hostName, CFStringRef container);

char * get_domains(void)
{
   NSMutableArray * all_domains = [(__bridge NSArray*)CFPreferencesCopyApplicationList(kCFPreferencesCurrentUser, kCFPreferencesAnyHost) mutableCopy];
   char * domains = [all_domains componentsJoinedByString:@" "].UTF8String;

   CFRelease(all_domains);
   return domains;
}

char * read_key(const char * app, const char * key)
{
    CFStringRef container = CFSTR("kCFPreferencesNoContainer");
    CFStringRef appId = CFStringCreateWithCString(kCFAllocatorDefault, app, kCFStringEncodingMacRoman);
    NSDictionary * res = (__bridge NSDictionary*)_CFPreferencesCopyMultipleWithContainer(NULL, (__bridge CFStringRef)appId,
        kCFPreferencesCurrentUser, kCFPreferencesAnyHost, container);
    if (key == NULL) {
        char * ret = res.description.UTF8String;
        CFRelease(res);
        return ret;
    } else {
        NSString * keyS = [NSString stringWithCString:key];
        if ([res objectForKey:keyS] != nil) {
            char * ret = [[res objectForKey:keyS] description].UTF8String;
            CFRelease(res);
            return ret;
        }
        CFRelease(res);
        return NULL;
    }
}
