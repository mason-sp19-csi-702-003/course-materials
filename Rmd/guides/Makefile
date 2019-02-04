include ../../make.inc

MD		=	$(GUIDES_DIR)/howto_provision_virtual_machine.md
MD_EXT	=	$(GUIDES_DIR)/%.md : %.Rmd

all : $(ALL_FILES)

clean :
	$(call cleanup)

$(GUIDES_DIR) :
	$(call setup_build_directory)

$(MD) : $(MD_EXT) | $(GUIDES_DIR)
	$(call rmarkdown_render,$(MD_OUTPUT))
