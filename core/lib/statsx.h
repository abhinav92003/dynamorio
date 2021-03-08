/* **********************************************************
 * Copyright (c) 2011-2021 Google, Inc.  All rights reserved.
 * Copyright (c) 2003-2010 VMware, Inc.  All rights reserved.
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
 * * Neither the name of VMware, Inc. nor the names of its contributors may be
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

/* Copyright (c) 2003-2007 Determina Corp. */

/*
 * statsx.h
 *
 * Statistics definitions and descriptions
 *
 */

/* This file is included multiple times
   - in dynamorio_stats.h once for structure definition,
   - in utils.c - dump_global_stats, dump_thread_stats
   - TODO: should also be included in the GUI
*/

/* Client files that include this header should define the following macros:
#ifdef DEBUG
# define STATS_DEF(description, name) // def here
#else
# define RSTATS_DEF(description, name) // def here
#endif
#undef STATS_DEF
#undef RSTATS_DEF

RSTATS_DEF should start the description with Current for stats to not print
under -rstats_to_stderr.
*/

/* Add new statistics at the end so that older GUIs can still show old statistics */
/* Try to avoid preprocessor directives in STATS -
   shouldn't matter, and makes old GUIs compatible */
/* Keep descriptions up to a reasonable length (column 62 max -- else will hit
 * a warning in gcc 4.1.2-2) */

/* use RSTATS_DEF for statistics that are available in release build as well
 * as debug (you must use RSTATS_INC, etc. as well with such stats)
 */
#if defined(DEBUG) && !defined(RSTATS_ONLY)
#    define RSTATS_DEF STATS_DEF
#else
#    define STATS_DEF(desc, name) /* nothing */
#endif

STATS_DEF("Application exited", exited)
RSTATS_DEF("Current threads under DynamoRIO control", num_threads)
RSTATS_DEF("Peak threads under DynamoRIO control", peak_num_threads)
RSTATS_DEF("Threads ever created", num_threads_created)
STATS_DEF("Threads killed", num_threads_killed)
STATS_DEF("Threads killed cleanly", num_threads_killed_cleanly)
#ifdef WINDOWS
RSTATS_DEF("Callbacks", num_callbacks)
STATS_DEF("Callbacks in no-asynch threads", num_callbacks_noasynch)
RSTATS_DEF("APCs", num_APCs)
STATS_DEF("APCs in no-asynch threads", num_APCs_noasynch)
RSTATS_DEF("Exceptions", num_exceptions)
STATS_DEF("Exceptions in no-asynch threads", num_exceptions_noasynch)
STATS_DEF("KiRaiseUserException instances", num_raise_exceptions)
STATS_DEF("KiRaiseUserException in no-asynch threads", num_raise_exceptions_noasynch)
STATS_DEF("Asynch event while lost control", num_asynch_while_lost)
STATS_DEF("Exceptions while lost control", num_except_while_lost)
STATS_DEF("Exceptions at SetContext points for reset", num_reset_setcontext_at_fault)
STATS_DEF("Exceptions at SetContext points for app", num_app_setcontext_at_fault)
STATS_DEF("GetContextThread w/o CONTEXT_CONTROL", num_app_getcontext_no_control)
STATS_DEF("SetContextThread w/o CONTEXT_CONTROL", num_app_setcontext_no_control)
STATS_DEF("Re-takeovers after native", num_retakeover_after_native)
#else
RSTATS_DEF("Total signals delivered", num_signals)
RSTATS_DEF("Total signals delivered to native threads", num_native_signals)
RSTATS_DEF("Signals dropped", num_signals_dropped)
RSTATS_DEF("Signals in coarse units delayed", num_signals_coarse_delayed)
#endif
STATS_DEF("Exceptions in decoding app memory", num_exceptions_decode)
RSTATS_DEF("System calls, pre", pre_syscall)
RSTATS_DEF("System calls, post", post_syscall)
STATS_DEF("System calls, pre, ignorable", pre_syscall_ignorable)
STATS_DEF("System calls, post, ignorable", post_syscall_ignorable)
STATS_DEF("Ignorable system calls", ignorable_syscalls)
#ifdef WINDOWS
STATS_DEF("Ignorable system calls not matching sysenter pattern",
          ignorable_syscalls_failed_sysenter_pattern)
#endif
STATS_DEF("Optimizable system calls", optimizable_syscalls)
STATS_DEF("Non-ignorable system calls", non_ignorable_syscalls)
#ifdef WINDOWS
STATS_DEF("Instances of interrupt 2B", num_int2b)
#endif
#ifdef VMX86_SERVER
STATS_DEF("VMKUW system call sites", vmkuw_syscall_sites)
STATS_DEF("VMKUW non-ignorable system calls", vmkuw_syscalls_intercept)
#endif
RSTATS_DEF("Native modules present", num_native_module_loads)
STATS_DEF("Native module entrance checks", num_native_entrance_checks)
STATS_DEF("Native module entrance TOS checks", num_native_entrance_TOS_checks)
STATS_DEF("Native module entrance TOS decodes", num_native_entrance_TOS_decodes)
STATS_DEF("Native module entrance potential misses", num_native_entrance_miss)
STATS_DEF("Native module entrance blocks", num_native_module_entrances)
STATS_DEF("Native module entrance blocks, call", num_native_module_entrances_call)
STATS_DEF("Native module entrance blocks, call*", num_native_module_entrances_indcall)
STATS_DEF("Native module entrance blocks, call+jmp*", num_native_module_entrances_plt)
STATS_DEF("Native module entrance blocks, TOS unknown",
          num_native_module_entrances_TOS_unknown)
STATS_DEF("Native module entrance blocks, TOS jmp*", num_native_module_entrances_TOS_jmp)
STATS_DEF("Native module entrance blocks, call* jmp/call",
          num_native_module_entrances_callcall)
STATS_DEF("Native module entrance blocks, ret", num_native_module_entrances_ret)
STATS_DEF("Native module execution entrances", num_native_module_enter)
STATS_DEF("Native module execution exits", num_native_module_exit)
STATS_DEF("Native our-fault write faults", num_native_cachecons_faults)
STATS_DEF("System call trampolines, total", num_syscall_trampolines)
STATS_DEF("System call trampolines, native", num_syscall_trampolines_native)
STATS_DEF("System call trampolines, cache", num_syscall_trampolines_cache)
STATS_DEF("System call trampolines, DR", num_syscall_trampolines_DR)
STATS_DEF("System call trampolines, retakeover", num_syscall_trampolines_retakeover)
RSTATS_DEF("Application mmaps", num_app_mmaps)
RSTATS_DEF("Application munmaps", num_app_munmaps)
STATS_DEF("Module rebindings", num_app_rebinds)
#ifdef WINDOWS
STATS_DEF("Application map mismatches with sections", map_section_mismatch)
STATS_DEF("Application map file unknown Dos name", map_unknown_Dos_name)
#endif
STATS_DEF("Application modules with long names", app_modname_too_long)
STATS_DEF("Application modules with code", num_app_code_modules)
STATS_DEF("Application code seen (bytes)", app_code_seen)
STATS_DEF("Interpreted calls, direct and indirect", num_all_calls)
STATS_DEF("Interpreted indirect calls", num_indirect_calls)
STATS_DEF("Interpreted convertible indirect calls", num_convertible_indcalls)
STATS_DEF("Interpreted to-sysenter indirect calls", num_sysenter_indcalls)
STATS_DEF("Interpreted indirect jmps", num_indirect_jumps)
STATS_DEF("Interpreted rets", num_returns)
STATS_DEF("Interpreted far direct calls", num_far_dir_calls)
STATS_DEF("Interpreted far direct jmps", num_far_dir_jmps)
STATS_DEF("Interpreted far indirect calls", num_far_ind_calls)
STATS_DEF("Interpreted far indirect jmps", num_far_ind_jmps)
STATS_DEF("Interpreted far rets", num_far_rets)
STATS_DEF("Interpreted irets", num_irets)
STATS_DEF("Decoded jcc branch hints", num_branch_hints)

STATS_DEF("Dynamic option synchronizations", option_synchronizations)
STATS_DEF("Dynamic option synchronizations, no change", option_synchronizations_nop)
STATS_DEF("Security violations, heap", num_heap_violations)
STATS_DEF("Security violations, stack", num_stack_violations)
#ifdef WINDOWS
STATS_DEF("Exempted regions, NtFlush, +w", num_NT_flush_w)
STATS_DEF("Exempted regions, NtFlush, -w", num_NT_flush_r)
STATS_DEF("Exempted regions, NtFlush, +w & on exec list", num_NT_flush_w2r)
STATS_DEF("Non-exempt regions b/c NtFlush was by loader", num_NT_flush_loader)
STATS_DEF("Exempted regions, NtFlush, heap", num_NT_flush_heap)
STATS_DEF("Exempted regions, NtFlush, stack", num_NT_flush_stack)
STATS_DEF("Exempted regions, loader-marked", num_mark_after_load)
#endif
STATS_DEF("Exempted regions, ->rx text", num_2rx_text)
STATS_DEF("Exempted regions, any text", num_text)
STATS_DEF("Exempted regions, rwx text", num_hook)
STATS_DEF("Non-exempted regions, rwx text, native module", num_hook_native_ignored)
STATS_DEF("Exempted regions, on text list", num_text_list)
STATS_DEF("Exempted regions, on IMAGE text list", num_image_text_list)
STATS_DEF("Exempted regions, .data section", num_dot_data)
STATS_DEF("Exempted regions, on .data section list", num_dot_data_list)
STATS_DEF("Exempted regions, .data x section", num_dot_data_x)
STATS_DEF("Exempted regions, on .data x section list", num_dot_data_x_list)
STATS_DEF("Exempted regions, ..x", num_mark_if_x)
STATS_DEF("Exempted regions, .-x", num_mark_if_rx)
STATS_DEF("Exempted regions, executable or library image", num_exempt_image)
STATS_DEF("Exempted regions, executable or library list", num_exempt_image_list)
STATS_DEF("Exempted regions, on moduledb exempt image list", num_moduledb_exempt_image)
STATS_DEF("Exempted threats", num_exempt_threat)
STATS_DEF("Silently blocked threats", num_silently_blocked_threat)
STATS_DEF("Exempted regions from dll2heap", num_exempt_dll2heap)
STATS_DEF("Exempted regions from moduledb exempt dll2heap", num_moduledb_exempt_dll2heap)
STATS_DEF("Exempted regions from dll2stack", num_exempt_dll2stack)
STATS_DEF("Exempted regions from moduledb exempt dll2stack",
          num_moduledb_exempt_dll2stack)
STATS_DEF("Exempted regions, alloc", num_alloc_exec)
STATS_DEF("Exempted future executions, heap", num_exec_future_heap)
STATS_DEF("Exempted future executions, stack", num_exec_future_stack)
STATS_DEF("Exempted future executions, once-only", num_exec_future_once)
#ifdef WINDOWS
STATS_DEF("Exempted loader-marked executions", num_exec_after_load)
#endif
STATS_DEF("Exempted trampoline executions, heap", num_trampolines_heap)
STATS_DEF("Exempted trampoline executions, stack", num_trampolines_stack)
STATS_DEF("Exempted trampoline direct calls", trampolines_direct_calls)
STATS_DEF("Exempted trampoline direct jmps", trampolines_direct_jmps)
STATS_DEF("Exempted .NET COM method table returns", trampolines_com_rets)
STATS_DEF("Exempted displaced hook code", trampolines_displaced_code)
STATS_DEF("Exempted assumed driver address", num_driver_areas)

STATS_DEF("Code origin addresses checked", checked_addresses)
STATS_DEF("Code origin addresses in last area", looked_up_in_last_area)

