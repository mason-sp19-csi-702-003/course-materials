include make.inc

DIRS	=	Rmd

all : $(DIRS)

clean :
	$(foreach dir,$(DIRS),cd $(dir) && $(MAKE) clean && cd ../;)
	$(call pycache_cleanup)
	$(call ipynb_checkpoints_cleanup)
	$(call cleanup)

conda-clean :
	$(call conda_cleanup)

env-full : env pydeps rdeps labextensions serverextensions

env :
	$(call update_conda_env)

help :
	$(call makefile_help)

lab :
	$(call launch_jupyter_lab)

labextensions :
	$(foreach extension,$(JUPYTERLAB_EXTENSIONS),$(call install_jupyterlab_extensions,--no-build $(extension));)
	bash -lc "$(CONDA) activate $(CONDA_ENV_NAME) && $(JUPYTER) lab build"

pydeps :
	$(call install_python_deps)

rdeps :
	$(call install_r_deps)

serverextensions :
	$(foreach serverextension,$(JUPYTERLAB_SERVEREXTENSION),$(call install_serverextension,$(serverextension));)

$(DIRS) :
	$(MAKE) -C $@

.PHONY : all clean env help lab labextensions pydeps rdeps serverextensions $(DIRS)
