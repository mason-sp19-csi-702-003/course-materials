# Credit for ROOTDIR implementation:
# kenorb (https://stackoverflow.com/users/55075/kenorb),
# How to get current relative directory of your Makefile?,
# URL (version: 2017-05-23): https://stackoverflow.com/a/35698978
ROOTDIR						=	$(abspath $(patsubst %/,%,$(dir $(abspath		\
								$(lastword $(MAKEFILE_LIST))))))

RM							=	rm
FIND						=	find
COPY						=	cp
LN							=	ln

CONDA						=	conda
CONDA_ENV_FILE				=	environment.yml
CONDA_ENV_NAME				=	csi702

PY							=	python
PY_SETUP					=	setup.py

JUPYTER						=	jupyter
JUPYTERLAB_EXTENSIONS		=	jupyterlab_vim									\
								jupyterlab_templates							\
								@jupyterlab/git									\
								@jupyterlab/github								\
								@mflevine/jupyterlab_html						\
								@jupyter-widgets/jupyterlab-manager				\
								jupyter-matplotlib								\
								@ryantam626/jupyterlab_code_formatter			\
								jupyterlab-python-file
JUPYTERLAB_SERVEREXTENSION	=	jupyterlab_templates							\
								jupyterlab_git									\
								jupyterlab_code_formatter

NBCONVERT_OPTS				=	--config $(ROOTDIR)/jupyter_notebook_config.py

R							=	Rscript

MD							=
JUPYTER_NB2PDF				=
JUPYTER_NB2RST				=

BUILD_DIR					=	$(ROOTDIR)/build
CLASS_NUMBER				=
OUTPUT_DIR					=	$(patsubst %/,%,$(BUILD_DIR)/$(CLASS_NUMBER))
HOMEWORK_DIR				=	$(patsubst %/,%,$(ROOTDIR)/homework)
GUIDES_DIR					=	$(patsubst %/,%,$(ROOTDIR)/guides)
FINAL_PROJECT_DIR			=	$(patsubst %/,%,$(ROOTDIR)/project)

MD_OUTPUT					=	github_document

MD_EXT						=
JUPYTER_NB2PDF_EXT			=	$(OUTPUT_DIR)/%.pdf : %.ipynb
JUPYTER_NB2RST_EXT			=	$(OUTPUT_DIR)/%.rst : %.ipynb

ALL_FILES					=	$(MD)											\
								$(JUPYTER_NB2PDF)								\
								$(JUPYTER_NB2RST)

CLEAN_FILES					=	*_files/										\
								*_cache/

define makefile_help
	@echo 'Makefile for CSI 702 (Spring 2019) course materials                       '
	@echo '                                                                          '
	@echo 'Usage:                                                                    '
	@echo '   make all                            Compile and render all materials   '
	@echo '                                                                          '
	@echo '   make clean                          remove temporary and build files   '
	@echo '   make help                           display this message               '
	@echo '   make env                            create conda venv and install deps '
	@echo '   make pdf                            export Jupyter nb to PDF format    '
	@echo '   make rst                            export Jupyter nb to RST format    '
	@echo '                                                                          '
endef


define setup_build_directory
	mkdir -p "$@"
endef

define cleanup
	-$(RM) -rf $(CLEAN_FILES)
	-$(RM) -f $(ALL_FILES)
	-$(RM) -rf $(BUILD_DIR)
endef

define conda_cleanup
	bash -lc "$(CONDA) clean -y -a"
	sudo bash -lc "conda clean -y --packages"
endef

define pycache_cleanup
	$(FIND) -name "__pycache__" -type d -exec $(RM) -rf {} +
endef

define ipynb_checkpoints_cleanup
	$(FIND) -name ".ipynb_checkpoints" -type d -exec $(RM) -rf {} +
endef

define install_python_deps
	bash -lc "																	\
	$(CONDA) activate $(CONDA_ENV_NAME) &&										\
	$(PY) -m nb_pdf_template.install --minted									\
	"
endef

define install_r_deps
	bash -lc "$(CONDA) activate $(CONDA_ENV_NAME) &&							\
	$(R) -e \"install.packages('remotes', repos = 'https://cran.rstudio.com')\"	\
		 -e \"remotes::install_deps()\""
endef

define update_conda_env
	bash -lc "$(CONDA) env update --file $(CONDA_ENV_FILE)"
endef

define launch_jupyter_lab
	bash -lc "																	\
	$(CONDA) activate $(CONDA_ENV_NAME) &&										\
	$(JUPYTER) lab --ip='0.0.0.0'												\
	"
endef

define nbconvert
	bash -lc "																	\
	$(CONDA) activate $(CONDA_ENV_NAME) &&										\
	$(JUPYTER) nbconvert --to $(1) --output-dir $(2) $(NBCONVERT_OPTS) $<		\
	"
endef

define rmarkdown_render
	$(R) -e "rmarkdown::render(input = '$<', output_file = '$@',			\
			 output_format = '$(1)')"
endef

define install_jupyterlab_extensions
	bash -lc "																	\
	$(CONDA) activate $(CONDA_ENV_NAME) &&										\
	$(JUPYTER) labextension install $(1)										\
	"
endef

define install_serverextension
	bash -lc "																	\
	$(CONDA) activate $(CONDA_ENV_NAME) &&										\
	$(JUPYTER) serverextension enable --py $(1)									\
	"
endef