STATS_DEF("Writable code regions", num_writable_code_regions)
STATS_DEF("Writable code regions we made read-only", num_rw2r_code_regions)
STATS_DEF("Writable executable regions we made read-only", num_delayed_rw2r)
STATS_DEF("Memory regions marked as sandboxed", num_selfmod_vm_areas)
STATS_DEF("Code regions not switched due to other sub-page", num_ro2sandbox_other_sub)
STATS_DEF("Code regions switched read-only to sandbox", num_ro2sandbox)
STATS_DEF("Code regions sandboxed before being read-only", num_sandbox_before_ro)
STATS_DEF("Code regions switched sandbox to read-only", num_sandbox2ro)
STATS_DEF("Code regions race in sandbox2ro attempt", num_sandbox2ro_race)
STATS_DEF("Code regions flush race in sandbox2ro attempt", num_sandbox2ro_flush_race)
STATS_DEF("Code regions on stack with sandbox counters", num_sandbox2ro_onstack)
STATS_DEF("Sandboxed fragments", num_sandboxed_fragments)
STATS_DEF("Sandboxed fragment executions", num_sandbox_execs)
STATS_DEF("Blocks ended early due to sandboxing limitations", num_bb_end_early)
STATS_DEF("Self-writes detected by sandboxing", num_self_writes)
STATS_DEF("Self-writes overruled by flushes", num_self_writes_after_flushes)
STATS_DEF("Write faults on read-only code regions", num_write_faults)
STATS_DEF("Write fault races", num_write_fault_races)
STATS_DEF("Write fault races, one selfmod", num_write_fault_races_selfmod)
STATS_DEF("Flushes racy, no exec removal since selfmod", flush_selfmod_race_no_remove)
STATS_DEF("Cache consistency flushes", num_flushes)
STATS_DEF("Cache consistency flushes that flushed nothing", num_empty_flushes)
STATS_DEF("Cache consistency flushes via synchall", flush_synchall)
STATS_DEF("Thread not translated in synchall flush (race)", flush_synchall_races)
STATS_DEF("Thread not synched with in synchall flush", flush_synchall_fail)
RSTATS_DEF("Synch attempt failure b/c not at safe spot", synchs_not_at_safe_spot)
STATS_DEF("Cache consistency coarse units flushed", flush_coarse_units)
STATS_DEF("Cache consistency persisted units flushed", flush_persisted_units)
STATS_DEF("Cache consistency persisted flushed at unload", flush_persisted_unload)
STATS_DEF("Pending-delete fragments re-deleted", deleted_frags_re_deleted)
STATS_DEF("Cache consistency non-code nop flushes", num_noncode_flushes)
STATS_DEF("Flushes that flushed >=1 shared fragment", num_shared_flushes)
STATS_DEF("Flushes of entire cache", fcache_flush_all)
STATS_DEF("Fcache units flushed", cache_units_flushed)
STATS_DEF("Fcache units flushed and freed", cache_units_flushed_freed)
STATS_DEF("Fcache units on to-flush list", cache_units_toflush)
STATS_DEF("Peak fcache units on to-flush list", peak_cache_units_toflush)
STATS_DEF("Fcache units on to-free list", cache_units_tofree)
STATS_DEF("Peak fcache units on to-free list", peak_cache_units_tofree)
STATS_DEF("Fcache units flushed for wset", cache_units_wset_flushed)
STATS_DEF("Fcache units allowed w/o a flush for wset", cache_units_wset_allowed)
STATS_DEF("Fcache units flushed w/ no live fragments", cache_units_flushed_nolive)
STATS_DEF("Flushes of vmvector areas", num_flush_vmvector)
STATS_DEF("Shared deletion regions unlinked", num_shared_flush_regions)
STATS_DEF("Shared deletion region walks", num_shared_flush_walks)
STATS_DEF("Shared deletion region at-syscall walks", num_shared_flush_atsyscall)
STATS_DEF("Shared deletion ref count decrements", num_shared_flush_refdec)
STATS_DEF("Shared deletion flushtime diff > #threads", num_shared_flush_diffthreads)
STATS_DEF("Shared deletion max flushtime diff", num_shared_flush_maxdiff)
STATS_DEF("Shared deletion max pending", num_shared_flush_maxpending)
STATS_DEF("Shared deletion region removals: ref 0", num_shared_flush_refzero)
STATS_DEF("Shared deletion region removals: at exit", num_shared_flush_atexit)
STATS_DEF("Shared deletion region removals: at reset", num_shared_flush_atreset)
STATS_DEF("Shared deletion: shared IBT tables unlinked", num_shared_ibt_table_unlinks)
STATS_DEF("Shared deletion: empty shared IBT tables skipped",
          num_shared_empty_ibt_tables_skipped)
STATS_DEF("Shared deletion: shared IBTs unlinked", num_shared_ibt_unlinks)
STATS_DEF("Shared deletion: shared IBT entries skipped", num_shared_ibt_entries_skipped)
STATS_DEF("Shared deletion: shared IBT entries examined", num_shared_ibt_entries_examined)
STATS_DEF("Flush queue nonempty: relink shared_sys", num_flushq_relink_syscall)
STATS_DEF("Flush queue nonempty: relink special ibl xfer",
          num_flushq_relink_special_ibl_xfer)
STATS_DEF("Flush queue marked nonempty, yet empty", num_flushq_actually_empty)
STATS_DEF("Fragments added to lazy deletion list", num_lazy_deletion_appends)
STATS_DEF("Fragments freed from lazy deletion list at exit",
          num_lazy_deletion_frees_atexit)
STATS_DEF("Fragments freed from lazy deletion list", num_lazy_deletion_frees)
STATS_DEF("Lazy list instances moved to pending list", num_lazy_del_to_pending)
STATS_DEF("Lazy list fragments moved to pending list", num_lazy_del_frags_to_pending)
STATS_DEF("Translation info computed", translations_computed)
STATS_DEF("Fragments with translation info stored", num_fragment_translation_stored)
STATS_DEF("Resets of entire fcache, proactively", fcache_reset_proactively)
STATS_DEF("Resets due to too many pending deletions", fcache_reset_pending_del)
STATS_DEF("Resets aborted due to thread synch problems", fcache_reset_abort)
STATS_DEF("Resets due to running low on vmm_heap", reset_low_vmm_count)
STATS_DEF("Resets due to running low on committable memory", reset_low_commit_count)
STATS_DEF("Number of queries of the commit limit", commit_limit_queries)
STATS_DEF("Data section protection changes", datasec_prot_changes)
STATS_DEF("Data section protection wasted calls", datasec_prot_wasted_calls)
STATS_DEF("Data section checks: unprotected (racy)", datasec_not_prot)
STATS_DEF("Generated code protection changes", gencode_prot_changes)
STATS_DEF("Protection change calls", protection_change_calls)
STATS_DEF("Protection change pages", protection_change_pages)
STATS_DEF("Unload race detected", num_unloaded_race)
STATS_DEF("Unload race prevented spurious .B", num_unloaded_race_code_origins)

#ifdef RETURN_AFTER_CALL
STATS_DEF("After call instructions, total added", ret_after_call_added)
STATS_DEF("After call instructions, existing", num_existing_after_call)
STATS_DEF("After call instructions, current", num_future_after_call)
STATS_DEF("After call instructions, removed", num_future_after_call_removed)
STATS_DEF("RAC persisted tables created", rac_persisted_tables)
STATS_DEF("RAC persisted table entries", rac_persisted_entries)
STATS_DEF("RAC live tables created", rac_live_tables)
STATS_DEF("RAC live table entries", rac_live_entries)
STATS_DEF("RAC non-module table entries", rac_non_module_entries)
STATS_DEF("Return after call total validations", ret_after_call_validations)
STATS_DEF("Return after call good returns", ret_after_call_good)
STATS_DEF("Return after call, before start ok", ret_after_call_before_start)
STATS_DEF("Return after call, signal restorers ok", ret_after_call_signal_restorer)
STATS_DEF("Return after call, known exceptions ok", ret_after_call_known_exceptions)
STATS_DEF("Return after call, SEH exemptions ok", ret_after_call_SEH)
STATS_DEF("Return after call, push reg; ret", ret_after_call_pushregret)
STATS_DEF("Return after call, .xdata call* target", ret_after_call_xdata)
STATS_DEF("Return after call, known exempt exceptions ok",
          ret_after_call_exempt_exceptions)
STATS_DEF("Return after call, prevented spurious unload .C", num_unloaded_race_during)
STATS_DEF("Return after call, after unload, silenced .C", num_unloaded_race_after)
STATS_DEF("RCT, moduledb exemptions ok", num_rct_moduledb_exempt)
STATS_DEF("RCT, driver address ok", num_rct_driver_address)
STATS_DEF("Return after call, exempt locations, added", ret_after_call_exempt_added)
STATS_DEF("Return after call violations, BAD", ret_after_call_violations)
#endif /* RETURN_AFTER_CALL */
#ifdef RCT_IND_BRANCH
STATS_DEF("RCT persisted tables created", rct_persisted_tables)
STATS_DEF("RCT persisted table entries", rct_persisted_entries)
STATS_DEF("RCT live tables created", rct_live_tables)
STATS_DEF("RCT live table entries", rct_live_entries)
STATS_DEF("RCT indirect branch targets, total", rct_ind_branch_valid_targets)
STATS_DEF("RCT indirect branch target entries, current", rct_ind_branch_entries)
STATS_DEF("RCT indirect branch target entries, removed", rct_ind_branch_entries_removed)
STATS_DEF("RCT indirect branch targets existing", rct_ind_branch_existing_targets)
STATS_DEF("RCT indirect branch modules added", rct_ind_branch_modules_analyzed)
STATS_DEF("RCT indirect branch sections added", rct_ind_branch_sections_analyzed)
STATS_DEF("RCT indirect branch not code section", rct_ind_branch_not_code_section)
STATS_DEF("RCT modules loaded from persisted data", rct_ind_branch_modules_persist_loaded)
STATS_DEF("RCT modules with partial persisted data",
          rct_ind_branch_modules_persist_partial)
STATS_DEF("RCT indirect branch unload race", rct_ind_branch_unload_race)
STATS_DEF("RCT indirect branch ref outside module", rct_ind_branch_ref_outside_module)
STATS_DEF("RCT indirect branch reloc sec w/o valid targets",
          rct_ind_branch_no_valid_targets)
STATS_DEF("RCT indirect branch exports added", rct_ind_added_exports)
STATS_DEF("RCT indirect branch exports already added", rct_ind_already_added_exports)
STATS_DEF("RCT indirect branch ok after analyze-at-vio", rct_ok_at_vio)
STATS_DEF("RCT indirect branch modules scanned at init", rct_scan_at_init)
STATS_DEF("RCT indirect branch modules scanned at violation", rct_scan_at_vio)
STATS_DEF("RCT indirect branch rip-rel new targets added", rct_ind_rip_rel_new)
STATS_DEF("RCT indirect branch rip-rel tgts already added", rct_ind_rip_rel_old)
STATS_DEF("RCT indirect branch rip-rel scan added", rct_ind_rip_rel_scan_new)
STATS_DEF("RCT indirect branch rip-rel scan already added", rct_ind_rip_rel_scan_old)
STATS_DEF("RCT indirect branch rip-rel scan out of range", rct_ind_rip_rel_scan_data)
STATS_DEF("RCT indirect branch SEH64 new targets added", rct_ind_seh64_new)
STATS_DEF("RCT indirect branch SEH64 targets already added", rct_ind_seh64_old)
STATS_DEF("RCT indirect branch SEH64 plus-1 entries", rct_ind_seh64_plus1)
STATS_DEF("RCT indirect branch total validations", rct_ind_branch_validations)
STATS_DEF("RCT indirect call good", rct_ind_call_good)
STATS_DEF("RCT indirect jmp good", rct_ind_jmp_good)
STATS_DEF("RCT indirect call exports", rct_ind_call_exports)
STATS_DEF("RCT indirect jmp exports", rct_ind_jmp_exports)
STATS_DEF("RCT indirect jmp instead of ret to after call", rct_ind_jmp_allowed_to_ac)
STATS_DEF("RCT indirect call exemptions", rct_ind_call_exemptions)
STATS_DEF("RCT indirect jmp exemptions", rct_ind_jmp_exemptions)
STATS_DEF("RCT indirect jmp x64-switch exemptions", rct_ind_jmp_x64switch)

