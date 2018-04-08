/*
 * Copyright (c) 2016 Apple Computer, Inc. All rights reserved.
 *
 * @APPLE_OSREFERENCE_LICENSE_HEADER_START@
 *
 * This file contains Original Code and/or Modifications of Original Code
 * as defined in and that are subject to the Apple Public Source License
 * Version 2.0 (the 'License'). You may not use this file except in
 * compliance with the License. The rights granted to you under the License
 * may not be used to create, or enable the creation or redistribution of,
 * unlawful or unlicensed copies of an Apple operating system, or to
 * circumvent, violate, or enable the circumvention or violation of, any
 * terms of an Apple operating system software license agreement.
 *
 * Please obtain a copy of the License at
 * http://www.opensource.apple.com/apsl/ and read it before using this file.
 *
 * The Original Code and all software distributed under the License are
 * distributed on an 'AS IS' basis, WITHOUT WARRANTY OF ANY KIND, EITHER
 * EXPRESS OR IMPLIED, AND APPLE HEREBY DISCLAIMS ALL SUCH WARRANTIES,
 * INCLUDING WITHOUT LIMITATION, ANY WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE, QUIET ENJOYMENT OR NON-INFRINGEMENT.
 * Please see the License for the specific language governing rights and
 * limitations under the License.
 *
 * @APPLE_OSREFERENCE_LICENSE_HEADER_END@
 */

#ifndef KPERF_ACTION_H
#define KPERF_ACTION_H

#include <mach/kern_return.h>

/* fwd decl */
struct kperf_sample;
struct kperf_context;

/* bits for defining what to do on an action */
#define SAMPLER_TH_INFO       (1U << 0)
#define SAMPLER_TH_SNAPSHOT   (1U << 1)
#define SAMPLER_KSTACK        (1U << 2)
#define SAMPLER_USTACK        (1U << 3)
#define SAMPLER_PMC_THREAD    (1U << 4)
#define SAMPLER_PMC_CPU       (1U << 5)
#define SAMPLER_PMC_CONFIG    (1U << 6)
#define SAMPLER_MEMINFO       (1U << 7)
#define SAMPLER_TH_SCHEDULING (1U << 8)
#define SAMPLER_TH_DISPATCH   (1U << 9)
#define SAMPLER_TK_SNAPSHOT   (1U << 10)

/* flags for sample calls */

/* pend certain samplers until AST boundary, instead of sampling them */
#define SAMPLE_FLAG_PEND_USER       (1U << 0)
/* sample idle threads */
#define SAMPLE_FLAG_IDLE_THREADS    (1U << 1)
/* do not sample callstacks */
#define SAMPLE_FLAG_EMPTY_CALLSTACK (1U << 2)
/* use the continuation as a kernel backtrace */
#define SAMPLE_FLAG_CONTINUATION    (1U << 3)
/* sample is occurring outside of interrupt context */
#define SAMPLE_FLAG_NON_INTERRUPT   (1U << 4)

/*  Take a sample into "sbuf" using current thread "cur_thread" */
kern_return_t kperf_sample(struct kperf_sample *sbuf,
                           struct kperf_context *ctx,
                           unsigned actionid,
                           unsigned sample_flags);

/* return codes from taking a sample
 * either keep trigger, or something went wrong (or we're shutting down)
 * so turn off.
 */
#define SAMPLE_CONTINUE (0)
#define SAMPLE_SHUTDOWN (1)
#define SAMPLE_OFF      (2)

void kperf_action_reset(void);

/* Interface functions  */
unsigned kperf_action_get_count(void);
int kperf_action_set_count(unsigned count);

int kperf_action_set_samplers(unsigned int actionid, uint32_t samplers);
int kperf_action_get_samplers(unsigned int actionid, uint32_t *samplers_out);

int kperf_action_set_userdata(unsigned int actionid, uint32_t userdata);
int kperf_action_get_userdata(unsigned int actionid, uint32_t *userdata_out);

int kperf_action_set_ucallstack_depth(unsigned int actionid, uint32_t depth);
int kperf_action_get_ucallstack_depth(unsigned int actionid, uint32_t * depth_out);
int kperf_action_set_kcallstack_depth(unsigned int actionid, uint32_t depth);
int kperf_action_get_kcallstack_depth(unsigned int actionid, uint32_t * depth_out);

int kperf_action_set_filter(unsigned int actionid, int pid);
int kperf_action_get_filter(unsigned int actionid, int *pid_out);

#endif /* !defined(KPERF_ACTION_H) */
