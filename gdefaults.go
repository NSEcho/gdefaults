package gdefaults

/*
#cgo CFLAGS: -x objective-c -Wno-deprecated-declarations -Wno-incompatible-pointer-types-discards-qualifiers
#cgo LDFLAGS: -framework Foundation -lobjc
#include "helper.h"
#import <Foundation/Foundation.h>
*/
import "C"
import (
	"strings"
	"unsafe"
)

// Domains returns all domains without kCFPreferencesAnyApplication
func Domains() []string {
	domc := C.get_domains()
	defer C.free(unsafe.Pointer(domc))

	doms := C.GoString(domc)
	domains := strings.Split(doms, " ")

	return domains
}

// Read will return all keys as a string for specific domain or a value for specific domain and key
func Read(domain, key string) string {
	d := C.CString(domain)
	defer C.free(unsafe.Pointer(d))

	var k *C.char = nil
	if key != "" {
		k = C.CString(key)
		defer C.free(unsafe.Pointer(k))
	}

	res := C.read_key(d, k)
	return C.GoString(res)
}