STATS_DEF("RCT indirect call violations, BAD", rct_ind_call_violations)
STATS_DEF("RCT indirect jmp violations, BAD", rct_ind_jmp_violations)
#endif /* RCT_IND_BRANCH */
STATS_DEF("App protection changes of DR memory", app_modify_DR_prot)
STATS_DEF("App protection changes of ntdll code", app_modify_ntdll_prot)
STATS_DEF("App protection changes of patch proof module", app_modify_module_prot)
STATS_DEF("App loads of patch proof modules", num_patch_proof_module_loads)
STATS_DEF("App writes to pretend-writable DR memory", app_modify_DR_writes)
STATS_DEF("App writes to pretend-writable ntdll memory", app_modify_ntdll_writes)
STATS_DEF("App writes to pretend-writable module memory", app_modify_patch_module_writes)
STATS_DEF("App writes emulated successfully", num_emulated_writes)
STATS_DEF("App writes emulated un-successfully", num_emulated_write_failures)

STATS_DEF("Fragments generated, bb and trace", num_fragments)
RSTATS_DEF("Basic block fragments generated", num_bbs)
RSTATS_DEF("Trace fragments generated", num_traces)
#ifdef X64
STATS_DEF("32-bit basic block fragments generated", num_32bit_bbs)
STATS_DEF("32-bit trace fragments generated", num_32bit_traces)
STATS_DEF("32-bit instructions translated to 64-bit", num_32bit_instrs_translated)
#endif
STATS_DEF("Trace fragments aborted for any reason", num_aborted_traces)
STATS_DEF("Trace fragments aborted: shared race", num_aborted_traces_race)
STATS_DEF("Trace fragments aborted: client bad mod", num_aborted_traces_client)
STATS_DEF("Trace building aborted: shared race", num_trace_building_race)
STATS_DEF("Trace building truncated: next bb deleted", num_trace_next_bb_deleted)
STATS_DEF("Trace building reset: no trace head", num_reset_trace_no_trace_head)
STATS_DEF("Trace building reset: in-progress flag cleared", num_trace_building_ip_cleared)
STATS_DEF("Number of bbs in all emitted traces", num_bbs_in_all_traces)
STATS_DEF("Number of bbs in all aborted traces", num_bbs_in_all_aborted_traces)
STATS_DEF("Maximum number of bbs in a trace", max_bbs_in_a_trace)
STATS_DEF("Traces truncated due to cache size limits", num_max_trace_size_enforced)
STATS_DEF("Number of times max_trace_bbs was enforced", num_max_trace_bbs_enforced)
STATS_DEF("Trace wannabes prevented from being traces", num_wannabe_traces)
STATS_DEF("Trace head too large to be a trace", num_huge_fragments)
STATS_DEF("Shared trace links shifted back to trace head", links_shared_trace_to_head)
STATS_DEF("Shadowed trace head deleted", shadowed_trace_head_deleted)
STATS_DEF("Trace head counters reset on trace deletion", th_counter_reset)
STATS_DEF("Trace heads re-marked", trace_head_remark)
STATS_DEF("Future fragments generated", num_future_fragments)
STATS_DEF("Shared fragments generated", num_shared_fragments)
STATS_DEF("Shared bbs generated", num_shared_bbs)
STATS_DEF("Shared traces generated", num_shared_traces)
STATS_DEF("Private fragments generated", num_private_fragments)
STATS_DEF("Private bbs generated", num_private_bbs)
STATS_DEF("Private traces generated", num_private_traces)
STATS_DEF("Shared future fragments generated", num_shared_future_fragments)
STATS_DEF("Unique fragments generated", num_unique_fragments)
STATS_DEF("Maximum fragment requested size in bytes", max_fragment_requested_size)
STATS_DEF("Maximum fragment size in bytes", max_fragment_size)
STATS_DEF("Maximum instrs in a bb", max_instrs_in_a_bb)
STATS_DEF("BBs truncated due to instr limits", num_max_bb_instrs_enforced)
STATS_DEF("BBs truncated due to selfmod write limits", num_max_selfmod_writes_enforced)
STATS_DEF("Maximum elided jmps in a bb", max_elided_jmps)
STATS_DEF("Maximum elided calls in a bb", max_elided_calls)
STATS_DEF("Total elided jmps in all bbs", total_elided_jmps)
STATS_DEF("Total elided calls in all bbs", total_elided_calls)
STATS_DEF("BB elisions prevented for coarse-grain", elisions_prevented_for_coarse)
STATS_DEF("Trace heads unlinked in IBTs", num_th_bb_ibt_unlinked)
STATS_DEF("Trace head IBT add race", num_th_bb_ibt_add_race)
STATS_DEF("Direct exit stubs created", num_direct_exit_stubs)
STATS_DEF("Indirect exit stubs created", num_indirect_exit_stubs)
STATS_DEF("Separate stubs created", num_separate_stubs)
STATS_DEF("Entrance stubs created", num_entrance_stubs)
#ifdef X64
STATS_DEF("Rip-relative instrs seen", rip_rel_instrs)
STATS_DEF("Rip-relative unreachable leas", rip_rel_lea)
STATS_DEF("Rip-relative unreachable leas in app", rip_rel_app_lea)
STATS_DEF("Rip-relative unreachable non-leas", rip_rel_unreachable)
STATS_DEF("Rip-relative unreachable non-leas in app", rip_rel_app_unreachable)
STATS_DEF("Rip-relative unreachable spills avoided", rip_rel_unreachable_nospill)
#endif
STATS_DEF("BBs with one indirect exit", num_bb_one_indirect_exit)
STATS_DEF("BBs with indirect exit + other exits", num_bb_indirect_extra_exits)
STATS_DEF("BBs with one direct exit", num_bb_one_direct_exit)
STATS_DEF("BBs with two direct exits", num_bb_two_direct_exits)
STATS_DEF("BBs with >2 direct exits", num_bb_many_direct_exits)
STATS_DEF("BBs with an elided cti", num_bb_has_elided)
STATS_DEF("BBs with an also_vmarea", num_bb_also_vmarea)
STATS_DEF("BB direct exits >SHRT_MAX from fragment tag", num_bb_exit_tgt_far)
STATS_DEF("BB direct exits <=SHRT_MAX from fragment tag", num_bb_exit_tgt_near)
STATS_DEF("BB cbr fall-through >SHRT_MAX from fragment tag", num_bb_fallthru_far)
STATS_DEF("BB cbr fall-through <=SHRT_MAX from fragment tag", num_bb_fallthru_near)
STATS_DEF("BBs using post-linkstub fragment offset", num_bb_fragment_offset)
STATS_DEF("BBs using cbr fall-through smaller linkstub", num_bb_cbr_fallthru_shrink)
STATS_DEF("BBs that write OF but no other arithmetic flags", bbs_eflags_writes_of)
STATS_DEF("BBs that write all 6 arithmetic flags", bbs_eflags_writes_6)
STATS_DEF("BBs that read a flag before writing any", bbs_eflags_reads)
STATS_DEF("BBs that write no arithmetic flags", bbs_eflags_writes_none)
STATS_DEF("BBs that write no arithmetic flags, end in ib", bbs_eflags_writes_none_ind)
STATS_DEF("Cbrs sharing a single exit stub", num_cbr_single_stub)
STATS_DEF("Far direct links", num_far_direct_links)
STATS_DEF("Fragments requiring post_linkstub offs", num_fragment_post_linkstub)
STATS_DEF("Fragments smaller than minimum fcache slot size", num_fragment_too_small)
STATS_DEF("Fragments final size < minimum fcache slot size", num_final_fragment_too_small)
STATS_DEF("Fragments unlinked for flushing", num_flushed_fragments)
STATS_DEF("Fragments deleted for any reason", num_fragments_deleted)
STATS_DEF("Fragments unlinked for deletion", fragments_unlinked_for_deletion)
STATS_DEF("Fragments unlinked for deletion from list", list_entries_unlinked_for_deletion)
STATS_DEF("Shared fragments deleted no-flush, race", shared_delete_noflush_race)
STATS_DEF("Trace component fragments deleted", trace_components_deleted)
STATS_DEF("Fragments deleted due to capacity conflicts", num_fragments_replaced)
STATS_DEF("Fragments deleted on thread/process death", num_fragments_deleted_exit)
STATS_DEF("Fragments deleted on thread/process reset", num_fragments_deleted_reset)
STATS_DEF("Trace heads marked", num_trace_heads_marked)
STATS_DEF("Fragments deleted and replaced with traces", num_fragments_deleted_trace_heads)
STATS_DEF("Fragments deleted after selfmod", num_fragments_deleted_selfmod)
STATS_DEF("Fragments deleted for munmap or RO consistency",
          num_fragments_deleted_consistency)
STATS_DEF("Fragments deleted for copy & replace", num_fragments_deleted_copy_and_replace)
#ifdef CLIENT_INTERFACE
STATS_DEF("Fragments deleted by client interface", num_fragments_deleted_client)
#endif
#ifdef SIDELINE
STATS_DEF("Fragments deleted by sideline replacement", num_fragments_deleted_sideline)
#endif
STATS_DEF("Trace fragments in 3 IBL tables", num_traces_in_3_ibl_tables)
STATS_DEF("Trace fragments in 2 IBL tables", num_traces_in_2_ibl_tables)
STATS_DEF("Trace fragments in 1 IBL tables", num_traces_in_1_ibl_tables)
STATS_DEF("Trace fragments targeted by IBL", num_traces_ibl_targets)
STATS_DEF("IBTs replaced previous fragments", num_ibt_replace_previous_fragments)
STATS_DEF("IBTs replaced unlinked fragments", num_ibt_replace_unlinked_fragments)
STATS_DEF("IBT linked/unlinked table rehashes", num_ibt_table_rehashes)
STATS_DEF("IBT resizes", num_ibt_table_resizes)
STATS_DEF("Same-size IBT table resizes", num_same_size_ibt_table_resizes)
STATS_DEF("Shared IBT table flushes", num_shared_ibt_table_flushes)
STATS_DEF("Shared IBT table ptr resets", num_shared_ibt_table_ptr_resets)
STATS_DEF("IBT adds disallowed shared table, private frag",
          num_ibt_shared_private_conflict)
STATS_DEF("Dead shared IBT tables", num_dead_shared_ibt_tables)
STATS_DEF("Peak # dead shared IBT tables", peak_num_dead_shared_ibt_tables)
STATS_DEF("Total dead shared IBT tables", num_total_dead_shared_ibt_tables)
STATS_DEF("Dead shared IBT tables freed", num_dead_shared_ibt_tables_freed)
STATS_DEF("Dead shared IBT tables freed: at exit",
          num_dead_shared_ibt_tables_freed_at_exit)
STATS_DEF("Shared IBT tables freed: immediately", num_shared_ibt_tables_freed_immediately)
STATS_DEF("Pvt ptrs to shared tables updated at-sys walks",
          num_shared_tables_updated_atsyscall)
STATS_DEF("Pvt ptrs to shared tables updated at delete exits",
          num_shared_tables_updated_delete)
