# gdefaults

gdefaults is a module which allows you to enumerate the `defaults` on macOS. This is right now WIP.

Features covered so far:

* Getting the list of domains
* Reading all keys for specific domain
* Reading specific key for specific domain

```go
package main

import (
	"fmt"
	"github.com/nsecho/gdefaults"
)

func main() {
	// Get all domains
	domains := gdefaults.Domains()

	// Enumerate over all domains and print their keys
	for _, dom := range domains {
		fmt.Printf("%s => %s\n", dom, gdefaults.Read(dom, ""))
	}
}

```

This project is based around [defaults](https://github.com/ProcursusTeam/defaults) from ProcursusTeam.