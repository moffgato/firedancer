ifdef FD_HAS_INT128
$(call add-hdrs,fd_bincode.h fd_types.h fd_types_custom.h)
$(call add-objs,fd_types,fd_flamenco)
$(call make-unit-test,test_types,test_types,fd_flamenco fd_ballet fd_util)
$(call run-unit-test,test_types)
endif
$(call add-objs,fd_solana_block.pb,fd_flamenco)