STATS_DEF("IBT unlinked entries NOT moved on resize", num_ibt_unlinked_entries_not_moved)
STATS_DEF("BB fragments in 3 IBL tables", num_bbs_in_3_ibl_tables)
STATS_DEF("BB fragments in 2 IBL tables", num_bbs_in_2_ibl_tables)
STATS_DEF("BB fragments in 1 IBL tables", num_bbs_in_1_ibl_tables)
STATS_DEF("BB fragments targeted by IBL", num_bbs_ibl_targets)
STATS_DEF("Exits due to IBL cold misses", num_ibt_cold_misses)
STATS_DEF("Exits due to IB targeting TH", num_ib_th_target)
STATS_DEF("Exits preventable if IB targeted bbs", num_ibt_bb_preventable)
STATS_DEF("Extra exits due to trace building", num_ibt_exit_trace_building)
STATS_DEF("Extra exits due to IBL sentinel leaks, BAD", num_ibt_leaks_likely_sentinel)
STATS_DEF("Extra exits due to selfmod exits", num_ibt_exit_src_sandboxed)
STATS_DEF("Extra exits due to shared table resizing", num_ibt_exit_shared_table_resize)
STATS_DEF("Extra exits due to src unlinked (frag deleted)",
          num_ibt_exit_src_unlinked_frag_deleted)
STATS_DEF("Extra exits due to src unlinked (shadowed)",
          num_ibt_exit_src_unlinked_shadowed)
STATS_DEF("Extra exits due to src unlinked (signal)", num_ibt_exit_src_unlinked_signal)
STATS_DEF("Extra exits due to shared syscall targetting BB",
          num_ibt_exit_src_trace_shared_syscall)
STATS_DEF("Extra IBT exits due to -no_link_ibl", num_ibt_exit_nolink)
STATS_DEF("Extra IBT exits due to unknown reasons", num_ibt_exit_unknown)
STATS_DEF("Fragments regenerated, in-cache replacement", num_fragments_regenerated)
STATS_DEF("Fragments regenerated or duplicated", num_fragments_deja_vu)
STATS_DEF("Trace fragments extended", num_traces_extended)
STATS_DEF("Trace building private copies created", num_trace_private_copies)
STATS_DEF("Trace building private copies deleted", num_trace_private_deletions)
STATS_DEF("Trace building private copies flushed b4 deleted",
          num_trace_private_deletions_flushed)
STATS_DEF("Trace building private copies aborting traces", num_trace_private_copy_abort)
STATS_DEF("Trace building private copies futures deleted", num_trace_private_fut_del)
STATS_DEF("Trace building private copies futures avoided", num_trace_private_fut_avoid)
STATS_DEF("Trace inline-ib comparisons", trace_ib_cmp)
#ifdef X64
STATS_DEF("Trace inline-ib no eflag restore needed", trace_ib_no_flag_restore)
#endif
STATS_DEF("Trace fragments extended, ibl exits updated", num_traces_ibl_extended)
#ifdef WINDOWS
STATS_DEF("Trace fragments extended w/shared syscall block",
          num_traces_shared_syscall_extended)
#endif
#ifdef CUSTOM_TRACES
STATS_DEF("Custom traces extended beyond normal stop", custom_traces_stop_late)
STATS_DEF("Custom traces stopped early", custom_traces_stop_early)
STATS_DEF("Shadowed bbs built for custom traces", custom_traces_bbs_built)
#endif
STATS_DEF("Recreated fragments, total", num_recreated_fragments)
STATS_DEF("Recreated fragments, traces", num_recreated_traces)
STATS_DEF("Recreations via app re-decode", recreate_via_app_ilist)
STATS_DEF("Recreations via stored info", recreate_via_stored_info)
STATS_DEF("Recreation spill value restores", recreate_spill_restores)
STATS_DEF("IBL stubs updated on table resize", num_ibl_stub_resize_updates)

STATS_DEF("Patched fragments", emit_patched_fragments)
STATS_DEF("Patched relocation slots", emit_patched_relocations)
STATS_DEF("Branches linked, direct", num_direct_links)
STATS_DEF("Branches linked, indirect", num_indirect_links)
STATS_DEF("Branches already linked, indirect", num_indirect_already_linked)

RSTATS_DEF("Current coarse-grain units", num_coarse_units)
RSTATS_DEF("Peak coarse-grain units", peak_num_coarse_units)
STATS_DEF("Coarse-grain fragments generated", num_coarse_fragments)
STATS_DEF("Coarse-grain fragments in secondary units", num_coarse_secondary)
STATS_DEF("Fine-grain fragments in coarse-grain regions", num_fine_in_coarse)
STATS_DEF("Coarse prevented by overlap w/ fine region", coarse_overlap_with_fine)
STATS_DEF("Coarse prevented by non-exit cti", coarse_prevent_cti)
#ifdef X64
STATS_DEF("Coarse prevented by rip-rel", coarse_prevent_riprel)
#endif
STATS_DEF("Coarse prevented by privateness", coarse_prevent_private)
STATS_DEF("Coarse prevented by ind call conversion", coarse_prevent_indcall)
STATS_DEF("Coarse prevented by system call", coarse_prevent_syscall)
STATS_DEF("Coarse prevented by must-end-trace", coarse_prevent_end_trace)
STATS_DEF("Coarse prevented by cannot-be-trace", coarse_prevent_no_trace)
STATS_DEF("Coarse prevented by selfmod", coarse_prevent_selfmod)
STATS_DEF("Coarse prevented by translation store", coarse_prevent_translation)
STATS_DEF("Coarse prevented by cb return", coarse_prevent_cbret)
STATS_DEF("Coarse prevented by native_exec", coarse_prevent_native_exec)
STATS_DEF("Coarse prevented by client", coarse_prevent_client)
STATS_DEF("Lazy links from coarse-grain", lazy_links_from_coarse)
STATS_DEF("Lazy links from persisted units", lazy_links_from_persisted)
STATS_DEF("Lazy links from fine-grain", lazy_links_from_fine)
STATS_DEF("Lazy links that failed to link", lazy_links_failed)
STATS_DEF("Coarse-grain direct re-links", coarse_relinks)
STATS_DEF("Coarse-grain trace head path-dependent", coarse_th_path_dependent)
STATS_DEF("Coarse-grain trace heads from fine", coarse_th_from_fine)
STATS_DEF("Coarse grain freezes", coarse_freezes)
STATS_DEF("Coarse grain freezes aborted", coarse_freeze_abort)
STATS_DEF("Coarse grain at-unload not persist: synch fail",
          persist_unload_suspend_failure)
STATS_DEF("Coarse grain units frozen", coarse_units_frozen)
STATS_DEF("Coarse grain fall-throughs during freezing", coarse_freeze_fallthrough)
STATS_DEF("Coarse grain trace heads found on shift", coarse_th_on_shift)
STATS_DEF("Coarse grain units persisted: attempts", coarse_units_persist_try)
STATS_DEF("Coarse grain units persist-at-unload attempts", persist_unload_try)
STATS_DEF("Coarse grain units persisted: success", coarse_units_persist)
STATS_DEF("Coarse grain fragments frozen", coarse_fragments_frozen)
STATS_DEF("Coarse grain code persisted (bytes)", coarse_code_persisted)
STATS_DEF("Coarse grain units not persisted: too small", persist_too_small)
STATS_DEF("Coarse grain code small, persisted anyway", persist_code_small)
STATS_DEF("Coarse grain units not persist: no space", coarse_units_persist_nospace)
STATS_DEF("Coarse grain units not persist: can't patch", coarse_units_persist_nopatch)
STATS_DEF("Coarse grain units not persist: duplicate", coarse_units_persist_dup)
STATS_DEF("Coarse grain units not persist: file/name error", coarse_units_persist_error)
STATS_DEF("Coarse grain units not persist: excluded", coarse_units_persist_excluded)
STATS_DEF("Persisted cache files renamed", persist_rename_success)
STATS_DEF("Coarse grain units not persist: rename tmp fail", persist_rename_tmp_fail)
STATS_DEF("Coarse grain units not persist: rename fail", persist_rename_fail)
STATS_DEF("Coarse grain units not persist: rename race", persist_rename_race)
STATS_DEF("Persisted cache files renamed & deleted", persist_delete_success)
STATS_DEF("Persisted cache tmp file delete error on failure", persist_delete_tmp_fail)
STATS_DEF("Coarse grain units merged", coarse_units_merged)
STATS_DEF("Coarse grain merges with on-disk files", coarse_merge_disk)
STATS_DEF("Coarse grain region mismatches w/ on-disk files", coarse_merge_disk_mismatch)
STATS_DEF("Coarse grain failed merges w/ on-disk files", coarse_merge_disk_fail)
STATS_DEF("Coarse grain dups when merging", coarse_merge_dups)
STATS_DEF("RAC entries out of coarse range when persisting",
          rac_module_persist_out_of_range)
STATS_DEF("RCT entries out of coarse range when persisting",
          rct_module_persist_out_of_range)
STATS_DEF("RCT entries that outlasted persisted cache", rct_persisted_outlast_cache)
STATS_DEF("Coarse units marked invalid", coarse_marked_invalid)
STATS_DEF("Coarse units marked valid", coarse_marked_valid)
STATS_DEF("Coarse units executed while invalid", coarse_executed_invalid)
STATS_DEF("Coarse region merged with IAT post-rebind", coarse_merge_IAT)
STATS_DEF("Coarse pclookup cached entries", coarse_pclookup_cached)

STATS_DEF("Hotpatch match requiring persisted cache flush", hotp_persist_flush)

STATS_DEF("Persisted cache exec loads attempted", perscache_load_attempt)
STATS_DEF("Persisted cache post-rebind re-loads attempted", perscache_rebind_load)
STATS_DEF("Persisted cache non-exec loads attempted", perscache_load_nox_attempt)
RSTATS_DEF("Persisted caches successfully loaded", perscache_loaded)
STATS_DEF("Persisted cache load error: name error/excluded", perscache_load_noname)
STATS_DEF("Persisted cache load error: excluded", perscache_load_excluded)
STATS_DEF("Persisted cache load error: file not found", perscache_load_nofile)
STATS_DEF("Persisted cache load error: bad file", perscache_bad_file)
STATS_DEF("Persisted cache load error: version mismatch", perscache_version_mismatch)
STATS_DEF("Persisted cache load error: md5 mismatch", perscache_md5_mismatch)
STATS_DEF("Persisted cache load error: modinfo mismatch", perscache_modinfo_mismatch)
STATS_DEF("Persisted cache load error: modbase mismatch", perscache_base_mismatch)
STATS_DEF("Persisted cache load error: region mismatch", perscache_region_mismatch)
STATS_DEF("Persisted cache load error: tls offs mismatch", perscache_tls_mismatch)
STATS_DEF("Persisted cache load error: no trace support", perscache_trace_mismatch)
STATS_DEF("Persisted cache load error: no RAC/RCT support", perscache_rct_mismatch)
STATS_DEF("Persisted cache load error: option mismatch", perscache_options_mismatch)
STATS_DEF("Persisted cache load error: maps not adjacent", perscache_maps_not_adjacent)
#ifdef HOT_PATCHING_INTERFACE
STATS_DEF("Persisted cache load error: hotp conflict", perscache_hotp_conflict)
STATS_DEF("Persisted cache hotp conflict avoided", perscache_hotp_conflict_avoided)
STATS_DEF("Persisted cache hotp nudge flush avoided", perscache_hotp_flush_avoided)
#endif
STATS_DEF("Persisted cache ibl entries prefilled", perscache_ibl_prefill)
STATS_DEF("Persisted cache stub unprot for link", pcache_unprot_link)
STATS_DEF("Persisted cache stub unprot for unlink", pcache_unprot_unlink)
STATS_DEF("Persisted cache stub writes over limit", pcache_unprot_over_limit)
STATS_DEF("Persisted cache stub pages touched", pcache_stub_touched)

