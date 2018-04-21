#usage:make -f define.mk PARAM=1
target:
ifdef PARAM
	@echo "define PARAM"
else
	@echo "undefine PARAM"
endif
