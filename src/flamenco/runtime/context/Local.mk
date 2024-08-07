ifdef FD_HAS_INT128
$(call add-hdrs,fd_tpool_runtime_ctx.h)
$(call add-objs,fd_tpool_runtime_ctx,fd_flamenco)

$(call add-hdrs,fd_exec_epoch_ctx.h)
$(call add-objs,fd_exec_epoch_ctx,fd_flamenco)

$(call add-hdrs,fd_exec_slot_ctx.h)
$(call add-objs,fd_exec_slot_ctx,fd_flamenco)

$(call add-hdrs,fd_exec_txn_ctx.h)
$(call add-objs,fd_exec_txn_ctx,fd_flamenco)

$(call add-hdrs,fd_exec_instr_ctx.h)
$(call add-objs,fd_exec_instr_ctx,fd_flamenco)

$(call add-hdrs,fd_capture_ctx.h)
$(call add-objs,fd_capture_ctx,fd_flamenco)
endif