#ifdef SIDELINE
STATS_DEF("Waits due to sideline", num_wait_sideline)
#endif
STATS_DEF("Waits due to flushing", num_wait_flush)
STATS_DEF("Waits due to shared cache barrier", num_wait_shared_barrier)

STATS_DEF("Entrance hooks to DR", num_entering_DR)
STATS_DEF("Exit hooks from DR", num_exiting_DR)
STATS_DEF("Fcache exits, total", num_exits)
STATS_DEF("Fcache exits, coarse-grain fragments", num_exits_coarse)
STATS_DEF("Fcache exits, coarse-grain targeting trace head", num_exits_coarse_trace_head)
STATS_DEF("Fcache exits, fine targeting th coarse", num_exits_fine2th_coarse)
STATS_DEF("Fcache exits, fine targeting non-th coarse", num_exits_fine2non_th_coarse)
STATS_DEF("Fcache exits, system call executions", num_exits_syscalls)
STATS_DEF("Fcache exits, flushed due to code mod", num_exits_code_mod_flush)
STATS_DEF("Fcache exits, deleted but hit in ibl", num_exits_ibl_deleted)
STATS_DEF("Fcache exits, asynch", num_exits_asynch)
STATS_DEF("Fcache exits, native_exec executions", num_exits_native_exec)
STATS_DEF("Fcache exits, native_exec syscalls", num_exits_native_exec_syscall)
STATS_DEF("Fcache exits, proactive reset", num_exits_reset)
STATS_DEF("Fcache exits, going native", num_exits_native)
#ifdef HOT_PATCHING_INTERFACE
STATS_DEF("Fcache exits, hot patching control flow change", num_exits_hot_patch)
#endif
#ifdef CLIENT_INTERFACE
STATS_DEF("Fcache exits, client redirecting", num_exits_client_redirect)
#endif
STATS_DEF("Fcache entrances aborted b/c target missing", num_entrances_aborted)
STATS_DEF("Fcache exits, from traces", num_trace_exits)
STATS_DEF("Fcache exits, from BBs", num_bb_exits)
STATS_DEF("Fcache exits, total indirect branches", num_exits_ind_total)
STATS_DEF("Fcache exits, non-trace indirect branches", num_exits_ind_non_trace)
STATS_DEF("Fcache exits, ind target not in cache", num_exits_ind_good_miss)
STATS_DEF("Fcache exits, ind target extending a trace, BAD", num_exits_ind_trace_build)
STATS_DEF("Fcache exits, ind target in cache but not table", num_exits_ind_bad_miss)
STATS_DEF("Fcache exits, src fragment unlinked", num_exits_ind_src_unlinked)

STATS_DEF("Fcache exits, from BB, ind target ...", num_exits_ind_bad_miss_bb)
STATS_DEF("Fcache exits, BB->BB, ind target ...", num_exits_ind_bad_miss_bb2bb)
STATS_DEF("Fcache exits, BB->BB trace head, ind target ...",
          num_exits_ind_bad_miss_bb2bb_th)
STATS_DEF("Fcache exits, BB->trace, ind target ...", num_exits_ind_bad_miss_bb2trace)

STATS_DEF("Fcache exits, from trace, ind target ...", num_exits_ind_bad_miss_trace)
STATS_DEF("Fcache exits, trace->trace, ind target ...",
          num_exits_ind_bad_miss_trace2trace)
STATS_DEF("Fcache exits, trace->BB not trace head, ind tgt",
          num_exits_ind_bad_miss_trace2bb_nth)
STATS_DEF("Fcache exits, trace->BB trace head, ind target",
          num_exits_ind_bad_miss_trace2bb_th)

#ifdef RETURN_AFTER_CALL
/* These statistics available only under RAC, should make default  */
STATS_DEF("Fcache exits, indirect calls", num_exits_ind_call)
STATS_DEF("Fcache exits, indirect jmps", num_exits_ind_jmp)
STATS_DEF("Fcache exits, returns", num_exits_ret)
STATS_DEF("Fcache exits, returns from traces", num_exits_ret_trace)
#endif /* RETURN_AFTER_CALL */
STATS_DEF("Fcache exits, unknown indirect, BAD", num_exits_ind_unknown)
STATS_DEF("Fcache exits, dir target not in cache", num_exits_dir_miss)
STATS_DEF("Fcache exits, link not allowed", num_exits_dir_nolink)
#ifndef TRACE_HEAD_CACHE_INCR
STATS_DEF("Fcache exits, target trace head", num_exits_dir_trace_head)
#endif
#ifdef TRACE_HEAD_CACHE_INCR
STATS_DEF("Fcache exits, target trace head now hot", num_exits_dir_trace_hot)
#endif
STATS_DEF("Fcache exits, extending a trace", num_exits_dir_trace_build)
STATS_DEF("Fcache exits, non-ignorable system call", num_exits_dir_syscall)
#ifdef WINDOWS
STATS_DEF("Fcache exits, callback return", num_exits_dir_cbret)
STATS_DEF("Fcache exits, from unlinked shared syscall",
          num_unlinked_shared_syscalls_exits)
STATS_DEF("Fcache exits, from BB->shared syscall", num_shared_syscalls_bb_exits)
STATS_DEF("Fcache exits, from trace->shared syscall", num_shared_syscalls_trace_exits)
#endif
STATS_DEF("Fcache exits, no link shared <-> private", num_exits_dir_nolink_sharing)
STATS_DEF("Fcache exits, presumed link race condition", num_exits_dir_race)
STATS_DEF("Fcache exits, self-replacement", num_exits_dir_self_replacement)
#ifdef UNIX
STATS_DEF("Fcache exits, signal delivery", num_exits_dir_signal)
#endif
STATS_DEF("Fcache exits needing cbr disambiguation", cbr_disambiguations)

STATS_DEF("Float pc state updates intra-cache", float_pc_from_cache)
STATS_DEF("Float pc state updates from d_r_dispatch", float_pc_from_dispatch)

STATS_DEF("Fragments with OF restore prefix", num_oflag_prefix_restore)
STATS_DEF("Fcache free capacity (bytes)", fcache_free_capacity)

STATS_DEF("Fcache trace capacity (bytes)", fcache_trace_capacity)
STATS_DEF("Fcache trace peak capacity (bytes)", fcache_trace_capacity_peak)
STATS_DEF("Fcache trace space claimed (bytes)", fcache_trace_claimed)
STATS_DEF("Fcache trace space used (bytes)", fcache_trace_used)
STATS_DEF("Fcache trace peak used (bytes)", fcache_trace_peak)
STATS_DEF("Fcache trace headers (bytes)", fcache_trace_headers)
STATS_DEF("Fcache trace fragment bodies (bytes)", fcache_trace_bodies)
STATS_DEF("Fcache trace direct exit stubs (bytes)", fcache_trace_direct_stubs)
STATS_DEF("Fcache trace indirect exit stubs (bytes)", fcache_trace_indirect_stubs)
STATS_DEF("Fcache trace fragment prefixes (bytes)", fcache_trace_prefixes)
STATS_DEF("Fcache trace align space (bytes)", fcache_trace_align)
STATS_DEF("Fcache trace empty space (bytes)", fcache_trace_empty)
STATS_DEF("Fcache trace selfmod copy (bytes)", fcache_trace_selfmod_copy)
STATS_DEF("Fcache trace free coalesce prev", fcache_trace_free_coalesce_prev)
STATS_DEF("Fcache trace free coalesce next", fcache_trace_free_coalesce_next)
STATS_DEF("Fcache trace free coalesce too big", fcache_trace_free_coalesce_too_big)
STATS_DEF("Fcache trace return last", fcache_trace_return_last)
STATS_DEF("Fcache trace free use larger bucket", fcache_trace_free_use_larger)
STATS_DEF("Fcache trace free split", fcache_trace_free_split)

STATS_DEF("Fcache bb capacity (bytes)", fcache_bb_capacity)
STATS_DEF("Fcache bb peak capacity (bytes)", fcache_bb_capacity_peak)
STATS_DEF("Fcache bb space claimed (bytes)", fcache_bb_claimed)
STATS_DEF("Fcache bb space used (bytes)", fcache_bb_used)
STATS_DEF("Fcache bb peak used (bytes)", fcache_bb_peak)
STATS_DEF("Fcache bb headers (bytes)", fcache_bb_headers)
STATS_DEF("Fcache bb fragment bodies (bytes)", fcache_bb_bodies)
STATS_DEF("Fcache bb direct exit stubs (bytes)", fcache_bb_direct_stubs)
STATS_DEF("Fcache bb indirect exit stubs (bytes)", fcache_bb_indirect_stubs)
STATS_DEF("Fcache bb fragment prefixes (bytes)", fcache_bb_prefixes)
STATS_DEF("Fcache bb align space (bytes)", fcache_bb_align)
STATS_DEF("Fcache bb empty space (bytes)", fcache_bb_empty)
STATS_DEF("Fcache bb selfmod copy (bytes)", fcache_bb_selfmod_copy)
STATS_DEF("Fcache bb free coalesce prev", fcache_bb_free_coalesce_prev)
STATS_DEF("Fcache bb free coalesce next", fcache_bb_free_coalesce_next)
STATS_DEF("Fcache bb free coalesce too big", fcache_bb_free_coalesce_too_big)
STATS_DEF("Fcache bb return last", fcache_bb_return_last)
STATS_DEF("Fcache bb free use larger bucket", fcache_bb_free_use_larger)
STATS_DEF("Fcache bb free split", fcache_bb_free_split)

STATS_DEF("Fcache shared bb capacity (bytes)", fcache_shared_bb_capacity)
STATS_DEF("Fcache shared bb peak capacity (bytes)", fcache_shared_bb_capacity_peak)
STATS_DEF("Fcache shared bb space claimed (bytes)", fcache_shared_bb_claimed)
STATS_DEF("Fcache shared bb space used (bytes)", fcache_shared_bb_used)
STATS_DEF("Fcache shared bb peak used (bytes)", fcache_shared_bb_peak)
STATS_DEF("Fcache shared bb headers (bytes)", fcache_shared_bb_headers)
STATS_DEF("Fcache shared bb fragment bodies (bytes)", fcache_shared_bb_bodies)
STATS_DEF("Fcache shared bb direct exit stubs (bytes)", fcache_shared_bb_direct_stubs)
STATS_DEF("Fcache shared bb indirect exit stubs (bytes)", fcache_shared_bb_indirect_stubs)
STATS_DEF("Fcache shared bb fragment prefixes (bytes)", fcache_shared_bb_prefixes)
STATS_DEF("Fcache shared bb align space (bytes)", fcache_shared_bb_align)
STATS_DEF("Fcache shared bb empty space (bytes)", fcache_shared_bb_empty)
STATS_DEF("Fcache shared bb selfmod copy (bytes)", fcache_shared_bb_selfmod_copy)
STATS_DEF("Fcache shared bb free coalesce prev", fcache_shared_bb_free_coalesce_prev)
STATS_DEF("Fcache shared bb free coalesce next", fcache_shared_bb_free_coalesce_next)
STATS_DEF("Fcache shared bb free coalesce too big",
          fcache_shared_bb_free_coalesce_too_big)
STATS_DEF("Fcache shared bb return last", fcache_shared_bb_return_last)
STATS_DEF("Fcache shared bb free use larger bucket", fcache_shared_bb_free_use_larger)
STATS_DEF("Fcache shared bb free split", fcache_shared_bb_free_split)

