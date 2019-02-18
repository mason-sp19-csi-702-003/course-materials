include ../../make.inc

MD		=	$(HOMEWORK_DIR)/homework0.md												\
			$(HOMEWORK_DIR)/homework1.md												\
			$(HOMEWORK_DIR)/homework2a.md
MD_EXT	=	$(HOMEWORK_DIR)/%.md : %.Rmd

all : $(ALL_FILES)

clean :
	$(call cleanup)

$(HOMEWORK_DIR) :
	$(call setup_build_directory)

$(MD) : $(MD_EXT) | $(HOMEWORK_DIR)
	$(call rmarkdown_render,$(MD_OUTPUT))
