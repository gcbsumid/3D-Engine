# Standard flags
PROJECTS := engine

.PHONY: all clean help $(PROJECTS)

all: ${PROJECTS}

engine:
	@echo "==== Building engine ===="
	@${MAKE} --no-print-directory -C . -f engine.make clang=1
	@echo "==== Finished engine ===="

verbose:
	@echo "==== Building engine ===="
	@${MAKE} --no-print-directory -C . -f engine.make clang=1 verbose=1
	@echo "==== Finished engine ===="

release:
	@echo "==== Building engine ===="
	@${MAKE} --no-print-directory -C . -f engine.make clang=1 release=1
	@echo "==== Finished engine ===="

run: 
	@echo "==== Running engine ===="
	@${MAKE} --no-print-directory -C . -f engine.make clang=1 run

clean:
	@${MAKE} --no-print-directory -C . -f engine.make clean