STATS_DEF("Fcache shared trace capacity (bytes)", fcache_shared_trace_capacity)
STATS_DEF("Fcache shared trace peak capacity (bytes)", fcache_shared_trace_capacity_peak)
STATS_DEF("Fcache shared trace space claimed (bytes)", fcache_shared_trace_claimed)
STATS_DEF("Fcache shared trace space used (bytes)", fcache_shared_trace_used)
STATS_DEF("Fcache shared trace peak used (bytes)", fcache_shared_trace_peak)
STATS_DEF("Fcache shared trace headers (bytes)", fcache_shared_trace_headers)
STATS_DEF("Fcache shared trace fragment bodies (bytes)", fcache_shared_trace_bodies)
STATS_DEF("Fcache shared trace direct exit stubs (bytes)",
          fcache_shared_trace_direct_stubs)
STATS_DEF("Fcache shared trace indirect exit stubs (bytes)",
          fcache_shared_trace_indirect_stubs)
STATS_DEF("Fcache shared trace fragment prefixes (bytes)", fcache_shared_trace_prefixes)
STATS_DEF("Fcache shared trace align space (bytes)", fcache_shared_trace_align)
STATS_DEF("Fcache shared trace empty space (bytes)", fcache_shared_trace_empty)
STATS_DEF("Fcache shared trace selfmod copy (bytes)", fcache_shared_trace_selfmod_copy)
STATS_DEF("Fcache shared trace free coalesce prev",
          fcache_shared_trace_free_coalesce_prev)
STATS_DEF("Fcache shared trace free coalesce next",
          fcache_shared_trace_free_coalesce_next)
STATS_DEF("Fcache shared trace free coalesce too big",
          fcache_shared_trace_free_coalesce_too_big)
STATS_DEF("Fcache shared trace return last", fcache_shared_trace_return_last)
STATS_DEF("Fcache shared trace free use larger bucket",
          fcache_shared_trace_free_use_larger)
STATS_DEF("Fcache shared trace free split", fcache_shared_trace_free_split)

STATS_DEF("Fcache coarse bb capacity (bytes)", fcache_coarse_bb_capacity)
STATS_DEF("Fcache coarse bb peak capacity (bytes)", fcache_coarse_bb_capacity_peak)
STATS_DEF("Fcache coarse bb space claimed (bytes)", fcache_coarse_bb_claimed)
STATS_DEF("Fcache coarse bb space used (bytes)", fcache_coarse_bb_used)
STATS_DEF("Fcache coarse bb peak used (bytes)", fcache_coarse_bb_peak)
STATS_DEF("Fcache coarse bb headers (bytes)", fcache_coarse_bb_headers)
STATS_DEF("Fcache coarse bb fragment bodies (bytes)", fcache_coarse_bb_bodies)
STATS_DEF("Fcache coarse bb direct exit stubs (bytes)", fcache_coarse_bb_direct_stubs)
STATS_DEF("Fcache coarse bb indirect exit stubs (bytes)", fcache_coarse_bb_indirect_stubs)
STATS_DEF("Fcache coarse bb fragment prefixes (bytes)", fcache_coarse_bb_prefixes)
STATS_DEF("Fcache coarse bb align space (bytes)", fcache_coarse_bb_align)
STATS_DEF("Fcache coarse bb empty space (bytes)", fcache_coarse_bb_empty)
STATS_DEF("Fcache coarse bb selfmod copy (bytes)", fcache_coarse_bb_selfmod_copy)
STATS_DEF("Fcache coarse bb free coalesce prev", fcache_coarse_bb_free_coalesce_prev)
STATS_DEF("Fcache coarse bb free coalesce next", fcache_coarse_bb_free_coalesce_next)
STATS_DEF("Fcache coarse bb free coalesce too big",
          fcache_coarse_bb_free_coalesce_too_big)
STATS_DEF("Fcache coarse bb return last", fcache_coarse_bb_return_last)
STATS_DEF("Fcache coarse bb free use larger bucket", fcache_coarse_bb_free_use_larger)
STATS_DEF("Fcache coarse bb free split", fcache_coarse_bb_free_split)

STATS_DEF("Fcache combined claimed (bytes)", fcache_combined_claimed)
RSTATS_DEF("Current fcache combined capacity (bytes)", fcache_combined_capacity)
RSTATS_DEF("Peak fcache combined capacity (bytes)", peak_fcache_combined_capacity)
RSTATS_DEF("Current fcache units on live list", fcache_num_live)
RSTATS_DEF("Peak fcache units on live list", peak_fcache_num_live)
RSTATS_DEF("Current fcache units on free list", fcache_num_free)
RSTATS_DEF("Peak fcache units on free list", peak_fcache_num_free)
STATS_DEF("Fcache unit lookups", fcache_unit_lookups)

STATS_DEF("Separate shared trace direct exit stubs (bytes)",
          separate_shared_trace_direct_stubs)
STATS_DEF("Separate shared bb direct exit stubs (bytes)", separate_shared_bb_direct_stubs)
STATS_DEF("Separate shared bb direct entrance stubs (bytes)",
          separate_shared_bb_entrance_stubs)
STATS_DEF("Separate trace direct exit stubs (bytes)", separate_trace_direct_stubs)
STATS_DEF("Separate bb direct exit stubs (bytes)", separate_bb_direct_stubs)
STATS_DEF("Special heap units", heap_special_units)
STATS_DEF("Peak special heap units", peak_heap_special_units)
STATS_DEF("Special heap align space (bytes)", heap_special_align)
RSTATS_DEF("Current special heap capacity (bytes)", heap_special_capacity)
RSTATS_DEF("Peak special heap capacity (bytes)", peak_heap_special_capacity)

RSTATS_DEF("Current heap units on live list", heap_num_live)
RSTATS_DEF("Peak heap units on live list", peak_heap_num_live)
RSTATS_DEF("Current heap units on free list", heap_num_free)
RSTATS_DEF("Peak heap units on free list", peak_heap_num_free)
STATS_DEF("Heap headers (bytes)", heap_headers)
STATS_DEF("Heap align space (bytes)", heap_align)
STATS_DEF("Peak heap align space (bytes)", peak_heap_align)
STATS_DEF("Heap bucket pad space (bytes)", heap_bucket_pad)
STATS_DEF("Peak heap bucket pad space (bytes)", peak_heap_bucket_pad)
STATS_DEF("Heap allocs in buckets", heap_allocs_buckets)
STATS_DEF("Heap allocs variable-sized", heap_allocs_variable)
STATS_DEF("Total reserved memory", reserved_memory_capacity)
STATS_DEF("Peak total reserved memory", peak_reserved_memory_capacity)
STATS_DEF("Guard pages, reserved virtual pages", guard_pages)
STATS_DEF("Peak guard pages, reserved virtual pages", peak_guard_pages)

#ifdef CLIENT_INTERFACE
RSTATS_DEF("Current client raw mmap size", client_raw_mmap_size)
RSTATS_DEF("Peak client raw mmap size", peak_client_raw_mmap_size)
#endif
RSTATS_DEF("Current stack capacity (bytes)", stack_capacity)
RSTATS_DEF("Peak stack capacity (bytes)", peak_stack_capacity)
STATS_DEF("Mmaps sharing stack alloc region", mmap_share_stack_region)
STATS_DEF("Mmaps unable to share stack alloc region", mmap_no_share_stack_region)
STATS_DEF("Mmap capacity (bytes)", mmap_capacity)
STATS_DEF("Peak mmap capacity (bytes)", peak_mmap_capacity)
STATS_DEF("Mmap reserved but not committed (bytes)", mmap_reserved_only)
STATS_DEF("Peak mmap reserved but not committed (bytes)", peak_mmap_reserved_only)
STATS_DEF("Heap claimed (bytes)", heap_claimed)
STATS_DEF("Peak heap claimed (bytes)", peak_heap_claimed)
RSTATS_DEF("Current heap capacity (bytes)", heap_capacity)
RSTATS_DEF("Peak heap capacity (bytes)", peak_heap_capacity)
STATS_DEF("Heap reserved but not committed (bytes)", heap_reserved_only)
STATS_DEF("Peak heap reserved but not committed (bytes)", peak_heap_reserved_only)
STATS_DEF("File map capacity (bytes)", file_map_capacity)
STATS_DEF("Peak file map capacity (bytes)", peak_file_map_capacity)
RSTATS_DEF("Current total memory from OS (bytes)", memory_capacity)
RSTATS_DEF("Peak total memory from OS (bytes)", peak_memory_capacity)
STATS_DEF("Our library space (bytes)", dr_library_space)

#ifdef WINDOWS
/* reserved means reserved but not committed */
STATS_DEF("Application reserved-only capacity (bytes)", app_reserved_capacity)
STATS_DEF("Peak application reserved-only capacity (bytes)", peak_app_reserved_capacity)
STATS_DEF("Application committed capacity (bytes)", app_committed_capacity)
STATS_DEF("Peak application committed capacity (bytes)", peak_app_committed_capacity)
#endif
STATS_DEF("Application stack capacity (bytes)", app_stack_capacity)
STATS_DEF("Peak application stack capacity (bytes)", peak_app_stack_capacity)
STATS_DEF("Application heap capacity (bytes)", app_heap_capacity)
STATS_DEF("Peak application heap capacity (bytes)", peak_app_heap_capacity)
#ifdef WINDOWS
STATS_DEF("Application image capacity (bytes)", app_image_capacity)
STATS_DEF("Peak application image capacity (bytes)", peak_app_image_capacity)
/* for win32, image is separated from rest of mmap */
#endif
STATS_DEF("Application mmap capacity (bytes)", app_mmap_capacity)
STATS_DEF("Peak application mmap capacity (bytes)", peak_app_mmap_capacity)
STATS_DEF("Application executable capacity (bytes)", app_exec_capacity)
STATS_DEF("Peak application executable capacity (bytes)", peak_app_exec_capacity)
STATS_DEF("Application read-only capacity (bytes)", app_ro_capacity)
STATS_DEF("Peak application read-only capacity (bytes)", peak_app_ro_capacity)
STATS_DEF("Application writable capacity (bytes)", app_rw_capacity)
STATS_DEF("Peak application writable capacity (bytes)", peak_app_rw_capacity)
STATS_DEF("Total (app + us) virtual size (bytes)", total_vsize)
STATS_DEF("Peak total (app + us) virtual size (bytes)", peak_total_vsize)
STATS_DEF("Application virtual size (bytes)", app_vsize)
STATS_DEF("Peak application virtual size (bytes)", peak_app_vsize)
STATS_DEF("Our additional virtual size (bytes)", dr_vsize)
STATS_DEF("Peak our additional virtual size (bytes)", peak_dr_vsize)
#ifdef WINDOWS
STATS_DEF("Our committed capacity (bytes)", dr_commited_capacity)
STATS_DEF("Our peak committed capacity (bytes)", peak_dr_commited_capacity)
STATS_DEF("Our reserved capacity (bytes)", dr_reserved_capacity)
STATS_DEF("Our peak reserved capacity (bytes)", peak_dr_reserved_capacity)
STATS_DEF("App unallocatable free space", app_wasted_vsize)
STATS_DEF("Peak app unallocatable free space", peak_app_wasted_vsize)
STATS_DEF("Our unallocatable free space", dr_wasted_vsize)
STATS_DEF("Our peak unallocatable free space", peak_dr_wasted_vsize)
STATS_DEF("Total unallocatable free space", total_wasted_vsize)
STATS_DEF("Peak total unallocatable free space", peak_total_wasted_vsize)
STATS_DEF("Number of unaligned allocations (TEB's etc.)", unaligned_allocations)
STATS_DEF("Peak unaligned allocations", peak_unaligned_allocations)
#endif
RSTATS_DEF("Current vmm blocks for unreachable heap", vmm_blocks_unreach_heap)
RSTATS_DEF("Peak vmm blocks for unreachable heap", peak_vmm_blocks_unreach_heap)
RSTATS_DEF("Current vmm blocks for stack", vmm_blocks_unreach_stack)
RSTATS_DEF("Peak vmm blocks for stack", peak_vmm_blocks_unreach_stack)
RSTATS_DEF("Current vmm blocks for unreachable special heap",
           vmm_blocks_unreach_special_heap)
