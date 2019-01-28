include ../make.inc

DIRS	=	homework

MD		=	$(ROOTDIR)/README.md
MD_EXT	=	$(ROOTDIR)/%.md : %.Rmd

.PHONY : clean $(DIRS)

all : $(ALL_FILES) $(DIRS)

clean :
	$(foreach dir,$(DIRS),cd $(dir) && $(MAKE) clean && cd ../;)
	$(call cleanup)

$(MD) : $(MD_EXT) | $(ROOTDIR)
	$(call rmarkdown_render,$(MD_OUTPUT))

$(DIRS) :
	$(MAKE) -C $@
