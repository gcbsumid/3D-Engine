# Standard flags
PROJECTS := opengl

.PHONY: all clean help $(PROJECTS)

all: ${PROJECTS}

opengl:
	@echo "==== Building opengl ===="
	@${MAKE} --no-print-directory -C . -f opengl.make clang=1
	@echo "==== Finished opengl ===="

verbose:
	@echo "==== Building opengl ===="
	@${MAKE} --no-print-directory -C . -f opengl.make clang=1 verbose=1
	@echo "==== Finished opengl ===="

release:
	@echo "==== Building opengl ===="
	@${MAKE} --no-print-directory -C . -f opengl.make clang=1 release=1
	@echo "==== Finished opengl ===="

run: 
	@echo "==== Running opengl ===="
	@${MAKE} --no-print-directory -C . -f opengl.make clang=1 run

clean:
	@${MAKE} --no-print-directory -C . -f opengl.make clean