RSTATS_DEF("Peak vmm blocks for unreachable special heap",
           peak_vmm_blocks_unreach_special_heap)
RSTATS_DEF("Current vmm blocks for unreachable special mmap",
           vmm_blocks_unreach_special_mmap)
RSTATS_DEF("Peak vmm blocks for unreachable special mmap",
           peak_vmm_blocks_unreach_special_mmap)
RSTATS_DEF("Current vmm blocks for reachable heap", vmm_blocks_reach_heap)
RSTATS_DEF("Peak vmm blocks for reachable heap", peak_vmm_blocks_reach_heap)
RSTATS_DEF("Current vmm blocks for cache", vmm_blocks_reach_cache)
RSTATS_DEF("Peak vmm blocks for cache", peak_vmm_blocks_reach_cache)
RSTATS_DEF("Current vmm blocks for reachable special heap", vmm_blocks_reach_special_heap)
RSTATS_DEF("Peak vmm blocks for reachable special heap",
           peak_vmm_blocks_reach_special_heap)
RSTATS_DEF("Current vmm blocks for reachable special mmap", vmm_blocks_reach_special_mmap)
RSTATS_DEF("Peak vmm blocks for reachable special mmap",
           peak_vmm_blocks_reach_special_mmap)
STATS_DEF("Our virtual memory blocks in use", vmm_vsize_blocks_used)
STATS_DEF("Peak our virtual memory blocks in use", peak_vmm_vsize_blocks_used)
STATS_DEF("Wasted vmm space due to alignment", vmm_vsize_wasted)
STATS_DEF("Peak wasted vmm space due to alignment", peak_vmm_vsize_wasted)
STATS_DEF("Allocations using multiple vmm blocks", vmm_multi_block_allocs)
STATS_DEF("Blocks used for multi-block allocs", vmm_multi_blocks)
RSTATS_DEF("Current vmm virtual memory in use (bytes)", vmm_vsize_used)
RSTATS_DEF("Peak vmm virtual memory in use (bytes)", peak_vmm_vsize_used)
STATS_DEF("Number of landing pad areas allocated", num_landing_pad_areas)
STATS_DEF("Total times mutexes acquired", total_acquired)
STATS_DEF("Total times mutexes contended", total_contended)
STATS_DEF("Unable to wait_at_safe_spot cache entries", no_wait_entries)
STATS_DEF("Interoperability fixups for apc_policy", num_used_apc_policy)
STATS_DEF("Interoperability fixups for thread_policy", num_used_thread_policy)
STATS_DEF("Number of safe reads", num_safe_reads)
STATS_DEF("Number of safe writes", num_safe_writes)
STATS_DEF("Number of vmarea vector resize reallocations", num_vmareas_resized)
STATS_DEF("Number of vmarea vector resize synch fixups", num_vmareas_resize_synch)
STATS_DEF("Peak vmarea vector length", max_vmareas_length)
STATS_DEF("Peak dynamo areas vector length", max_DRareas_length)
STATS_DEF("Peak executable areas vector length", max_execareas_length)
STATS_DEF("Peak module areas vector length", max_modareas_length)

/* probably more -pad_jmps stats then needed, remove some of the less important ones
 * once we've better characterized the behavior */
STATS_DEF("-pad_jmps fragments size overestimated", pad_jmps_fragments_overestimated)
STATS_DEF("-pad_jmps excess instances coalesced w/ nxt free", pad_jmps_excess_next_free)
STATS_DEF("-pad_jmps excess instances failed to be returned", pad_jmps_excess_wasted)
STATS_DEF("-pad_jmps excess bytes failed to be returned", pad_jmps_excess_wasted_bytes)
STATS_DEF("-pad_jmps body bytes shared bb", pad_jmps_shared_bb_body_bytes)
STATS_DEF("-pad_jmps stub bytes shared bb", pad_jmps_shared_bb_stub_bytes)
STATS_DEF("Emitted unaligned patch exits shared bb", pad_jmps_shared_bb_unaligned_exits)
STATS_DEF("Emitted unaligned exits bytes shared bb",
          pad_jmps_shared_bb_unaligned_exit_bytes)
STATS_DEF("Emitted unaligned stubs shared bb", pad_jmps_shared_bb_unaligned_stubs)
STATS_DEF("Emitted unaligned stubs bytes shared bb",
          pad_jmps_shared_bb_unaligned_stubs_bytes)
STATS_DEF("-pad_jmps excess bytes shared bb", pad_jmps_shared_bb_excess_bytes)
STATS_DEF("Bytes shared frags ever", pad_jmps_shared_bb_sum_fragment_bytes_ever)
STATS_DEF("-pad_jmps start_pcs shifted shared bb",
          pad_jmps_shared_bb_num_start_pc_shifted)
STATS_DEF("-pad_jmps start_pcs shifted bytes shared bb",
          pad_jmps_shared_bb_start_pc_shifted_bytes)
STATS_DEF("-pad_jmps excess bytes released shared bb",
          pad_jmps_shared_bb_extra_space_released)
STATS_DEF("-pad_jmps shifted stubs shared bb", pad_jmps_shared_bb_num_shifted_stubs)
STATS_DEF("-pad_jmps shifted stub bytes shared bb", pad_jmps_shared_bb_shifted_stub_bytes)
STATS_DEF("-pad_jmps no shift stubs shared bb", pad_jmps_shared_bb_num_stubs_no_shift)
STATS_DEF("-pad_jmps inserted nops shared bb", pad_jmps_shared_bb_num_nops)
STATS_DEF("-pad_jmps inserted nop bytes shared bb", pad_jmps_shared_bb_nop_bytes)
STATS_DEF("-pad_jmps no pad exits shared bb", pad_jmps_shared_bb_num_no_pad_exits)

/* shtrace to avoid going over 60 columns */
STATS_DEF("-pad_jmps body bytes shtrace", pad_jmps_shared_trace_body_bytes)
STATS_DEF("-pad_jmps stub bytes shtrace", pad_jmps_shared_trace_stub_bytes)
STATS_DEF("Emitted unaligned patch exits shtrace", pad_jmps_shared_trace_unaligned_exits)
STATS_DEF("Emitted unaligned exits bytes shtrace",
          pad_jmps_shared_trace_unaligned_exit_bytes)
STATS_DEF("Emitted unaligned stubs shtrace", pad_jmps_shared_trace_unaligned_stubs)
STATS_DEF("Emitted unaligned stubs bytes shtrace",
          pad_jmps_shared_trace_unaligned_stubs_bytes)
STATS_DEF("-pad_jmps excess bytes shtrace", pad_jmps_shared_trace_excess_bytes)
STATS_DEF("Bytes shared frags ever", pad_jmps_shared_trace_sum_fragment_bytes_ever)
STATS_DEF("-pad_jmps start_pcs shifted shtrace",
          pad_jmps_shared_trace_num_start_pc_shifted)
STATS_DEF("-pad_jmps start_pcs shifted bytes shtrace",
          pad_jmps_shared_trace_start_pc_shifted_bytes)
STATS_DEF("-pad_jmps excess bytes released shtrace",
          pad_jmps_shared_trace_extra_space_released)
STATS_DEF("-pad_jmps shifted stubs shtrace", pad_jmps_shared_trace_num_shifted_stubs)
STATS_DEF("-pad_jmps shifted stub bytes shtrace",
          pad_jmps_shared_trace_shifted_stub_bytes)
STATS_DEF("-pad_jmps no shift stubs shtrace", pad_jmps_shared_trace_num_stubs_no_shift)
STATS_DEF("-pad_jmps inserted nops shtrace", pad_jmps_shared_trace_num_nops)
STATS_DEF("-pad_jmps inserted nop bytes shtrace", pad_jmps_shared_trace_nop_bytes)
STATS_DEF("-pad_jmps no pad exits shtrace", pad_jmps_shared_trace_num_no_pad_exits)

STATS_DEF("-pad_jmps body bytes trace", pad_jmps_trace_body_bytes)
STATS_DEF("-pad_jmps stub bytes trace", pad_jmps_trace_stub_bytes)
STATS_DEF("Emitted unaligned exits trace", pad_jmps_trace_unaligned_exits)
STATS_DEF("Emitted unaligned exits bytes trace", pad_jmps_trace_unaligned_exit_bytes)
STATS_DEF("Emitted unaligned stubs trace", pad_jmps_trace_unaligned_stubs)
STATS_DEF("Emitted unaligned stubs bytes trace", pad_jmps_trace_unaligned_stubs_bytes)
STATS_DEF("-pad_jmps excess bytes trace", pad_jmps_trace_excess_bytes)
STATS_DEF("Bytes trace frags ever", pad_jmps_trace_sum_fragment_bytes_ever)
STATS_DEF("-pad_jmps start_pcs shifted trace", pad_jmps_trace_num_start_pc_shifted)
STATS_DEF("-pad_jmps start_pcs shifted bytes trace",
          pad_jmps_trace_start_pc_shifted_bytes)
STATS_DEF("-pad_jmps excess bytes released trace", pad_jmps_trace_extra_space_released)
STATS_DEF("-pad_jmps shifted stubs trace", pad_jmps_trace_num_shifted_stubs)
STATS_DEF("-pad_jmps shifted stub bytes trace", pad_jmps_trace_shifted_stub_bytes)
STATS_DEF("-pad_jmps no shift stubs trace", pad_jmps_trace_num_stubs_no_shift)
STATS_DEF("-pad_jmps inserted nops trace", pad_jmps_trace_num_nops)
STATS_DEF("-pad_jmps inserted nop bytes trace", pad_jmps_trace_nop_bytes)
STATS_DEF("-pad_jmps no pad exits trace", pad_jmps_trace_num_no_pad_exits)

STATS_DEF("-pad_jmps body bytes temp", pad_jmps_temp_body_bytes)
STATS_DEF("-pad_jmps stub bytes temp", pad_jmps_temp_stub_bytes)
STATS_DEF("Emitted unaligned exits temp", pad_jmps_temp_unaligned_exits)
STATS_DEF("Emitted unaligned exits bytes temp", pad_jmps_temp_unaligned_exit_bytes)
STATS_DEF("Emitted unaligned stubs temp", pad_jmps_temp_unaligned_stubs)
STATS_DEF("Emitted unaligned stubs bytes temp", pad_jmps_temp_unaligned_stubs_bytes)
STATS_DEF("-pad_jmps excess bytes temp", pad_jmps_temp_excess_bytes)
STATS_DEF("Bytes temp frags ever", pad_jmps_temp_sum_fragment_bytes_ever)
STATS_DEF("-pad_jmps start_pcs shifted temp", pad_jmps_temp_num_start_pc_shifted)
STATS_DEF("-pad_jmps start_pcs shifted bytes temp", pad_jmps_temp_start_pc_shifted_bytes)
STATS_DEF("-pad_jmps excess bytes released temp", pad_jmps_temp_extra_space_released)
STATS_DEF("-pad_jmps shifted stubs temp", pad_jmps_temp_num_shifted_stubs)
STATS_DEF("-pad_jmps shifted stub bytes temp", pad_jmps_temp_shifted_stub_bytes)
STATS_DEF("-pad_jmps no shift stubs temp", pad_jmps_temp_num_stubs_no_shift)
STATS_DEF("-pad_jmps inserted nops temp", pad_jmps_temp_num_nops)
STATS_DEF("-pad_jmps inserted nop bytes temp", pad_jmps_temp_nop_bytes)
STATS_DEF("-pad_jmps no pad exits temp", pad_jmps_temp_num_no_pad_exits)

