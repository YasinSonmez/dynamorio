/* **********************************************************
 * Copyright (c) 2022 Google, Inc.  All rights reserved.
 * **********************************************************/

/*
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * * Redistributions of source code must retain the above copyright notice,
 *   this list of conditions and the following disclaimer.
 *
 * * Redistributions in binary form must reproduce the above copyright notice,
 *   this list of conditions and the following disclaimer in the documentation
 *   and/or other materials provided with the distribution.
 *
 * * Neither the name of Google, Inc. nor the names of its contributors may be
 *   used to endorse or promote products derived from this software without
 *   specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL VMWARE, INC. OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH
 * DAMAGE.
 */

/* kernel_image.h: header of module for dump kernel code segments to one file.
 */

#ifndef _KCORE_H_
#define _KCORE_H_ 1

struct proc_module_t;
struct proc_kcore_code_segment_t;

/* This class is used to dump kernel code segments to one file.
 */
class kernel_image_t {
public:
    kernel_image_t();
    ~kernel_image_t();

    /* Parse the kernel code segments from /proc/kcore.
     * This function will first read modules from /proc/modules, then read all kernel
     * symbols from /proc/kallsyms. Then it will parse the kernel code segments from
     * /proc/kcore.
     */
    bool
    init();

    /* Dump the kernel code segments to one file.
     * This function will dump all kernel code segments to one file called kimage and dump
     * the metadata of every code segment to kimage.metadata.
     */
    bool
    dump(const char *to_dir);

private:
    /* Read the module information to module list from /proc/modules.
     */
    bool
    read_modules();

    /* Parse the kernel module information from /proc/kallsyms and insert them to the
     * start ofmodule list.
     */
    bool
    read_kallsyms();

    /* Read the kernel code segments from /proc/kcore.
     */
    bool
    read_kcore();

    /* The module list. */
    proc_module_t *modules_;

    /* The kernel code segment list. */
    proc_kcore_code_segment_t *kcore_code_segments_;
};

#endif /* _KCORE_H_ */