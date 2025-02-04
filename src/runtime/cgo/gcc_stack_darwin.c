// Copyright 2023 The Go Authors. All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

#include <pthread.h>
#include "libcgo.h"

void
x_cgo_getstackbound(G *g)
{
	void* addr;
	size_t size;
	pthread_t p;

	p = pthread_self();
	addr = pthread_get_stackaddr_np(p); // high address (!)
	size = pthread_get_stacksize_np(p);
	g->stacklo = (uintptr)addr - size;
	// NOTE: don't change g->stackhi. We are called from asmcgocall
	// which saves the stack depth based on g->stackhi.
}