STATS_DEF("-pad_jmps body bytes bb", pad_jmps_bb_body_bytes)
STATS_DEF("-pad_jmps stub bytes bb", pad_jmps_bb_stub_bytes)
STATS_DEF("Emitted unaligned exits bb", pad_jmps_bb_unaligned_exits)
STATS_DEF("Emitted unaligned exits bytes bb", pad_jmps_bb_unaligned_exit_bytes)
STATS_DEF("Emitted unaligned stubs bb", pad_jmps_bb_unaligned_stubs)
STATS_DEF("Emitted unaligned stubs bytes bb", pad_jmps_bb_unaligned_stubs_bytes)
STATS_DEF("-pad_jmps excess bytes bb", pad_jmps_bb_excess_bytes)
STATS_DEF("Bytes bb frags ever", pad_jmps_bb_sum_fragment_bytes_ever)
STATS_DEF("-pad_jmps start_pcs shifted bb", pad_jmps_bb_num_start_pc_shifted)
STATS_DEF("-pad_jmps start_pcs shifted bytes bb", pad_jmps_bb_start_pc_shifted_bytes)
STATS_DEF("-pad_jmps excess bytes released bb", pad_jmps_bb_extra_space_released)
STATS_DEF("-pad_jmps shifted stubs bb", pad_jmps_bb_num_shifted_stubs)
STATS_DEF("-pad_jmps shifted stub bytes bb", pad_jmps_bb_shifted_stub_bytes)
STATS_DEF("-pad_jmps no shift stubs bb", pad_jmps_bb_num_stubs_no_shift)
STATS_DEF("-pad_jmps inserted nops bb", pad_jmps_bb_num_nops)
STATS_DEF("-pad_jmps inserted nop bytes bb", pad_jmps_bb_nop_bytes)
STATS_DEF("-pad_jmps no pad exits bb", pad_jmps_bb_num_no_pad_exits)

STATS_DEF("Num unsafe hot patches", unaligned_patches)
STATS_DEF("Num nops removed for tracing", num_nops_removed)
STATS_DEF("Num bytes nops removed for tracing", num_nop_bytes_removed)
STATS_DEF("Num synch yields for exiting threads", synch_yields_for_exiting_thread)
STATS_DEF("Num synch yields for uninit threads", synch_yields_for_uninit_thread)
STATS_DEF("Num synch yields", synch_yields)
STATS_DEF("Num synch loops in wait_at_safe_spot", synch_loops_wait_safe)
STATS_DEF("Multiple setcontexts while in wait_at_safe_spot", wait_multiple_setcxt)

#ifdef WINDOWS
/* Borland SEH related stats, xref case 5752 */
STATS_DEF("Num build bb loop breaks due to fs instrs", num_bb_build_fs)
STATS_DEF("Num bbs terminated early for process SEH", num_process_SEH_bb_early_terminate)
STATS_DEF("Num bbs terminated early for debug only process SEH checks",
          num_process_SEH_bb_early_terminate_debug)
STATS_DEF("Num pops to fs0 ignored by process SEH", num_process_SEH_pop_fs0)
STATS_DEF("Num observed writes of a NULL/EndList SEH frame", num_endlist_SEH_write)
STATS_DEF("Num SEH frame push/pops processed", num_SEH_pushes_processed)
STATS_DEF("Num fs instructions processed that aren't SEH", num_fs_movs_not_SEH)
#    ifdef RETURN_AFTER_CALL
STATS_DEF("Num borland SEH try constructs initially matched",
          num_borland_SEH_initial_match)
STATS_DEF("Num borland SEH duplicate frames processed", num_borland_SEH_dup_frame)
STATS_DEF("Num borland SEH try constructs fully matched", num_borland_SEH_try_match)
STATS_DEF("Num borland SEH finally constructs fully matched",
          num_borland_SEH_finally_match)
STATS_DEF("Num borland SEH modified except exemptions", num_borland_SEH_modified)
#    endif
#endif
STATS_DEF("Trace fragment ending with an IBL", num_traces_end_at_ibl)
STATS_DEF("Trace fragment ending with an IBL, return", num_traces_end_at_ibl_return)
STATS_DEF("Trace fragment ending with an IBL, ind call", num_traces_end_at_ibl_ind_call)
STATS_DEF("Trace fragment ending with an IBL, ind jump", num_traces_end_at_ibl_ind_jump)
STATS_DEF("Trace fragment ending with an IBL, syscall", num_traces_end_at_ibl_syscall)
STATS_DEF("Trace fragment ending at MUST_END_TRACE", num_traces_at_must_end_trace)
STATS_DEF("Trace fragment ending with an IBL, speculative",
          num_traces_end_at_ibl_speculative_link)
STATS_DEF("Yields in intercept_apc wait dynamo_initialized",
          apc_yields_while_initializing)
STATS_DEF("IBL Tables groomed", num_ibt_groomed)
STATS_DEF("IBL Tables reached maximum capacity", num_ibt_max_capacity)
STATS_DEF("IAT areas in current modules", num_IAT_areas)
STATS_DEF("Indirect calls via IAT", num_indirect_calls_IAT)
STATS_DEF("Indirect calls via IAT elided", num_indirect_calls_IAT_elided)
STATS_DEF("Indirect calls via IAT converted", num_indirect_calls_IAT_converted)
STATS_DEF("Indirect calls via IAT to native module, skipped",
          num_indirect_calls_IAT_native)
STATS_DEF("Indirect jumps via IAT", num_indirect_jumps_IAT)
STATS_DEF("Indirect jumps via IAT elided", num_indirect_jumps_IAT_elided)
STATS_DEF("Indirect jumps via IAT converted", num_indirect_jumps_IAT_converted)
STATS_DEF("Indirect jumps via IAT non PLT, curiosity", num_indirect_jumps_IAT_not_PLT)
STATS_DEF("Indirect jumps likely PLT not IAT, curiosity", num_indirect_jumps_PLT_not_IAT)
STATS_DEF("Indirect jumps likely PLT", num_indirect_jumps_likely_PLT)
STATS_DEF("Indirect jumps via IAT to native module, skipped",
          num_indirect_jumps_IAT_native)
STATS_DEF("Invalidating cache due to IAT hooker", num_invalidate_IAT_hooker)
STATS_DEF("Num flushes in app prot->rwx we could've skipped",
          num_possible_app_to_rwx_skip_flush)
#ifdef HOT_PATCHING_INTERFACE
STATS_DEF("Protector executions", hotp_num_prot_exec)
STATS_DEF("Detector executions", hotp_num_det_exec)
STATS_DEF("Hot patch control flow changes", hotp_num_cflow_change)
STATS_DEF("Policy read nudges", hotp_num_policy_nudge)
STATS_DEF("Mode read nudges", hotp_num_mode_nudge)
STATS_DEF("Hot patches injected", hotp_num_inject)
STATS_DEF("Fragments w/ direct cti should be hot patched", hotp_num_frag_direct_cti)
STATS_DEF("Hot patches executed after mode was set to OFF", hotp_exec_mode_off)
STATS_DEF("Hot patches injected in hotp_only mode", hotp_only_num_inject)
STATS_DEF("Hot patch control flow collisions in hotp_only", hotp_only_cflow_collision)
STATS_DEF("hotp_only injections aborted", hotp_only_aborted_injects)
#endif
STATS_DEF("ASLR DLLs randomized", aslr_dlls_bumped)
STATS_DEF("ASLR DLLs randomized, retry", aslr_error_retry)
STATS_DEF("ASLR DLLs conflicted, giving up", aslr_dll_conflict_giveup)
STATS_DEF("ASLR DLLs conflicted, better fit retry", aslr_dll_conflict_fit_retry)
STATS_DEF("ASLR DLLs randomized, retry: at base", aslr_retry_at_base)
STATS_DEF("ASLR DLLs randomized, retry: not at base", aslr_retry_not_at_base)
STATS_DEF("ASLR DLLs randomized, retry: app error", aslr_error_on_retry)
STATS_DEF("ASLR DLLs randomized, exempted: reverted", aslr_dlls_exempted)
STATS_DEF("mmap --x mappings loader, no fixup", app_mmap_section_x)
STATS_DEF("mmap rw- mappings loader, fixup", app_mmap_section_rw)
STATS_DEF("mmap r-- mappings non-loader", app_mmap_section_r)
STATS_DEF("mmap requested base mappings", app_mmap_requested_base)
STATS_DEF("mmap PE as MAPPED not IMAGE", app_mmap_PE_as_MAPPED)
STATS_DEF("ASLR randomized mmap of not PE", app_mmap_not_PE_rebased)
STATS_DEF("ASLR sharing: not using shared", aslr_dlls_not_shared)
STATS_DEF("ASLR sharing: shared map attempted", aslr_dlls_shared_mapped)
STATS_DEF("ASLR sharing: shared mapped good", aslr_dlls_shared_mapped_good)
STATS_DEF("ASLR sharing: shared map rebased, not shared", aslr_dlls_shared_map_rebased)
STATS_DEF("ASLR sharing: shared map failed, BAD", aslr_dlls_shared_map_failed)
STATS_DEF("ASLR sharing: compare handle with KnownDlls", aslr_dlls_known_dlls_query)
STATS_DEF("ASLR wouldbe RCT ind call/jmp", aslr_rct_ind_wouldbe)
STATS_DEF("ASLR wouldbe RCT ret", aslr_rct_ret_wouldbe)
STATS_DEF("ASLR wouldbe target, native execution fault", aslr_wouldbe_exec)
STATS_DEF("ASLR heap pads, current", aslr_heap_pads)
STATS_DEF("ASLR heap pads, peak", peak_aslr_heap_pads)
STATS_DEF("ASLR heap pads, ever", ever_aslr_heap_pads)
STATS_DEF("ASLR initial padding, KB", aslr_heap_initial_reservation)
STATS_DEF("ASLR current total random padding, KB", aslr_heap_total_reservation)
STATS_DEF("ASLR peak random padding, KB", peak_aslr_heap_total_reservation)
STATS_DEF("ASLR HEAP_FILL gave up filling", aslr_heap_giveup_filling)
/* GBOP */
STATS_DEF("GBOP validations", gbop_validations)
STATS_DEF("GBOP violations, BAD", gbop_violations)
STATS_DEF("Nudges", num_nudges)
STATS_DEF("Doubled-up nudges", num_pending_nudges)
/*  Clean Calls */
STATS_DEF("Clean Call analyzed", cleancall_analyzed)
STATS_DEF("Clean Call inserted", cleancall_inserted)
STATS_DEF("Clean Call inlined", cleancall_inlined)
STATS_DEF("Clean Call [xyz]mm skipped", cleancall_simd_skipped)
#ifdef X86
STATS_DEF("Clean Call mask skipped", cleancall_opmask_skipped)
#endif
STATS_DEF("Clean Call aflags save skipped", cleancall_aflags_save_skipped)
STATS_DEF("Clean Call aflags clear skipped", cleancall_aflags_clear_skipped)
/* i#107 handle application using same segment register */
STATS_DEF("App reference with FS/GS seg being mangled", app_seg_refs_mangled)
STATS_DEF("App access FS/GS seg being mangled", app_mov_seg_mangled)
#ifdef ARM
STATS_DEF("Reg spills for non-mbr mangling", non_mbr_spills)
STATS_DEF("Reg respill for non-mbr mangling avoided", non_mbr_respill_avoided)
#endif
#ifdef LINUX
RSTATS_DEF("Rseq regions identified", num_rseq_regions)
RSTATS_DEF("Rseq instrumented stores elided", num_rseq_stores_elided)
RSTATS_DEF("Rseq native calls inserted", num_rseq_native_calls_inserted)
#endif
#ifdef AARCHXX
RSTATS_DEF("Load-exclusive instrs converted to CAS", num_ldex2cas)
RSTATS_DEF("Store-exclusive instrs converted to CAS", num_stex2cas)
#endif
